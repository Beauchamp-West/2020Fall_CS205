//
// Created by 陆彦青 on 2020/10/30.
//

#include <iostream>
#include "functions.h"
#include <immintrin.h>
#include <omp.h>
#include <cstring>
#include <thread>

using namespace std;

//向量点乘
float vectorCompute(float * v1, float * v2, size_t length){
    float sum[8] = {0},re = 0;
    __m256 a, b;
    __m256 c = _mm256_setzero_ps();
    size_t n = length - length % 8;
//#pragma omp parallel for
    for (size_t i = 0; i < n; i+=8)
    {
        a = _mm256_load_ps(v1 + i);
        b = _mm256_load_ps(v2 + i);
        c = _mm256_add_ps(c, _mm256_mul_ps(a, b));
    }
    _mm256_store_ps(sum, c);

    if (n != length){
        for (int i = n; i < length; ++i)
            re += v1[i] * v2[i];
    }
    return (sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]+re);
}
//解决线程冲突的向量点乘
float vectorCompute1(float * v1, float * v2, size_t length){
    size_t n = length - length % 8;
    float *sum = new float[n](),re = 0, res = 0;
    __m256 *a = new __m256[n], *b = new __m256[n], *tmp =new __m256[n];
    __m256 c = _mm256_setzero_ps();

#pragma omp parallel
    {
#pragma omp for
        for (size_t i = 0; i < n; i += 8) {
            a[i] = _mm256_load_ps(v1 + i);
            b[i] = _mm256_load_ps(v2 + i);
            tmp[i] = _mm256_mul_ps(a[i], b[i]);
            _mm256_store_ps(&sum[i], tmp[i]);
        }
    }

    delete [] a;
    delete [] b;
    delete [] tmp;

    for (size_t i = 0; i < n; ++i)
        res += sum[i];


    if (n != length){
        for (int i = n; i < length; ++i)
            re += v1[i] * v2[i];
    }

    delete [] sum;

    return (res+re);
}
//未转置的矩阵乘法
void matrixCompute(const matrix &m1, const matrix &m2, matrix &m3){
    if (m1.column != m2.row)
        cout << "These 2 matrices cannot be multiplied" << endl;
    else {
        size_t n = m1.row * m2.column;
        auto *v2 = new float [m1.column];

//        #pragma omp parallel for
        for (size_t i = 0; i < n; ++i) {
            size_t r = i / m2.column, c = i % m2.column;

            for (int j = 0; j < m1.column; ++j)
                v2[j] = m2.data[c + j * m2.column];

            m3.data[i] = vectorCompute(&m1.data[r * m1.column], v2, m1.column);
        }

        delete[] v2;
    }
}
//转置后的矩阵乘法
void matrixCompute_t(const matrix &m1, const matrix &m2, matrix &m3){
    if (m1.column != m2.column)
        cout << "These 2 matrices cannot be multiplied" << endl;
    else {
        size_t n = m1.row * m2.row;

        #pragma omp parallel for
        for (size_t i = 0; i < n; ++i) {
            size_t r = i / m2.row, c = i % m2.row;

            m3.data[i] = vectorCompute(&m1.data[r * m1.column], &m2.data[c * m2.column], m1.column);
//            cout << m3.data[i];
        }
    }
}
//子矩阵的乘法
void subMatrixCompute(const matrix &m1, const matrix &m2, size_t start, size_t end, matrix &m3)
{
    for (size_t i = start; i < end; ++i) {
        size_t r = i / m2.row, c = i % m2.row;

        m3.data[i] = vectorCompute(&m1.data[r * m1.column], &m2.data[c * m2.column], m1.column);
    }
}
//利用thread的多线程矩阵乘法
void matrixCompute_thread(const matrix &m1, const matrix &m2, matrix &m3)
{
    size_t len = m1.row * m2.row;
    size_t n = len / 8;
    //8线程
    thread t1(subMatrixCompute,ref(m1),ref(m2),0,n,ref(m3));
    thread t2(subMatrixCompute,ref(m1),ref(m2),n,2*n,ref(m3));
    thread t3(subMatrixCompute,ref(m1),ref(m2),2*n,3*n,ref(m3));
    thread t4(subMatrixCompute,ref(m1),ref(m2),3*n,4*n,ref(m3));
    thread t5(subMatrixCompute,ref(m1),ref(m2),4*n,5*n,ref(m3));
    thread t6(subMatrixCompute,ref(m1),ref(m2),5*n,6*n,ref(m3));
    thread t7(subMatrixCompute,ref(m1),ref(m2),6*n,7*n,ref(m3));
    thread t8(subMatrixCompute,ref(m1),ref(m2),7*n,8*n,ref(m3));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    subMatrixCompute(m1,m2,8*n,len,m3);
}
//展示矩阵
void showMatrix(matrix &m){
    for (int i = 0; i <m.row; ++i) {
        for (int j = 0; j < m.column; ++j) {
            cout << m.data[i*m.column+j] << ' ';
        }
        cout << "\n";
    }
}
//初始化矩阵
void init(matrix *m3, matrix *m1, matrix *m2){
    m3->row = m1->row;
    m3->column = m2->column;
    m3->data = new float [m3->row*m3->column]();
}
//删除矩阵
void del(matrix *m){
    delete [] m->data;
    delete m;
}
//矩阵转置
void trans(matrix &m){
    unsigned int tmp = m.column;
    m.column = m.row;
    m.row = tmp;

    auto * org = new float[m.column*m.row];
    memcpy(org,m.data,m.column*m.row*sizeof(float));

    for (int i = 0; i < m.row; ++i) {
#pragma omp parallel for
        for (int j = 0; j < m.column; ++j) {
            m.data[i*m.column+j] = org[j*m.row+i];
        }
    }

    delete [] org;
}
//矩阵输入
void inputMatrix(matrix &m)
{
    cout << "Please input the rows and columns: ";
    cin >> m.row >> m.column;

    size_t len = m.column*m.row;
    m.data = new float [len]();

    cout << "Please input the data: " << endl;
    for (int i = 0; i < len; ++i) {
        cin >> m.data[i];
    }
}
//行列式
double det(float *data, unsigned int row, unsigned int column)
{
    if (row != column) return 0;
    if (row == 1) return data[0];

    short flag,add;
    auto *data1 = new float [(row-1)*(row-1)];
    double sum;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < row-1; ++j) {
            add = i > j ? 0 : 1; //划去第i行后子矩阵的前i-1行对应原矩阵前i-1行，而之后的行数+1
            for (int k = 0; k < row-1; ++k) {
                data1[j*(row-1)+k] = data[(j+add)*row+k+1];
            }
        }
        flag = i % 2 == 0 ? 1 : -1;
        sum += flag * data[i*row] * det(data1, row-1, row-1);
    }

    delete [] data1;
