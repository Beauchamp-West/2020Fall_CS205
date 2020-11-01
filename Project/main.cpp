#include <iostream>
#include "functions.h"
#include </usr/local/Cellar/openblas/0.3.10_1/include/cblas.h>
#include <chrono>

using namespace std;

int main() {
    //初始化3个矩阵
    auto m1 = new matrix(10,2000000), m2 = new matrix(2000000,10), m3 = new matrix();
    (*m1).data[0] = 2.5f;
    (*m2).data[0] = 2;
    (*m1).data[2000001] = 3;
    (*m2).data[10] = 5;
    init(*m3,*m1,*m2);

//    auto start = std::chrono::steady_clock::now();
//    //自定义的矩阵乘法
//    matrixCompute(*m1,*m2,*m3);
//
//    auto end = std::chrono::steady_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    cout << "result =\n";
//    showMatrix(*m3);
//    cout << "duration = " << duration << " ms" << std::endl;

    trans(*m2);

    //m2转置后的矩阵乘法
    auto start0 = std::chrono::steady_clock::now();
    matrixCompute_t(*m1,*m2,*m3);

    auto end0 = std::chrono::steady_clock::now();
    auto duration0 = std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0).count();
    cout << "result =\n";
    showMatrix(*m3);
    cout << "transpose duration = " << duration0 << " ms" << std::endl;

    //openblas中的矩阵乘法
    auto start1 = std::chrono::steady_clock::now();
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasTrans,10,10,2000000,
                1,(*m1).data,2000000,(*m2).data,2000000,0,(*m3).data,10);

    auto end1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    cout << "cblas result =\n";
    showMatrix(*m3);
    cout << "duration = " << duration1 << " ms" << std::endl;

    //删除矩阵释放内存
    del(m1);
    del(m2);
    del(m3);

    return 0;
}
