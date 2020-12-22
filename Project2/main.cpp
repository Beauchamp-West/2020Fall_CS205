#include "cnn.h"
#include "face_binary_cls.cpp"

int main() {
    Mat origin;
    origin = imread("/Users/leolu/Downloads/C++/SimpleCNNbyCPP/samples/bg.jpg");
    cout << origin.channels() << "*" << origin.rows << "*" << origin.cols << endl;
    auto * data = new float[origin.total()*3];
    convert2float(origin,data);
    Image image(origin.rows,origin.cols,origin.channels(),data);

//3次卷积操作
    for (int i = 0; i < 3; ++i) {
        image.conv(conv_params[i].out_channels,conv_params[i].in_channels,conv_params[i].kernel_size,
                   conv_params[i].pad,conv_params[i].stride,conv0_weight,conv0_bias);
//        cout << "conv " << i << endl;
//        image.show();

        image.reLU();
//        cout << "reLU " << i << endl;
//        image.show();

        image.max_pool();
//        cout << "max " << i << endl;
//        image.show();
    }
//全连接
    image.fc(fc_params->out_features,fc0_weight,fc0_bias);
//展示结果
    image.show();
//    Layers<3> layers0(origin.rows,origin.cols);
//    layers0.init(origin);
//
//    Layers<16> layers1(origin.rows/2,origin.cols/2);
//    Layers<32> layers2(origin.rows/4,origin.cols/4);
//    Layers<32> layers3(origin.rows/8,origin.cols/8);
//    for (int i = 0; i < origin.rows; ++i)
//        delete [] data[i];
//    delete [] data;

    return 0;
}


