//
// Created by 陆彦青 on 2020/11/23.
//
#include "matrix.hpp"
#include <immintrin.h>
#include <arm_neon.h>
#include <omp.h>

using namespace std;

size_t matrix::count = 1;

matrix::matrix() {
    num = count;
//    cout << "default matrix m" << num << " created" << endl;
    count++;

    row = 0;
    column = 0;
    data = nullptr;
}

matrix::matrix(const matrix &m) {
    row = m.row;
    column = m.column;
    data = new float[row*column];

#pragma omp parallel for
    for (size_t i = 0; i < row*column; ++i) {
        data[i] = m.data[i];
    }

    if (m.flag == 0) {
        num = count;
//        cout << "matrix m" << num << " created by copying matrix m" << m.num << endl;
        count++;
    } else {
        num = m.num;
        delete &m;
    }
}

matrix::matrix(const matrix &m1, const matrix &m2) {
    row = m1.row;
    column = m2.column;
    data = new float[row * column]();

    if (m1.flag == 0 && m2.flag == 0) {
        num = count;
//        cout << "matrix m" << num << " created by assigning matrix m" << m1.num << " and m" << m2.num << endl;
        count++;
    } else {
        if (m1.flag != 0) {
            num = 0;
            delete &m1;
        }
        if (m2.flag != 0) {
            num = 0;
            delete &m2;
        }
    }
}

matrix::matrix(size_t r, size_t c) {
    num = count;
//    cout << "matrix m" << num <<" created with row " << r << " and column " << c << endl;
    count++;

    row = r;
    column = c;
    data = new float[r * c]();
}

matrix::~matrix() {
    delete [] data;
//    --count;
//    if (flag == 0) cout << "matrix m" << num << " is deleted" << endl;
}

matrix & matrix::operator=(matrix &m) {
    if (this == &m) return *this;

    delete [] data;
    data = new float[m.column*m.row];
#pragma omp parallel for
    for (size_t i = 0; i < row*column; ++i) {
        data[i] = m.data[i];
    }

    row = m.row;
    column = m.column;

    if (m.flag != 0) {
        delete &m;
    }

    return *this;
}

matrix & matrix::operator+(const matrix &m) {
    if (row == m.row && column == m.column) {
        matrix *res = new matrix(*this);

#pragma omp parallel for
        for (size_t i = 0; i < row*column; ++i) {
            res->data[i] += m.data[i];
        }

        res->flag = 1;
        return *res;
    }
    else cout << "The matrix cannot be added" << endl;

}

matrix & matrix::operator-(const matrix &m) {
    if (row == m.row && column == m.column) {
        matrix *res = new matrix(*this);

#pragma omp parallel for
        for (size_t i = 0; i < row*column; ++i) {
            res->data[i] -= m.data[i];
        }

        res->flag = 1;
        return *res;
    }
    else cout << "The matrix cannot be subtracted" << endl;
}

matrix & matrix::operator*(matrix &m) {
    if (column == m.row) {
        matrix *res = new matrix(*this,m);
        m.trans();
        size_t n = row * m.row;

#pragma omp parallel for
        for (size_t i = 0; i < n; ++i) {
            size_t r = i / m.row, c = i % m.row;
            res->data[i] = vectorCompute(&data[r * column], &m.data[c * m.column], column);
        }

        res->flag = 1;
        return *res;
    }
    else cout << "The matrix cannot be multiplied" << endl;
}

matrix & matrix::operator*(float n) {
    matrix *res = new matrix(*this);

#pragma omp parallel for
    for (size_t i = 0; i < row*column; ++i) {
        res->data[i] *= n;
    }

    res->flag = 1;
    return *res;
}

matrix & matrix::operator*=(float n) {
#pragma omp parallel for
    for (size_t i = 0; i < row*column; ++i) {
        data[i] *= n;
    }
    return *this;
}

matrix & matrix::operator*=(matrix &m) {
    if (column == m.row) {
        matrix res(*this,m);
        m.trans();
        size_t n = row * m.row;

#pragma omp parallel for
        for (size_t i = 0; i < n; ++i) {
            size_t r = i / m.row, c = i % m.row;
            res.data[i] = vectorCompute(&data[r * column], &m.data[c * m.column], column);
        }

        *this = res;
        return *this;
    }
    else cout << "The matrix cannot be multiplied" << endl;
}

matrix & matrix::operator+=(matrix &m) {
    if (row == m.row && column == m.column) {

#pragma omp parallel for
        for (size_t i = 0; i < row*column; ++i) {
            data[i] += m.data[i];
        }
        return *this;
    }
    else cout << "The matrix cannot be added" << endl;
}
matrix & matrix::operator-=(matrix &m) {
    if (row == m.row && column == m.column) {

#pragma omp parallel for
        for (size_t i = 0; i < row*column; ++i) {
            data[i] -= m.data[i];
        }
        return *this;
    }
    else cout << "The matrix cannot be subtracted" << endl;
}

float & matrix::operator[](size_t i) {
    return data[i];
}

