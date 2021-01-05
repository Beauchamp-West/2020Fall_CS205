//
// Created by 陆彦青 on 2020/12/20.
//
#include "cnn.h"
#include <cmath>
//#if defined(_OPENMP)
//#include <omp.h>
//#endif

//从图像读取数据到一维数组
void convert2float(const Mat & image, float * data) {
    Mat out = image.clone();
    cvtColor(out, out, COLOR_BGR2RGB, 0); //颜色顺序转换
    out.convertTo(out, CV_32F, 1.0 / 255); //数据类型转换

    if (out.isContinuous()) { //判断图像元素是否在内存上连续
        int height = out.rows, width = out.cols, dep = out.channels();

        for (int i = 0; i < out.channels(); ++i) {
            for (int j = 0; j < height; ++j) {
                const auto *row = out.ptr<float>(j); //获取第j行数据的指针
                for (int k = 0; k < width; ++k)
                    data[i*height*width+j*width+k] = row[i+k*dep]; //channel-wise方式存储
            }
        }
    }
}
void convert2float_p(const Mat & image, float * data) {
    Mat out = image.clone();
    cvtColor(out, out, COLOR_BGR2RGB, 0); //颜色顺序转换
    out.convertTo(out, CV_32F, 1.0 / 255); //数据类型转换

    if (out.isContinuous()) { //判断图像元素是否在内存上连续
        int height = out.rows, width = out.cols;

        for (int j = 0; j < height; ++j) {
            const auto *row = out.ptr<float>(j); //获取第j行数据的指针
            for (int k = 0; k < width*out.channels(); ++k)
                data[j*width*out.channels()+k] = row[k]; //point-wise方式存储
        }
    }
}


