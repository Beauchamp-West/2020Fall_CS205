#pragma once
#include <iostream>

using namespace std;

class matrix {
private:

    size_t num;
    static size_t count;
    size_t row{};
    size_t column{};
    float *data{};
    int flag = 0; //标志是否为临时
public:
    matrix();
    matrix(size_t, size_t);
    matrix(const matrix &);
    matrix(const matrix &, const matrix &);
    ~matrix();

    matrix & operator=(matrix &);
    matrix & operator+(const matrix &);
    matrix & operator-(const matrix &);
    matrix & operator*(matrix &);
    matrix & operator*(float);
    matrix & operator*=(float);
    matrix & operator*=(matrix &);
    matrix & operator+=(matrix &);
    matrix & operator-=(matrix &);
    float & operator[](size_t);

    void trans(); //转置矩阵
    double det(); //求行列式
    static matrix & inverse(matrix &); //矩阵求逆
    static matrix & identity(size_t); //生成n阶初等矩阵

    friend bool operator==(const matrix &, const matrix &);
    friend ostream & operator<<(ostream &, matrix &);
    friend istream & operator>>(istream &, matrix &);
    friend matrix & operator*(float, matrix &);

    size_t getRow() const {return row;};
    size_t getColumn() const {return column;};
    float *getData(size_t i) {return &data[i];};
    void setData(size_t i, float v) {data[i] = v;};
};

float vectorCompute(float *, float *v2, size_t); //向量点乘
float vectorCompute_arm(const float *p1, const float * p2, size_t length);
void subMatrixCompute(matrix &, matrix &, size_t, size_t, matrix &);