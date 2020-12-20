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
private:
    int rows;
    int cols;
    int channels;
    int length;
    float *data;
public:
    Image(int rows, int cols, int channels, float *data);
    void conv(conv_param & convParam);
    void maxPool();
    void reLU();
    void fc(fc_param & fcParam);
};

void * convertToFloat(const Mat & image, float * data);

#endif //PROJECT2_CNN_H
