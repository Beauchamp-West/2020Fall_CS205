//
// Created by 陆彦青 on 2020/12/20.
//

#ifndef PROJECT2_CNN_H
#define PROJECT2_CNN_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "face_binary_cls.h"
using namespace cv;
using namespace std;

class Image {
public:
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
    void reLU() const;
    void max_pool();
    void fc(int out_dep, const float * weight, const float * bias);
    void softmax() const;

    void conv1(int out_dep, int in_dep, int ker_size, int pad, int stride,
               const float *weight, const float *bias);
    void conv2_1(int out_dep, int in_dep, int ker_size, int pad, int stride,
              const float * weight, const float * bias);
    void conv2_2(int out_dep, int in_dep, int ker_size, int pad, int stride,
               const float * weight, const float * bias);

//point-wise存储对应方法
    void conv_p(int out_dep, int in_dep, int ker_size, int pad, int stride,
              float * weight, const float * bias);
    void max_pool_p();
    void fc_p(int out_dep, const float * weight, const float * bias);

    void show() const;

//前向传播封装
    void forward(conv_param *convParam, fc_param *fcParam, int layers);
    void forward1(conv_param *convParam, fc_param *fcParam, int layers);
    void forward2_1(conv_param *convParam, fc_param *fcParam, int layers);
    void forward2_2(conv_param *convParam, fc_param *fcParam, int layers);
    void forward_p(conv_param *convParam, fc_param *fcParam, int layers);

};

void convert2float(const Mat & image, float * data);
void convert2float_p(const Mat & image, float * data);
void convert_order(float * out, const float * data, int out_dep, int in_dep, int ker_size);
float max_4(float f1, float f2, float f3, float f4); //4个浮点数取最大值

#endif //PROJECT2_CNN_H
