//
// Created by 陆彦青 on 2020/12/20.
//
#include "cnn.h"
#include <cmath>
#if defined(_OPENMP)
#include <omp.h>
#endif
#if defined(_ENABLE_AVX512) || defined(_ENABLE_AVX2)
#include <immintrin.h>
#endif
#if defined(_ENABLE_NEON)
#include <arm_neon.h>
#endif

//从图像读取数据到一维数组
void convert2float(const Mat & image, float * data) {
    Mat out;
    image.convertTo(out, CV_32F, 1.0/255.0); //数据类型转换
    cvtColor(out, out, COLOR_BGR2RGB, 0); //颜色顺序转换
//    cout << out.rowRange(0,1) << endl;

    if (out.isContinuous()) { //判断图像元素是否在内存上连续
        int height = out.rows, width = out.cols, dep = out.channels();

        for (int i = 0; i < out.channels(); ++i) {
            for (int j = 0; j < height; ++j) {
                const auto *row = out.ptr<float>(j); //获取第j行数据的指针
                for (int k = 0; k < width; ++k) {
                    data[i*height*width+j*width+k] = row[i+k*dep]; //channel-wise方式存储
                }
            }
        }
    }
//    for (int i = 0; i < 128; ++i) {
//        cout << data[i] << ", ";
//    }
//    cout << endl;
}

//卷积层
void Image::conv(int out_dep, int in_dep, int ker_size, int pad, int stride,
          const float * weight, const float * bias) {
    float * layer_j, *weight_ij, * out_i;
    auto * kernel = new float[ker_size*ker_size]; //卷积核
    int out_h = (height+2*pad-ker_size)/stride+1;
    int out_w = (width+2*pad-ker_size)/stride+1;
    auto * out = new float[out_dep*out_h*out_w](); //输出的数组
    int in_kr, in_kc, out_kr, out_kc, in_k;
    int kernel_r, kernel_c, p;

    for (int i = 0; i < out_dep; ++i) {
        out_i = &out[i*out_w*out_h]; //取出输出数组第i层首地址

        for (int j = 0; j < in_dep; ++j) {
//            layer_j = &data[j*height*width]; //取出输入数组第j层首地址
//            weight_ij = &weight[i*(in_dep*ker_size*ker_size) + j*(ker_size*ker_size)]; //取出对应卷积核参数首地址

            for (int k = 0; k < ker_size*ker_size; ++k) {
//                kernel[k] = weight_ij[k];
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
                    if ((in_k+p) >= 0) //填充部分为0故不参与计算
//                        out_i[k] += kernel[l]*layer_j[in_k+p];
                        out[i * out_w * out_h + k] += kernel[l] * data[j * height * width + in_k + p];
                }
            }
        }

        for (int k = 0; k < out_w*out_h; ++k) {
//            out_i[k] += bias[i]; //输出数组第i层逐个加bias
            out[i * out_w * out_h + k] += bias[i];
        }
    }

    delete [] kernel;
    delete [] data;
    data = out;
    height = out_h, width = out_w, depth = out_dep;
    length = height*width*depth;
}
//优化后的卷积
void Image::conv1(int out_dep, int in_dep, int ker_size, int pad, int stride,
                 const float * weight, const float * bias) {
    float kernel_l;
    int out_h = (height+2*pad-ker_size)/stride+1;
    int out_w = (width+2*pad-ker_size)/stride+1;
    auto * out = new float[out_dep*out_h*out_w](); //输出的数组
    int in_kr, in_kc, out_kr, out_kc, in_k;
    int kernel_r, kernel_c, p;

    for (int i = 0; i < out_dep; ++i) {
        for (int j = 0; j < in_dep; ++j) {
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

                    if ((in_k+p) >= 0) //填充部分为0故不参与计算
                        out[i * out_w * out_h + k] += kernel_l * data[j * height * width + in_k + p];
                }

            }
        }

        for (int k = 0; k < out_w*out_h; ++k) {
            out[i * out_w * out_h + k] += bias[i];
        }
    }

    delete [] data;
    data = out;
    height = out_h, width = out_w, depth = out_dep;
    length = height*width*depth;
}

//激励层
void Image::reLU() {
    for (int i = 0; i < length; ++i) {
        data[i] = (data[i] < 0 )? 0 : data[i];
    }
}

//池化层
void Image::max_pool() {
    int r, c, out_s = length/4;
    float * out = new float[out_s];
    float * out_i, *in_i;
    float f1, f2, f3, f4;

    for (int i = 0; i < depth; ++i) {
//        out_i = &out[i*length/depth/4]; //取出数组第i层首地址
//        in_i = &data[i*length/depth];

        for (int j = 0; j < out_s/depth; ++j) {
            r = j/(width/2)*2;
            c = j%(width/2)*2;
//            f1 = in_i[r*width+c];
//            f2 = in_i[r*width+c+1];
//            f3 = in_i[(r+1)*width+c];
//            f4 = in_i[(r+1)*width+c+1];
//            out_i[j] = max_4(f1,f2,f3,f4);

            f1 = data[i*length/depth+r*width+c];
            f2 = data[i*length/depth+r*width+c+1];
            f3 = data[i*length/depth+(r+1)*width+c];
            f4 = data[i*length/depth+(r+1)*width+c+1];
            out[i*length/depth/4+j] = max_4(f1,f2,f3,f4);
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
    float * weight_i;

    for (int i = 0; i < out_dep; ++i) {
//        weight_i = &weight[i*length];

        for (int j = 0; j < length; ++j) {
//            out[i] += data[j]*weight_i[j];
            out[i] += data[j]*weight[i*length+j];
        }

        out[i] += bias[i];
    }

    delete [] data;
    data = out;
    height = 1, width = 1, depth = out_dep;
    length = out_dep;
}

void Image::softmax() {
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

float max_4(float f1, float f2, float f3, float f4) {
    float out = f1;
    out = (out > f2) ? out : f2;
    out = (out > f3) ? out : f3;
    out = (out > f4) ? out : f4;

    return out;
}

Image::Image(int rows, int cols, int channels, float *data) {
    this->height = rows;
    this->width = cols;
    this->depth = channels;
    this->data = data;
    this->length = rows * cols * channels;
}

Image::~Image() {
    delete [] data;
//    cout << "image destructed" << endl;
}

void Image::show() {
//    cout << "height = " << height << ", width = " << width << ", depth = " << depth << endl;
    for (int i = 0; i < depth; ++i) {
        cout << "score_" << fixed << setprecision(2) << i << ": "  << data[i] << ", ";
    }
}

void Image::show_info() const {
    cout << endl;
    cout << "length: " << length << ", height: " << height << ", depth: " << depth << endl;
    for (int j = 100; j < 120; ++j) {
        cout << data[j] << ", ";
    }
}