//卷积层
//channel-wise
void Image::conv(int out_dep, int in_dep, int ker_size, int pad, int stride,
          const float * weight, const float * bias) {
    auto * kernel = new float[ker_size*ker_size]; //卷积核
    int out_h = (height+2*pad-ker_size)/stride+1;
    int out_w = (width+2*pad-ker_size)/stride+1;
    auto * out = new float[out_dep*out_h*out_w](); //输出的数组
    int in_kr, in_kc, out_kr, out_kc, in_k;
    int kernel_r, kernel_c, p;

    for (int i = 0; i < out_dep; ++i) {
        for (int j = 0; j < in_dep; ++j) {
            for (int k = 0; k < ker_size*ker_size; ++k) {
                kernel[k] = weight[i * (in_dep * ker_size * ker_size) + j * (ker_size * ker_size) + k];
            }

            for (int k = 0; k < out_h*out_w; ++k) {
                out_kr = k/out_w; //输出数组第i层第kr行
                out_kc = k%out_w;
                in_kr = out_kr*stride-pad;
                in_kc = out_kc*stride-pad;
                in_k = in_kr*width+in_kc; //输入数组第j层对应卷积部分首地址

                for (int l = 0; l < ker_size*ker_size; ++l) {
                    kernel_r = l/ker_size; //卷积核第r层
                    kernel_c = l%ker_size;
                    p = kernel_r*width+kernel_c; //输入数组对应坐标(从卷积部分首地址算起)
                    bool out_of_range = in_kr+kernel_r < 0 || in_kr+kernel_r >= width
                                        || in_kc+kernel_c < 0 || in_kc+kernel_c >= width; //判断坐标是否在非填充区域外
                    if (!out_of_range) //填充部分为0故不参与计算
                        out[i * out_w * out_h + k] += kernel[l] * data[j * height * width + in_k + p];
                }
            }
        }

        for (int k = 0; k < out_w*out_h; ++k) {
            out[i * out_w * out_h + k] += bias[i];
        }
    }

    delete [] kernel;
    delete [] data;
    data = out;
    height = out_h, width = out_w, depth = out_dep;
    length = height*width*depth;
}
void Image::conv1(int out_dep, int in_dep, int ker_size, int pad, int stride,
                  const float * weight, const float * bias) {
    float kernel_l;
    int out_h = (height+2*pad-ker_size)/stride+1;
    int out_w = (width+2*pad-ker_size)/stride+1;
    auto * out = new float[out_dep*out_h*out_w](); //输出的数组
    int in_kr, in_kc, out_kr, out_kc, in_k;
    int kernel_r, kernel_c, p;
    float * out_i, * data_j, bias_i;

    for (int i = 0; i < out_dep; ++i) {
        out_i = &out[i * out_w * out_h]; //输出矩阵第i层首地址
        bias_i = bias[i];

        for (int j = 0; j < in_dep; ++j) {
            data_j = &data[j * height * width]; // 输入矩阵第j层首地址

            for (int l = 0; l < ker_size*ker_size; ++l) {
                kernel_r = l/ker_size; //卷积核第r层
                kernel_c = l%ker_size;
                p = kernel_r*width+kernel_c; //输入矩阵对应坐标偏移量(从卷积部分首地址算起)
                kernel_l = weight[i * (in_dep * ker_size * ker_size) + j * (ker_size * ker_size) + l];

                for (int k = 0; k < out_h*out_w; ++k) {
                    out_kr = k/out_w; //输出矩阵第i层第kr行
                    out_kc = k%out_w;
                    in_kr = out_kr*stride-pad;
                    in_kc = out_kc*stride-pad;
                    in_k = in_kr*width+in_kc; //输入矩阵第j层对应卷积部分首地址
                    bool out_of_range = in_kr+kernel_r < 0 || in_kr+kernel_r >= width
                                        || in_kc+kernel_c < 0 || in_kc+kernel_c >= width; //判断坐标是否在非填充区域外
                    if (!out_of_range) { //填充部分为0故不参与计算
                        out_i[k] += kernel_l * data_j[in_k + p];
                    }
                }

            }
        }

        for (int k = 0; k < out_w*out_h; ++k) {
            out[i * out_w * out_h + k] += bias_i;
        }
    }

    delete [] data;
    data = out;
    height = out_h, width = out_w, depth = out_dep;
    length = height*width*depth;
}
void Image::conv2_1(int out_dep, int in_dep, int ker_size, int pad, int stride,
                 const float * weight, const float * bias) {
    auto * kernel = new float[ker_size*ker_size]; //卷积核
    int out_h = (height+2*pad-ker_size)/stride+1;
    int out_w = (width+2*pad-ker_size)/stride+1;
    auto * out = new float[out_dep*out_h*out_w+1](); //输出的数组
    int in_kr, in_kc, out_kr, out_kc, in_k;
    int kernel_r, kernel_c;

    for (int i = 0; i < out_dep; ++i) {
        for (int j = 0; j < in_dep; ++j) {
            for (int k = 0; k < ker_size*ker_size; ++k) {
                kernel[k] = weight[i * (in_dep * ker_size * ker_size) + j * (ker_size * ker_size) + k];
            }

            for (int k = 0; k < out_h*out_w; ++k) {
                out_kr = k/out_w; //输出数组第i层第kr行
                out_kc = k%out_w;
                in_kr = out_kr*stride-pad;
                in_kc = out_kc*stride-pad;

                for (int l = 0; l < ker_size*ker_size; ++l) {
                    kernel_r = l/ker_size; //卷积核第r层
                    kernel_c = l%ker_size;
                    in_k = (in_kr+kernel_r) * width + (in_kc+kernel_c); //输入矩阵对应坐标
                    bool out_of_range = in_kr+kernel_r < 0 || in_kr+kernel_r >= width
                                        || in_kc+kernel_c < 0 || in_kc+kernel_c >= width; //判断坐标是否在非填充区域外
                    out[i * out_w * out_h + k] += out_of_range? 0 : kernel[l] * data[j * height * width + in_k];
                }
            }
        }

        for (int k = 0; k < out_w*out_h; ++k) {
            out[i * out_w * out_h + k] += bias[i];
        }
    }
    delete [] kernel;
    delete [] data;
    data = out;
    height = out_h, width = out_w, depth = out_dep;
    length = height*width*depth;
}
void Image::conv2_2(int out_dep, int in_dep, int ker_size, int pad, int stride,
                 const float * weight, const float * bias) {
    float kernel_l,bias_i;
    int out_h = (height+2*pad-ker_size)/stride+1;
    int out_w = (width+2*pad-ker_size)/stride+1;
    auto * out = new float[out_dep*out_h*out_w](); //输出的数组
    int in_kr, in_kc, out_kr, out_kc, in_k;
    int kernel_r, kernel_c;
    float * out_i, * data_j;

    for (int i = 0; i < out_dep; ++i) {
        out_i = &out[i * out_w * out_h]; //输出矩阵第i层首地址
        bias_i = bias[i];

        for (int j = 0; j < in_dep; ++j) {
            data_j = &data[j * height * width]; // 输入矩阵第j层首地址

            for (int l = 0; l < ker_size*ker_size; ++l) {
                kernel_r = l/ker_size; //卷积核第r层
                kernel_c = l%ker_size;
                kernel_l = weight[i * (in_dep * ker_size * ker_size) + j * (ker_size * ker_size) + l];

                for (int k = 0; k < out_h*out_w; ++k) {
                    out_kr = k/out_w; //输出矩阵第i层第kr行
                    out_kc = k%out_w;
                    in_kr = out_kr*stride-pad;
                    in_kc = out_kc*stride-pad;
                    in_k = (in_kr+kernel_r) * width + (in_kc+kernel_c); //输入矩阵对应坐标
                    bool out_of_range = in_kr+kernel_r < 0 || in_kr+kernel_r >= width
                                        || in_kc+kernel_c < 0 || in_kc+kernel_c >= width; //判断坐标是否在非填充区域外
                    out_i[k] += out_of_range? 0 : kernel_l * data_j[in_k];
                }

            }
        }

        for (int k = 0; k < out_w*out_h; ++k) {
            out_i[k] += bias_i;
        }
    }

    delete [] data;
    data = out;
    height = out_h, width = out_w, depth = out_dep;
    length = height*width*depth;
}
//point-wise
void Image::conv_p(int out_dep, int in_dep, int ker_size, int pad, int stride, float *weight, const float *bias) {
    float * kernel; //卷积核
    int out_h = (height+2*pad-ker_size)/stride+1;
    int out_w = (width+2*pad-ker_size)/stride+1;
    auto * out = new float[out_dep*out_h*out_w](); //输出的数组
    int in_r, in_c, out_r, out_c, in_l;
    int kernel_r, kernel_c, p;

    for (int i = 0; i < out_h*out_w; ++i) {
        out_r = i/out_w;
        out_c = i%out_w;
        in_r = out_r*stride-pad;
        in_c = out_c*stride-pad;
        for (int j = 0; j < out_dep; ++j) {
            for (int k = 0; k < ker_size*ker_size; ++k) {
                kernel = &weight[k*in_dep*out_dep + j*in_dep];
                kernel_r = k/ker_size; //卷积核第r层
                kernel_c = k%ker_size;
                p = kernel_r*width+kernel_c; //平面上坐标偏移量

                for (int l = 0; l < in_dep; ++l) {
                    in_l = (in_r*width+in_c+p) * in_dep + l; //原矩阵对应坐标
                    bool out_of_range = in_r+kernel_r < 0 || in_r+kernel_r >= width
                                        || in_c+kernel_c < 0 || in_c+kernel_c >= width; //判断坐标是否在非填充区域外
                    out[i*out_dep+j] += out_of_range ? 0 : kernel[l]*data[in_l];
                }
            }

            out[i*out_dep+j] += bias[j];
        }
    }

    delete [] data;
    data = out;
    height = out_h, width = out_w, depth = out_dep;
    length = height*width*depth;
}

