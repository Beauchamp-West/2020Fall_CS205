#include <iostream>
#include "functions.h"
#include </usr/local/Cellar/openblas/0.3.10_1/include/cblas.h>
#include <chrono>

using namespace std;

int main() {
    matrix m1(10,20000000), m2(20000000,10), m3;
    m1.data[0] = 2.5f;
    m2.data[0] = 2;
    m1.data[20000001] = 3;
    m2.data[10] = 5;
    m3.row = m1.row;
    m3.column = m2.column;
    long dataLength = m3.row * m3.column;
    m3.data = new float[dataLength];

    auto start = std::chrono::steady_clock::now();
    matrixCompute(m1,m2,m3);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "result =\n";
    for (int i = 0; i < m3.row; ++i) {
        for (int j = 0; j < m3.column; ++j) {
            cout << m3.data[i*m3.column+j] << ' ';
        }
        cout << "\n";
    }
    cout << "duration = " << duration << " ms" << std::endl;

    delete [] m1.data;
    delete [] m2.data;
    delete [] m3.data;

    return 0;
}
