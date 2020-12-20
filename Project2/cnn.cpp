//
// Created by 陆彦青 on 2020/12/20.
//
#include "cnn.h"

void * convertToFloat(const Mat & image, float * data) {
//    cout << image(Range(0, 1), Range::all()) << endl;
    cvtColor(image, image, COLOR_BGR2RGB, 0); //颜色顺序转换
//    cout << image(Range(0, 1), Range::all()) << endl;
    image.convertTo(image, CV_32F, 1.0 / 255); //数据类型转换
//    cout << image(Range(0, 1), Range::all()) << endl;

    if (image.isContinuous()) {
        int row = image.rows, col = image.cols;
        int d,r,c;
        for (int i = 0; i < image.total()*3; ++i) {
            d = i / (row*col);
            r = (i % (row*col)) / col;
            c = (i % (row*col)) % col;
            data[i] = float(image.at<Vec3f>(r,c)[d]); //用数组存储数据
        }
    }
    return nullptr;
}

Image::Image(int rows, int cols, int channels, float *data) {
    this->rows = rows;
    this->cols = cols;
    this->channels = channels;
    this->data = data;
    this->length = rows * cols * channels;
}

void Image::conv(conv_param & param) {
    int outRows = (rows+2*param.pad-param.kernel_size)/param.stride+1;
    int outCols = (cols+2*param.pad-param.kernel_size)/param.stride+1;
    int outSize = outCols*outRows*param.out_channels;

    auto **out = new float*[outRows];
    for (int i = 0; i < outRows; ++i) {
        out[i] = new float[outCols*param.out_channels];
    }

    int kernelSize = param.kernel_size*param.kernel_size;
    int kernelNum = param.out_channels*param.in_channels;
    float kernel[kernelNum][kernelSize];
    float bias[param.out_channels];

    for (int o = 0; o < param.out_channels; ++o) {
        for (int i = 0; i < param.in_channels; ++i) {
            // weights
            // first row of the kernel
            for (int j = 0; j < kernelSize; ++j)
                kernel[o*param.in_channels+i][j] = param.p_weight[o*(param.in_channels*3*3) + i*(3*3) + j];


        }
        // bias
        bias[o] = param.p_bias[o];
    }

    int d,r,c;
    for (int i = 0; i < outSize; ++i) {
        d = i/(outRows*outCols);
        r = i / (param.out_channels*outCols);
        c = (i % (param.out_channels*outCols)) / param.out_channels;


    }

}
