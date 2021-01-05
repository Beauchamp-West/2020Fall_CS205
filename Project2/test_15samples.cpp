#include "cnn.h"
#include <chrono>

int main() {
    Mat origin;
    origin = imread("../image/face.jpg");
//    cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;

    cout << "sample face, ";

//    for (int i = 0; i < 10; ++i) {
    auto *data = new float[origin.total() * 3];
    convert2float(origin, data);
    Image image(origin.rows, origin.cols, origin.channels(), data);

    auto start0 = std::chrono::steady_clock::now();

    image.forward(conv_params,fc_params,3);

    auto end0 = std::chrono::steady_clock::now();
    auto duration0 = std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0).count();


//展示结果
    image.show();
//        cout << endl;
    cout << "duration = " << duration0 << "ms\n";
//    }



    origin = imread("../image/face1.jpeg");
//    cout << "channels*rows*cols = " << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;

    cout << "Asian_man_face, ";

//    for (int i = 0; i < 10; ++i) {
        data = new float[origin.total() * 3];
        convert2float(origin, data);
        Image image20(origin.rows, origin.cols, origin.channels(), data);

    start0 = std::chrono::steady_clock::now();

        image20.forward(conv_params,fc_params,3);

    end0 = std::chrono::steady_clock::now();
    duration0 = std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0).count();


//展示结果
        image20.show();
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

        image0.forward(conv_params,fc_params,3);

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

    image1.forward(conv_params,fc_params,3);

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

    image3.forward(conv_params,fc_params,3);

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

    image4.forward(conv_params,fc_params,3);

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

    image5.forward(conv_params,fc_params,3);

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

    image6.forward(conv_params,fc_params,3);

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

    image7.forward(conv_params,fc_params,3);

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

    image8.forward(conv_params,fc_params,3);

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

    image9.forward(conv_params,fc_params,3);

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

    image10.forward(conv_params,fc_params,3);

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

    image11.forward(conv_params,fc_params,3);

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

    image12.forward(conv_params,fc_params,3);

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

    image14.forward(conv_params,fc_params,3);

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

    image15.forward(conv_params,fc_params,3);

    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

//展示结果
    image15.show();
//    cout << endl;
    cout << "duration = " << duration << "ms\n";
//    }

    return 0;
}