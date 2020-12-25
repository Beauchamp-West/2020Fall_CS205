//
// Created by 陆彦青 on 2020/12/20.
//
#include "cnn.h"
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
void convert2float(const Mat & image, double * data) {
    Mat out;
    cvtColor(image, image, COLOR_BGR2RGB, 0); //颜色顺序转换
    image.convertTo(out, CV_64F, 1.0 / 255); //数据类型转换

    if (out.isContinuous()) { //判断图像元素是否在内存上连续
        int height = out.rows, width = out.cols, dep = out.channels();
        float * layer[out.channels()];

//#pragma omp parallel for
        for (int i = 0; i < out.channels(); ++i) {
//            cout << i << " ";
//            layer[i] = &data[i*height*width];
            for (int j = 0; j < height; ++j) {
                const auto *row = out.ptr<double>(j); //获取第j行数据的指针
                for (int k = 0; k < width; ++k) {
                    data[i*height*width+j*width+k] = row[i+k*dep]; //channel-wise方式存储
                }
            }
        }
    }
}

//卷积层
void Image::conv(int out_dep, int in_dep, int ker_size, int pad, int stride,
          const float * weight, const float * bias) {
    float * layer_j[in_dep], *weight_ij, * out_i[out_dep];
    auto * kernel = new float[ker_size*ker_size]; //卷积核
    int out_h = (height+2*pad-ker_size+1)/stride;
    int out_w = (width+2*pad-ker_size+1)/stride;
    auto * out = new double[out_dep*out_h*out_w](); //输出的数组
    int in_kr, in_kc, out_kr, out_kc, in_k;
    int kernel_r, kernel_c, p;

    for (int i = 0; i < out_dep; ++i) {
//        out_i[i] = &out[i*out_w*out_h]; //取出输出数组第i层首地址

        for (int j = 0; j < in_dep; ++j) {
//            layer_j[j] = &data[j*height*width]; //取出输入数组第j层首地址
//            weight_ij = &weight[i*(in_dep*ker_size*ker_size) + j*(ker_size*ker_size)]; //取出对应卷积核参数首地址

            for (int k = 0; k < ker_size * ker_size; ++k) {
                kernel[k] = weight[i * (in_dep * ker_size * ker_size) + j * (ker_size * ker_size) + k];
            }

//#pragma omp parallel for private(out_kr, out_kc, in_kr, in_kc, in_k)
            for (int k = 0; k < out_h * out_w; ++k) {
                out_kr = k / out_w; //输出数组第i层第kr行
                out_kc = k % out_w;
                in_kr = out_kr * stride - pad;
                in_kc = out_kc * stride - pad;
                in_k = in_kr * width + in_kc; //输入数组第j层对应卷积部分首地址
                #pragma omp critical
                {
                    for (int l = 0; l < ker_size * ker_size; ++l) {
                        kernel_r = l / ker_size; //卷积核第r层
                        kernel_c = l % ker_size;
                        p = kernel_r * (width + 2 * pad) + kernel_c; //输入数组对应坐标(从卷积部分首地址算起)
                        if ((in_k + p) >= 0) //填充部分为0故不参与计算
                            out[i * out_w * out_h + k] += kernel[l] * data[j * height * width + in_k + p];
                    }
                }
            }

            for (int k = 0; k < out_w * out_h; ++k) {
                out[i * out_w * out_h + k] += bias[i]; //输出数组第i层逐个加bias
            }
        }
    }

    delete [] kernel;
    delete [] data;
    data = out;
    height = out_h, width = out_w, depth = out_dep;
    length = height*width*depth;
}

//激励层
void Image::reLU() {
#pragma omp parallel for
    for (int i = 0; i < length; ++i) {
        data[i] = (data[i] < 0 )? 0 : data[i];
    }
}

//池化层
void Image::max_pool() {
    int r, c, out_s = length/4;
    auto * out = new double[out_s];
    float * out_i[depth], *in_i[depth];
    double f1, f2, f3, f4;

    for (int i = 0; i < depth; ++i) {
//        out_i[i] = &out[i*length/depth/4]; //取出数组第i层首地址
//        in_i[i] = &data[i*length/depth];

//#pragma omp parallel for private(f1,f2,f3,f4)
        for (int j = 0; j < out_s/depth; ++j) {
            r = j/(width/2)*2;
            c = j%(width/2)*2;
//            f1 = in_i[i][r*width+c];
//            f2 = in_i[i][r*width+c+1];
//            f3 = in_i[i][(r+1)*width+c];
//            f4 = in_i[i][(r+1)*width+c+1];
            f1 = data[i*length/depth+r*width+c];
            f2 = data[i*length/depth+r*width+c+1];
            f3 = data[i*length/depth+(r+1)*width+c];
            f4 = data[i*length/depth+(r+1)*width+c+1];
            out[i*length/depth/4+j] = max_4(f1,f2,f3,f4);
//            out_i[i][j] = max_4(f1,f2,f3,f4);
        }
    }

    delete [] data;
    data = out;
    height /= 2, width /= 2;
    length = out_s;
}

