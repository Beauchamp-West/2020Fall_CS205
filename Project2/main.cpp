#include "cnn.h"
#include "face_binary_cls.cpp"
#include <chrono>

int main() {
    Mat origin;
    origin = imread("../image/face.jpg");
//    cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;

    cout << "(face & conv) * 100, ";
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
            image.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                       conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
            image.reLU();
            if (j < 2) image.max_pool(); //最后一次不需要池化
        }

//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image.softmax();

//展示结果
//        image.show();
//        cout << endl;
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";






    cout << "(face & conv1) * 100, ";
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float(origin, data);

        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
            image.conv1(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                          conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
            image.reLU();
            if (j < 2) image.max_pool(); //最后一次不需要池化
        }

//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image.softmax();


//展示结果
//        image.show();
//        cout << endl;
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";


    cout << "(face & conv2_1) * 100, ";
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
            image.conv2_1(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                        conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
            image.reLU();
            if (j < 2) image.max_pool(); //最后一次不需要池化
        }

//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image.softmax();


//展示结果
//        image.show();
//        cout << endl;
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";





    cout << "(face & conv2_2) * 100, ";
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
            image.conv2_2(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                          conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
            image.reLU();
            if (j < 2) image.max_pool(); //最后一次不需要池化
        }

//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image.softmax();

//展示结果
//        image.show();
//        cout << endl;
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";





    cout << "(face & conv2_1) * 100, ";
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
            image.conv2_1(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                          conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
            image.reLU();
            if (j < 2) image.max_pool(); //最后一次不需要池化
        }

//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image.softmax();


//展示结果
//        image.show();
//        cout << endl;
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";






    cout << "(face & conv1) * 100, ";
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
            image.conv1(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                        conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
            image.reLU();
            if (j < 2) image.max_pool(); //最后一次不需要池化
        }

//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image.softmax();


//展示结果
//        image.show();
//        cout << endl;
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";






    cout << "(face & conv) * 100, ";
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
            image.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                        conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
            image.reLU();
            if (j < 2) image.max_pool(); //最后一次不需要池化
        }

//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image.softmax();


//展示结果
//        image.show();
//        cout << endl;
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";

    return 0;
}


