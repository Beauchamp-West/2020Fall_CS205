#include "cnn.h"
#include "face_binary_cls.cpp"
#include <chrono>

int main() {
    Mat origin;
    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/bg4.jpeg");

    for (int i = 0; i < 10; ++i) {

        cout << "bg4(double), ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
        auto *data = new double[origin.total() * 3];

        auto start = std::chrono::steady_clock::now();

        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (auto &conv_param : conv_params) {
//            auto inter0 = std::chrono::steady_clock::now();
            image.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
                       conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        cout << "conv " << i << endl;
//        image.show();
//            auto inter1 = std::chrono::steady_clock::now();
//            auto dur0 = std::chrono::duration_cast<std::chrono::milliseconds>(inter1 - inter0).count();
//            cout << "convolution costs " << dur0 << " ms, ";

            image.reLU();
//        cout << "reLU " << i << endl;
//        image.show();
//            auto inter2 = std::chrono::steady_clock::now();
//            auto dur1 = std::chrono::duration_cast<std::chrono::milliseconds>(inter2 - inter1).count();
//            cout << "reLU costs " << dur1 << " ms, ";

            image.max_pool();
//        cout << "max " << i << endl;
//        image.show();
//            auto inter3 = std::chrono::steady_clock::now();
//            auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(inter3 - inter2).count();
//            cout << "max pooling costs " << dur2 << " ms, ";
        }
//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        cout << "duration = " << duration << "ms, ";

//展示结果
        image.show();
        cout << endl;
    }
    return 0;
}


