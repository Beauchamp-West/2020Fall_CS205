#include "cnn.h"
#include "face_binary_cls.cpp"
#include <chrono>

int main() {
    Mat origin;
    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face.jpg");

    for (int i = 0; i < 10; ++i) {

        cout << "face0 & O3, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
        auto *data = new float[origin.total() * 3];

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

//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face1.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face1 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image1(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image1.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                   conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image1.reLU();
//        image1.max_pool();
//    }
////全连接
//    image1.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image1.show();
//    cout << endl;
////    }
//
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face2.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face2 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image2(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image2.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image2.reLU();
//        image2.max_pool();
//    }
////全连接
//    image2.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image2.show();
//    cout << endl;
////    }
//
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face3.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face3 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image3(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image3.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image3.reLU();
//        image3.max_pool();
//    }
////全连接
//    image3.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image3.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face4.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face4 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image4(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image4.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image4.reLU();
//        image4.max_pool();
//    }
////全连接
//    image4.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image4.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face5.jpg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face5 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image5(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image5.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image5.reLU();
//        image5.max_pool();
//    }
////全连接
//    image5.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image5.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face6.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face6 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image6(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image6.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image6.reLU();
//        image6.max_pool();
//    }
////全连接
//    image6.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image6.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face7.jpg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face7 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image7(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image7.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image7.reLU();
//        image7.max_pool();
//    }
////全连接
//    image7.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image7.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face8.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face8 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image8(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image8.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image8.reLU();
//        image8.max_pool();
//    }
////全连接
//    image8.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image8.show();
//    cout << endl;
////    }
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face9.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face9 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image9(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image9.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image9.reLU();
//        image9.max_pool();
//    }
////全连接
//    image9.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image9.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/face10.jpg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "face10 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image10(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image10.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image10.reLU();
//        image10.max_pool();
//    }
////全连接
//    image10.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image10.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/bg0.jpg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "bg0 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image11(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image11.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image11.reLU();
//        image11.max_pool();
//    }
////全连接
//    image11.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image11.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/bg1.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "bg1 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image12(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image12.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image12.reLU();
//        image12.max_pool();
//    }
////全连接
//    image12.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image12.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/bg2.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "bg2 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image13(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image13.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image13.reLU();
//        image13.max_pool();
//    }
////全连接
//    image13.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image13.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/bg3.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "bg3 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image14(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image14.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image14.reLU();
//        image14.max_pool();
//    }
////全连接
//    image14.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image14.show();
//    cout << endl;
////    }
//
//
//
//    origin = imread("/Users/leolu/Downloads/C++/Project2_1/image/bg4.jpeg");
//
////    for (int i = 0; i < 10; ++i) {
//
//    cout << "bg4 & O3, ";
////        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
//    data = new float[origin.total() * 3];
//
//    start = std::chrono::steady_clock::now();
//
//    convert2float(origin, data);
//    Image image15(origin.rows, origin.cols, origin.channels(), data);
//
////3次卷积操作
//    for (auto &conv_param : conv_params) {
//        image15.conv(conv_param.out_channels, conv_param.in_channels, conv_param.kernel_size,
//                    conv_param.pad, conv_param.stride, conv_param.p_weight, conv_param.p_bias);
//        image15.reLU();
//        image15.max_pool();
//    }
////全连接
//    image15.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
//
//    end = std::chrono::steady_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//
//    cout << "duration = " << duration << "ms, ";
//
////展示结果
//    image15.show();
//    cout << endl;
////    }

    return 0;
}


