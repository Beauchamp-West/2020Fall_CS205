#include "cnn.h"
#include "face_binary_cls.cpp"
#include <chrono>

int main() {
    Mat origin;
    origin = imread("../image/face1.jpeg");
//    cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;

    cout << "Asian_man_face, ";
    auto start0 = std::chrono::steady_clock::now();

//    for (int i = 0; i < 10; ++i) {
        auto *data = new float[origin.total() * 3];
        convert2float(origin, data);
        Image image(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
            image.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                       conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
//            auto inter1 = std::chrono::steady_clock::now();
//            auto dur0 = std::chrono::duration_cast<std::chrono::milliseconds>(inter1 - inter0).count();
//            cout << "convolution costs " << dur0 << " ms, ";

            image.reLU();
//            auto inter2 = std::chrono::steady_clock::now();
//            auto dur1 = std::chrono::duration_cast<std::chrono::milliseconds>(inter2 - inter1).count();
//            cout << "reLU costs " << dur1 << " ms, ";

            if (j < 2) image.max_pool(); //最后一次不需要池化
//            auto inter3 = std::chrono::steady_clock::now();
//            auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(inter3 - inter2).count();
//            cout << "max pooling costs " << dur2 << " ms, ";
        }

//全连接
        image.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image.softmax();

    auto end0 = std::chrono::steady_clock::now();
    auto duration0 = std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0).count();


//展示结果
        image.show();
//        cout << endl;
    cout << "duration = " << duration0 << "ms\n";
//    }



    origin = imread("../image/face2.jpeg");
//    for (int i = 0; i < 10; ++i) {
        data = new float[origin.total() * 3];
        convert2float(origin, data);
        Image image0(origin.rows, origin.cols, origin.channels(), data);

        cout << "white_woman_face, ";
        auto start = std::chrono::steady_clock::now();

//3次卷积操作
        for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
            image0.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                        conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);

//            auto inter1 = std::chrono::steady_clock::now();
//            auto dur0 = std::chrono::duration_cast<std::chrono::milliseconds>(inter1 - inter0).count();
//            cout << "convolution costs " << dur0 << " ms, ";


            image0.reLU();
//            auto inter2 = std::chrono::steady_clock::now();
//            auto dur1 = std::chrono::duration_cast<std::chrono::milliseconds>(inter2 - inter1).count();
//            cout << "reLU costs " << dur1 << " ms, ";

            if (j < 2) image0.max_pool(); //最后一次不需要池化

//            auto inter3 = std::chrono::steady_clock::now();
//            auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(inter3 - inter2).count();
//            cout << "max pooling costs " << dur2 << " ms, ";
        }

//全连接
        image0.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
        image0.softmax();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//展示结果
        image0.show();
//        cout << endl;


    cout << "duration = " << duration << "ms\n";
//    }


    origin = imread("../image/face0.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "white_woman_profile, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image1(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image1.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image1.reLU();
        if (j < 2) image1.max_pool(); //最后一次不需要池化
    }

//全连接
    image1.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image1.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


//展示结果
    image1.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";


    origin = imread("../image/face3.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "Asian_woman_profile(small), ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image3(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image3.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image3.reLU();
        if (j < 2) image3.max_pool(); //最后一次不需要池化
    }

//全连接
    image3.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image3.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


//展示结果
    image3.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/face4.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "partly_covered_face, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image4(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image4.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image4.reLU();
        if (j < 2) image4.max_pool(); //最后一次不需要池化
    }
//全连接
    image4.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image4.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image4.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/face5.jpg");

//    for (int i = 0; i < 10; ++i) {

    cout << "black_woman_profile, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image5(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image5.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image5.reLU();
        if (j < 2) image5.max_pool(); //最后一次不需要池化
    }
//全连接
    image5.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image5.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image5.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }




    origin = imread("../image/face6.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "old_man_face, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image6(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image6.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image6.reLU();
        if (j < 2) image6.max_pool(); //最后一次不需要池化
    }
//全连接
    image6.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image6.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image6.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/face7.jpg");

//    for (int i = 0; i < 10; ++i) {

    cout << "Asian_man_profile, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image7(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image7.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image7.reLU();
        if (j < 2) image7.max_pool(); //最后一次不需要池化
    }
//全连接
    image7.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image7.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image7.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/face8.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "Asian_woman_face, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image8(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image8.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image8.reLU();
        if (j < 2) image8.max_pool(); //最后一次不需要池化
    }
//全连接
    image8.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image8.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image8.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }


    origin = imread("../image/face9.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "black_man_face, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image9(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image9.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image9.reLU();
        if (j < 2) image9.max_pool(); //最后一次不需要池化
    }
//全连接
    image9.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image9.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image9.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/face10.jpg");

//    for (int i = 0; i < 10; ++i) {

    cout << "cartoon_man_profile, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image10(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image10.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image10.reLU();
        if (j < 2) image10.max_pool(); //最后一次不需要池化
    }
//全连接
    image10.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image10.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image10.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/bg1.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "mountain&river, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image11(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image11.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image11.reLU();
        if (j < 2) image11.max_pool(); //最后一次不需要池化
    }
//全连接
    image11.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image11.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image11.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/bg2.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "sky&grassland, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image12(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image12.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image12.reLU();
        if (j < 2) image12.max_pool(); //最后一次不需要池化
    }
//全连接
    image12.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image12.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image12.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/bg3.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "building, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image14(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image14.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image14.reLU();
        if (j < 2) image14.max_pool(); //最后一次不需要池化
    }
//全连接
    image14.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image14.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image14.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }



    origin = imread("../image/bg4.jpeg");

//    for (int i = 0; i < 10; ++i) {

    cout << "Apple_logo&aurora, ";
//        cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    data = new float[origin.total() * 3];

    start = std::chrono::steady_clock::now();

    convert2float(origin, data);
    Image image15(origin.rows, origin.cols, origin.channels(), data);

//3次卷积操作
    for (int j = 0; j < 3; ++j) {
//            auto inter0 = std::chrono::steady_clock::now();
        image15.conv(conv_params[j].out_channels, conv_params[j].in_channels, conv_params[j].kernel_size,
                    conv_params[j].pad, conv_params[j].stride, conv_params[j].p_weight, conv_params[j].p_bias);
        image15.reLU();
        if (j < 2) image15.max_pool(); //最后一次不需要池化
    }
//全连接
    image15.fc(fc_params->out_features, fc_params->p_weight, fc_params->p_bias);
    image15.softmax();

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image15.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }

    return 0;
}


