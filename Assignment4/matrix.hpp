#pragma once
#include <iostream>

using namespace std;

class matrix {
private:

    size_t num; //元素个数
    size_t row{};
    size_t column{};
    float *data{};
    int flag = 0;
public:
    matrix();
    matrix(size_t, size_t);
    matrix(matrix &);
    ~matrix();

    matrix & operator=(const matrix &);
    matrix & operator+(const matrix &);
    matrix & operator-(const matrix &);
    matrix & operator*(matrix &);
    matrix & operator*(float);
    void operator*=(float);
    void operator*=(matrix &);
    void operator+=(matrix &);
    void operator-=(matrix &);
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

float vectorCompute(const float *, const float *v2, size_t); //向量点乘
void subMatrixCompute(matrix &, matrix &, size_t, size_t, matrix &);