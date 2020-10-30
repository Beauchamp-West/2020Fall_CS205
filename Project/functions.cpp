//
// Created by 陆彦青 on 2020/10/30.
//

#include <iostream>
#include "functions.h"
#include <immintrin.h>

using namespace std;

float vectorCompute(float * v1, float * v2, size_t length){
    float sum[8] = {0},re = 0;
    __m256 a, b;
    __m256 c = _mm256_setzero_ps();
    int n = length - length % 8;

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

void matrixCompute(matrix &m1, matrix &m2, matrix &m3){
    if (m1.column != m2.row)
        cout << "These 2 matrices cannot be multiplied" << endl;
    else {
        long n = m1.row * m2.column;
        auto *v2 = new float [m1.column];

        for (long i = 0; i < n; ++i) {
            long r = i / m2.column, c = i % m2.column;

            for (int j = 0; j < m1.column; ++j)
                v2[j] = m2.data[c + j * m2.column];

            m3.data[i] = vectorCompute(&m1.data[r * m1.column],v2,m1.column);
        }

        delete [] v2;
    }
}