//激励层
void Image::reLU() const {
    for (int i = 0; i < length; ++i) {
        data[i] = (data[i] < 0 )? 0 : data[i];
    }
}

//池化层
void Image::max_pool() {
    int r, c, out_s = length/4;
    auto * out = new float[out_s];
    float f1, f2, f3, f4;

    for (int i = 0; i < depth; ++i) {
        for (int j = 0; j < out_s/depth; ++j) {
            r = j / (width / 2) * 2;
            c = j % (width / 2) * 2;

            f1 = data[i * length / depth + r * width + c];
            f2 = data[i * length / depth + r * width + c + 1];
            f3 = data[i * length / depth + (r + 1) * width + c];
            f4 = data[i * length / depth + (r + 1) * width + c + 1];

            out[i * length / depth / 4 + j] = max_4(f1, f2, f3, f4);
        }
    }

    delete [] data;
    data = out;
    height /= 2, width /= 2;
    length = out_s;
}
//point-wise存储的池化
void Image::max_pool_p() {
    int r, c, out_s = length/4;
    auto * out = new float[out_s];
    float f1, f2, f3, f4;

    for (int i = 0; i < depth; ++i) {
        for (int j = 0; j < width*height/4; ++j) {
            r = j / (width / 2) * 2;
            c = j % (width / 2) * 2;

            f1 = data[(r*width+c)*depth+i];
            f2 = data[(r*width+c+1)*depth+i];
            f3 = data[((r+1)*width+c)*depth+i];
            f4 = data[((r+1)*width+c+1)*depth+i];

            out[j*depth+i] = max_4(f1, f2, f3, f4);
        }
    }

    delete [] data;
    data = out;
    height /= 2, width /= 2;
    length = out_s;
}

//全连接层
void Image::fc(int out_dep, const float * weight, const float * bias) {
    auto * out = new float[out_dep]();

    for (int i = 0; i < out_dep; ++i) {
        for (int j = 0; j < length; ++j) {
            out[i] += data[j] * weight[i * length + j];
        }

        out[i] += bias[i];
    }

    delete [] data;
    data = out;
    height = 1, width = 1, depth = out_dep;
    length = out_dep;
}
//point-wise存储的全连接
void Image::fc_p(int out_dep, const float *weight, const float *bias) {
    auto * out = new float[out_dep]();

    for (int i = 0; i < out_dep; ++i) {
        for (int j = 0; j < length; ++j) {
            int p = j%(height*width) * depth + j/(height*width);
            out[i] += data[p] * weight[i * length + j];
        }

        out[i] += bias[i];
    }

    delete [] data;
    data = out;
    height = 1, width = 1, depth = out_dep;
    length = out_dep;
}

