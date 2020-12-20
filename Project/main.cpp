#include <iostream>
#include "functions.h"
#include "/usr/local/Cellar/openblas/0.3.10_1/include/cblas.h"
#include <chrono>

using namespace std;

int main() {
    //初始化6个矩阵
    auto m1 = new matrix(10,20000000), m2 = new matrix(20000000,10), m3 = new matrix();
    m1->data[0] = 2.5f;
    m2->data[0] = 2;
    m1->data[200001] = 3;
    m2->data[10] = 5;
    init(m3,m1,m2);
    //m4,m6相同
    auto m4 = new matrix(2,2), m6 = new matrix(2,2), m5 = new matrix();
    m4->data[0] = 1;
    m4->data[1] = 1;
    m4->data[2] = 0;
    m4->data[3] = 2;
    m6->data[0] = 1;
    m6->data[1] = 1;
    m6->data[2] = 0;
    m6->data[3] = 2;
    init(m5,m4,m6);

    //求逆测试
//    trans(*m6);
//    cout << "transpose of m6:\n";
//    showMatrix(*m6);
//    inverse(*m4);
//    cout << "inverse of m4:\n";
//    showMatrix(*m4);
//    matrixCompute_t(*m4,*m6,*m5);
//    cout << "m4^{-1} * m6 = \n";
//    showMatrix(*m5);

    //自定义的矩阵乘法
//    auto start = std::chrono::steady_clock::now();
//
//    matrixCompute(*m1,*m2,*m3);
//
//    auto end = std::chrono::steady_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    cout << "result =\n";
//    showMatrix(*m3);
//    cout << "duration = " << duration << " ms" << std::endl;

    //将m2转置
    trans(*m2);

    //使用thread的矩阵乘法
    auto start = std::chrono::steady_clock::now();
    matrixCompute_thread(*m1,*m2,*m3);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "result =\n";
    showMatrix(*m3);
    cout << "thread duration = " << duration << " ms" << std::endl;

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
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasTrans,10,10,20000000,
                1,(*m1).data,20000000,(*m2).data,20000000,0,(*m3).data,10);

    auto end1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    cout << "cblas result =\n";
    showMatrix(*m3);
    cout << "duration = " << duration1 << " ms" << std::endl;

    //输入矩阵测试
//    auto m4 = new matrix();
//    inputMatrix(*m4);
//    showMatrix(*m4);

    //删除矩阵释放内存
    del(m1);
    del(m2);
    del(m3);
    del(m4);
    del(m5);
    del(m6);
    return 0;
}
