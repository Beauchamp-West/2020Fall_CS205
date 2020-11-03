//
// Created by 陆彦青 on 2020/10/30.
//

#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

struct matrix{
    matrix(int r, int c) { //构造函数
        row = r;
        column = c;
        data = new float [r*c](); //元素按行主序存储
    }
    matrix() = default; //默认构造函数

    int row{};
    int column{};
    float *data{};
};

void matrixCompute(const matrix &m1, const matrix &m2, matrix &m3); //矩阵乘
float vectorCompute(float * v1, float * v2, size_t n); //向量点乘
void showMatrix(matrix &m); //打印出矩阵
void init(matrix &m3, matrix &m1, matrix &m2); //初始化矩阵
void del(matrix *m); //删除矩阵
void trans(matrix &m); //转置矩阵
void matrixCompute_t(const matrix &m1, const matrix &m2, matrix &m3); //m2转置后的矩阵乘
void inputMatrix(matrix &m); //输入矩阵
float vectorCompute1(float * v1, float * v2, size_t n); //解决多线程冲突的点乘

#endif //PROJECT_FUNCTIONS_H