//全连接层
void Image::fc(int out_dep, const float * weight, const float * bias) {
    auto * out = new double[out_dep]();
    float * weight_i[out_dep];
    double sum = 0;

    for (int i = 0; i < out_dep; ++i) {
//        weight_i[i] = &weight[i*length];
        for (int j = 0; j < length; ++j) {
            out[i] += data[j]*weight[i*length+j];
        }

        out[i] += bias[i];

        if (out[i] < 0) out[i] = 0; //负值说明负相关，得分记为0
        sum += out[i];
    }

    for (int i = 0; i < out_dep; ++i) {
        out[i] /= sum; //使输出数值在[0,1]之间
    }

    delete [] data;
    data = out;
    height = 1, width = 1, depth = out_dep;
    length = out_dep;
}

double max_4(double f1, double f2, double f3, double f4) {
    double out = f1;
    out = (out > f2) ? out : f2;
    out = (out > f3) ? out : f3;
    out = (out > f4) ? out : f4;

    return out;
}

Image::Image(int rows, int cols, int channels, double *data) {
    this->height = rows;
    this->width = cols;
    this->depth = channels;
    this->data = data;
    this->length = rows * cols * channels;
}

Image::~Image() {
    delete [] data;
}

void Image::show() {
//    cout << "height = " << height << ", width = " << width << ", depth = " << depth << endl;
    for (int i = 0; i < depth; ++i) {
        cout << "score_" << fixed << setprecision(2) << i << ": "  << data[i] << ", ";
    }
}

template<int depth>
Layers<depth>::Layers(int r, int c) {
    rows = r;
    cols = c;
    data = new array*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new array[cols];
    }
}

template<int depth>
Layers<depth>::~Layers() {
    for (int i = 0; i < rows; ++i) {
        delete [] data[i];
    }
    delete [] data;
}

//point-wise将图像转为数组
template<int depth>
void Layers<depth>::init(const Mat &image) {
    cvtColor(image, image, COLOR_BGR2RGB, 0); //颜色顺序转换
    image.convertTo(image, CV_32F, 1.0 / 255); //数据类型转换

    if (image.isContinuous()) { //判断元素是否在内存上连续
        int col = image.cols;
        int r,c;
        for (int i = 0; i < image.total(); ++i) {
            r = i / col;
            c = i % col;
            for (int j = 0; j < depth; ++j) {
                data[r][c][j] = float(image.at<Vec3f>(r, c)[j]); //at函数耗时长
            }
        }
    }
}

template<int depth>
void Layers<depth>::conv(int out_dep, int in_dep, int ker_size, int pad, int stride,
                         const float *weight, const float *bias, Layers & layers) {
    int r_o, c_o, k_r, k_c;
    float kernel[ker_size][ker_size];
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            r_o = r * stride - pad; //原矩阵中相应子矩阵左上角元素坐标
            c_o = c * stride - pad;
            for (int i = 0; i < out_dep; ++i) {
                float * ele = layers.data[r][c][i]; //循环中多次访问用指针代替
                for (int j = 0; j < in_dep; ++j) {
                    for (int k = 0; k < ker_size*ker_size; ++k) {
                        k_r = k / ker_size;
                        k_c = k % ker_size;
                        //取出卷积核各元素
                        kernel[k_r][k_c] = weight[i*(in_dep*ker_size*ker_size) + j*(ker_size*ker_size) + k];
                        if (r_o+k_r >= 0 && r_o+k_r < rows && c_o+k_c >= 0 && c_o+k_c < cols) //非填充的部分才可能不是0
                            ele += kernel[k_r][k_c] * data[r_o+k_r][c_o+k_c][j];
                    }
                }
                *ele += bias[i];
            }
        }
    }
}

template<int depth>
void Layers<depth>::max_pool(Layers &layers) {
    auto ** out = new array *[rows/2];
    for (int i = 0; i < rows/2; ++i) {
        out[i] = new array[cols/2];
    }
    array max;
    for (int i = 0; i < rows-1; i+=2) {
        for (int j = 0; j < cols-1; j+=2) {
            for (int k = 0; k < depth; ++k) {
                max[k] = data[i][j][k];
                if (data[i+1][j][k] > max[k]) max[k] = data[i+1][j][k];
                if (data[i][j+1][k] > max[k]) max[k] = data[i][j+1][k];
                if (data[i+1][j+1][k] > max[k]) max[k] = data[i+1][j+1][k];
            }
            out[i][j] = max;
        }
    }

    for (int i = 0; i < rows; ++i) {
        delete [] data[i];
    }
    delete [] data;
    data = out;
    rows /= 2;
    cols /= 2;
}

template<int depth>
void Layers<depth>::reLU() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < depth; ++k) {
                if (data[i][j][k] < 0) data[i][j][k] = 0;
            }
        }
    }
}

template<int depth>
void Layers<depth>::flatten(float * out) {
    int r,c;
    for (int i = 0; i < rows*cols*depth; i+=depth) {
        r = i/depth / cols;
        c = i/depth % cols;
        for (int j = 0; j < depth; ++j) {
            out[i] = data[r][c][j];
        }
    }
}

void fc(int in_size, int out_size, float * in, float * out, const float * weight, float * bias)
{
    float w_ij;
    for (int i = 0; i < out_size; ++i) {
        for (int j = 0; j < in_size; ++j) {
            out[i] += weight[i*out_size + j];

        }
    }
}