void Image::softmax() const {
    float sum = 0, max = 0;
    for (int i = 0; i < length; ++i) {
        max = max > data[i] ? max : data[i];
    }
    for (int i = 0; i < length; ++i) {
        sum += exp(data[i]-max);
    }
    for (int i = 0; i < length; ++i) {
        data[i] = exp(data[i]-max)/sum; //防止上下溢出
    }
}

Image::Image(int rows, int cols, int channels, float *data) {
    this->height = rows;
    this->width = cols;
    this->depth = channels;
    this->length = rows * cols * channels;
    this->data = data;
}

Image::~Image() {
    delete [] data;
}

void Image::show() const {
//    cout << "height = " << height << ", width = " << width << ", depth = " << depth << endl;
    for (int i = 0; i < depth; ++i) {
        printf("score_%d: %.2f, ",i,data[i]);
    }
}

//point-wise方式前向传播封装
void Image::forward_p(conv_param * convParam, fc_param * fcParam, int layers) {
    for (int i = 0; i < layers; ++i) {
        auto weight = new float[convParam[i].out_channels*convParam[i].in_channels*
                                convParam[i].kernel_size*convParam[i].kernel_size];
        convert_order(weight,convParam[i].p_weight,convParam[i].out_channels,
                      convParam[i].in_channels,convParam[i].kernel_size);

        conv_p(convParam[i].out_channels, convParam[i].in_channels, convParam[i].kernel_size,
                     convParam[i].pad, convParam[i].stride, weight, convParam[i].p_bias);
        reLU();
        if (i < layers-1) max_pool_p(); //最后一次不需要池化

        delete [] weight;
    }

    fc_p(fcParam->out_features, fcParam->p_weight, fcParam->p_bias);
    softmax();
}

void Image::forward(conv_param *convParam, fc_param *fcParam, int layers) {
    for (int i = 0; i < layers; ++i) {
        conv(convParam[i].out_channels, convParam[i].in_channels, convParam[i].kernel_size,
               convParam[i].pad, convParam[i].stride, convParam[i].p_weight, convParam[i].p_bias);
        reLU();
        if (i < layers-1) max_pool(); //最后一次不需要池化
    }

    fc(fcParam->out_features, fcParam->p_weight, fcParam->p_bias);
    softmax();
}

void Image::forward1(conv_param *convParam, fc_param *fcParam, int layers) {
    for (int i = 0; i < layers; ++i) {
        conv1(convParam[i].out_channels, convParam[i].in_channels, convParam[i].kernel_size,
             convParam[i].pad, convParam[i].stride, convParam[i].p_weight, convParam[i].p_bias);
        reLU();
        if (i < layers-1) max_pool(); //最后一次不需要池化
    }

    fc(fcParam->out_features, fcParam->p_weight, fcParam->p_bias);
    softmax();
}

void Image::forward2_1(conv_param *convParam, fc_param *fcParam, int layers) {
    for (int i = 0; i < layers; ++i) {
        conv2_1(convParam[i].out_channels, convParam[i].in_channels, convParam[i].kernel_size,
             convParam[i].pad, convParam[i].stride, convParam[i].p_weight, convParam[i].p_bias);
        reLU();
        if (i < layers-1) max_pool(); //最后一次不需要池化
    }

    fc(fcParam->out_features, fcParam->p_weight, fcParam->p_bias);
    softmax();
}

void Image::forward2_2(conv_param *convParam, fc_param *fcParam, int layers) {
    for (int i = 0; i < layers; ++i) {
        conv2_2(convParam[i].out_channels, convParam[i].in_channels, convParam[i].kernel_size,
             convParam[i].pad, convParam[i].stride, convParam[i].p_weight, convParam[i].p_bias);
        reLU();
        if (i < layers-1) max_pool(); //最后一次不需要池化
    }

    fc(fcParam->out_features, fcParam->p_weight, fcParam->p_bias);
    softmax();
}

float max_4(float f1, float f2, float f3, float f4) {
    float out = f1;
    out = (out > f2) ? out : f2;
    out = (out > f3) ? out : f3;
    out = (out > f4) ? out : f4;

    return out;
}

//channel-wise转为point-wise
void convert_order(float * out, const float * data, int out_dep, int in_dep, int ker_size) {
    for (int i = 0; i < ker_size*ker_size; ++i) {
        for (int j = 0; j < out_dep; ++j) {
            for (int k = 0; k < in_dep; ++k) {
                out[i*out_dep*in_dep+j*in_dep+k] = data[j*in_dep*ker_size*ker_size + k*ker_size*ker_size + i];
            }
        }
    }
}