matrix & operator*(float n, matrix &m) {
    matrix *res = new matrix(m);

#pragma omp parallel for
    for (size_t i = 0; i < m.row*m.column; ++i) {
        res->data[i] *= n;
    }

    res->flag = 1;
    return *res;
}

bool operator==(const matrix &m1, const matrix &m2) {
    if (m1.row != m2.row || m1.column != m2.column) return false;

    for (size_t i = 0; i < m1.column*m1.row; ++i) {
        if (m1.data[i] != m2.data[i]) return false;
    }

    return true;
}

ostream & operator<<(ostream & os, matrix &m) {
//    os << "matrix m" << m.num << " is\n";
    for (int i = 0; i <m.row; ++i) {
        for (int j = 0; j < m.column; ++j) {
            os << m.data[i*m.column+j] << ' ';
        }
        os << "\n";
    }

    return os;
}

istream & operator>>(istream & is, matrix &m) {
    cout << "Please input the rows and columns: ";
    is >> m.row >> m.column;

    size_t len = m.column*m.row;
    delete [] m.data;
    m.data = new float [len];

    cout << "Please input the data: " << endl;
    for (int i = 0; i < len; ++i) {
        is >> m.data[i];
    }

    return is;
}
void matrix::trans(){
    size_t tmp = column;
    column = row;
    row = tmp;

    auto * org = new float[column*row];
#pragma omp parallel for
    for (size_t i = 0; i < row*column; ++i) {
        org[i] = data[i];
    }

    for (int i = 0; i < row; ++i) {
#pragma omp parallel for
        for (int j = 0; j < column; ++j) {
            data[i*column+j] = org[j*row+i];
        }
    }

    delete [] org;
}


//行列式
double matrix::det()
{
    if (row != column) return 0;
    if (row == 1) return data[0];

    short flag,add;
    matrix sub(row-1,row-1);
    double sum;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < row-1; ++j) {
            add = i > j ? 0 : 1; //划去第i行后子矩阵的前i-1行对应原矩阵前i-1行，而之后的行数+1
            for (int k = 0; k < row-1; ++k) {
                sub.setData(j*(row-1)+k,data[(j+add)*row+k+1]);
            }
        }
        flag = i % 2 == 0 ? 1 : -1;
        sum += flag * data[i*row] * sub.det();
    }

    return sum;
}
//矩阵求逆
matrix & matrix::inverse(matrix &m)
{
    double detOfm = m.det();
    if (detOfm == 0)
    {
        cout << "This matrix does not have the inverse" << endl;
        abort();
    }

    auto res = new matrix(m.row,m.column);

    matrix sub(m.row-1,m.column-1);
    int add1,add2,flag;
    for (size_t i = 0; i < m.column * m.row; ++i) {
        size_t r = i/m.row, c = i%m.row; //对应伴随矩阵第r行，第c列的元素(原矩阵第c行，第r列的代数余子式)
        for (int j = 0; j < m.row-1; ++j) {
            for (int k = 0; k < m.row-1; ++k) {
                add1 = c > j ? 0 : 1; //划去第c行后子矩阵的前c-1行对应原矩阵前c-1行，而之后的行数+1
                add2 = r > k ? 0 : 1; //划去第r列后子矩阵的前r-1列对应原矩阵前r-1列，而之后的列数+1
                sub[j*(m.row-1)+k] = m.data[(j+add1)*m.row+k+add2];
            }
        }

        flag = ((r+c) % 2 == 0) ? 1 : -1;

        float ele = sub.det() / detOfm * flag;
        res->data[i] =  ele == -0 ? 0 : ele;
    }
    m.flag = 1;

    return *res;
}

//构造n阶单位矩阵
matrix & matrix::identity(size_t n) {
    auto * m = new matrix(n,n);
    for (size_t i = 0; i < n; ++i) {
        m->data[i*n+i] = 1;
    }
    m->flag = 1;
    return *m;
}

//向量点乘(avx)
float vectorCompute(float * v1, float * v2, size_t length){
    float sum[8] = {0},re = 0;
    __m256 a, b;
    __m256 c = _mm256_setzero_ps();
    size_t n = length - length % 8;

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

//向量点乘()
float vectorCompute_arm(const float *v1, const float * v2, size_t length) {
    float sum[8] = {0}, re = 0;
    float32x4_t a, b;
    float32x4_t c = vdupq_n_f32(0);
    size_t n = length - length % 8;

    for (size_t i = 0; i < n; i+=8)
    {
        a = vld1q_f32(v1 + i);
        b = vld1q_f32(v2 + i);
        c =  vaddq_f32(c, vmulq_f32(a, b));
    }
    vst1q_f32(sum, c);

    if (n != length){
        for (int i = n; i < length; ++i)
            re += v1[i] * v2[i];
    }
    return (sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]+re);
}

//子矩阵的乘法
void subMatrixCompute(matrix &m1, matrix &m2, size_t start, size_t end, matrix &m3)
{
    for (size_t i = start; i < end; ++i) {
        size_t r = i / m2.getRow(), c = i % m2.getRow();
        float v = vectorCompute(m1.getData(r * m1.getColumn()), m2.getData(c * m2.getColumn()), m1.getColumn());
        m3.setData(i,v);
    }
}