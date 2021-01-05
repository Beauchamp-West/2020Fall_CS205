//
// Created by 陆彦青 on 2021/1/5.
//

#ifndef PROJECT2_FACE_BINARY_CLS_H
#define PROJECT2_FACE_BINARY_CLS_H
typedef struct conv_param {
    int pad;
    int stride;
    int kernel_size;
    int in_channels;
    int out_channels;
    float* p_weight;
    float* p_bias;
} conv_param;

typedef struct fc_param {
    int in_features;
    int out_features;
    float* p_weight;
    float* p_bias;
} fc_param;

extern conv_param conv_params[3];
extern fc_param fc_params[1];

#endif //PROJECT2_FACE_BINARY_CLS_H
