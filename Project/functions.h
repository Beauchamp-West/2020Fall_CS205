//
// Created by 陆彦青 on 2020/10/30.
//

#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

#include <iostream>
using namespace std;
struct matrix{
    matrix(unsigned int r, unsigned int c) { //构造函数
        row = r;
        column = c;
        data = new float [r*c](); //元素按行主序存储
    }
    matrix() = default; //默认构造函数
    unsigned int row{};
    unsigned int column{};
    float *data{};
};

void matrixCompute(const matrix &m1, const matrix &m2, matrix &m3); //矩阵乘
void matrixCompute_t(const matrix &m1, const matrix &m2, matrix &m3); //m2转置后的矩阵乘
float vectorCompute(float * v1, float * v2, size_t n); //向量点乘
float vectorCompute1(float * v1, float * v2, size_t n); //解决多线程冲突的点乘
void subMatrixCompute(const matrix &m1, const matrix &m2, size_t start, size_t end, matrix &m3); //部分矩阵乘
void matrixCompute_thread(const matrix &m1, const matrix &m2, matrix &m3); // 使用thread的矩阵乘
void showMatrix(matrix &m); //打印出矩阵
void init(matrix *m3, matrix *m1, matrix *m2); //初始化矩阵
void del(matrix *m); //删除矩阵
void trans(matrix &m); //转置矩阵
void inputMatrix(matrix &m); //输入矩阵
double det(float *data, unsigned int row, unsigned int column); //求行列式
void inverse(matrix &m); //矩阵求逆

#endif //PROJECT_FUNCTIONS_H
