#include "cnn.h"
#include <chrono>

int main() {
    Mat origin;
    origin = imread("../image/face.jpg"); //读取输入图像
    cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;


    cout << "(face & conv) * 100, ";
    auto start = std::chrono::steady_clock::now();

//重复测试100次
    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data); //初始化

//3层卷积计算
        image.forward(conv_params,fc_params,3);

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

        image.forward1(conv_params,fc_params,3);


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

        image.forward2_1(conv_params,fc_params,3);


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

        image.forward2_2(conv_params,fc_params,3);

//展示结果
//        image.show();
//        cout << endl;
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";



    cout << "(face & conv_p) * 100, ";
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < 100; ++i) {
        auto *data = new float[origin.total() * 3]();
        convert2float_p(origin, data); //按point-wise存储方式转换
        Image image(origin.rows, origin.cols, origin.channels(), data);

        image.forward_p(conv_params,fc_params,3);
////3次卷积操作
//        for (int j = 0; j < 3; ++j) {
//            //转换原参数的存储方式
//            auto weight = new float[conv_params[j].out_channels*conv_params[j].in_channels*
//                                  conv_params[j].kernel_size*conv_params[j].kernel_size];
//            convert_order(weight,conv_params[j].p_weight,conv_params[j].out_channels,
//                          conv_params[j].in_channels,conv_params[j].kernel_size);
//
//            image.conv_p(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
//                        conv_params[j].pad, conv_params[j].stride, weight, conv_params[j].p_bias);
//            image.reLU();
//            if (j < 2) image.max_pool_p(); //最后一次不需要池化
//
//            delete [] weight;
//        }
//
////全连接
//        image.fc_p(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//        image.softmax();


//展示结果
//        image.show();
//        cout << endl;
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "duration = " << duration << "ms,\n";


    return 0;
}


