#include "cnn.h"

int main() {
    Mat origin;
    origin = imread("/Users/leolu/Downloads/C++/SimpleCNNbyCPP/samples/face.jpg");
    cout << origin.total() << endl;
    cout << origin.channels() << endl;

    auto * data = new float[origin.total()*3];
    convertToFloat(origin,data);
    Image layer0(origin.rows,origin.cols,origin.channels(),data);

    delete [] data;
//    waitKey(0);
    return 0;
}