//    cout << sum << endl;
    return sum;
}
//矩阵求逆
void inverse(matrix &m)
{
    double detOfm = det(m.data,m.row,m.column);
    if (detOfm == 0)
    {
        cout << "This matrix does not have the inverse" << endl;
        return;
    }

    auto *inv = new float[m.row*m.column]();
    auto *sub = new float[(m.row-1)*(m.column-1)]();
    int add1,add2,flag;
    for (unsigned int i = 0; i < m.column*m.row; ++i) {
        unsigned int r = i/m.row, c = i%m.row; //对应伴随矩阵第r行，第c列的元素(原矩阵第c行，第r列的代数余子式)
        for (int j = 0; j < m.row-1; ++j) {
            for (int k = 0; k < m.row-1; ++k) {
                add1 = c > j ? 0 : 1; //划去第c行后子矩阵的前c-1行对应原矩阵前c-1行，而之后的行数+1
                add2 = r > k ? 0 : 1; //划去第r列后子矩阵的前r-1列对应原矩阵前r-1列，而之后的列数+1
                sub[j*(m.row-1)+k] = m.data[(j+add1)*m.row+k+add2];
            }
        }

        flag = ((r+c) % 2 == 0) ? 1 : -1;
        inv[i] = flag /detOfm * det(sub,m.row-1,m.column-1);
    }

    delete [] m.data;
    m.data = inv;
    delete [] sub;
}