//
// Created by 陆彦青 on 2020/12/20.
//

#ifndef PROJECT2_CNN_H
#define PROJECT2_CNN_H

#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

class Image {
private:
    int height;
    int width;
    int depth;
    int length;
    float *data;
public:
    Image(int rows, int cols, int channels, float * data);
    ~Image();

    void conv(int out_dep, int in_dep, int ker_size, int pad, int stride,
             const float * weight, const float * bias);
    void reLU();
    void max_pool();
    void fc(int out_dep, const float * weight, const float * bias);
    void softmax();

    void show();
    void show_info() const;

    void conv1(int out_dep, int in_dep, int ker_size, int pad, int stride, const float *weight, const float *bias);
};

template<int depth>
class Layers {
private:
    typedef float array[depth]; //将深度为depth的float数组定义为类型array，方便运算
    array ** data;
    int rows;
    int cols;
public:
    Layers(int rows, int cols);
    ~Layers();
    void init(const Mat & image);
    void conv(int out_dep, int in_dep, int ker_size, int pad, int stride,
              const float * weight, const float * bias, Layers & layers);
    void reLU();
    void max_pool(Layers & layers);
    void flatten(float * out);
};

void convert2float(const Mat & image, float * data);
float max_4(float f1, float f2, float f3, float f4); //4个浮点数取最大值

#endif //PROJECT2_CNN_H
