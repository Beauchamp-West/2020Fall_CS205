#include <iostream>
#include "matrix.hpp"
#include <chrono>

using namespace std;

int main() {
    //初始化2个矩阵
    matrix m1(10,20000000), m2(20000000,10);
    m1[0]=2.5f;
    m2[0]=3;
    m1[20000000]=1.5f;
    cout << "m1 is 10 * 200000\n";
    cout << "m2 is 200000 * 10\n";

    //矩阵相乘测试
    auto start = std::chrono::steady_clock::now();
    matrix m3 = m1*m2;
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "m3 = m1 * m2, m3 =\n";
    cout << m3;
    cout << "duration = " << duration << "ms" << std::endl;

    //矩阵与标量相乘测试
    m3 *= 2;
    cout << "m3 *= 2, m3 =\n";
    cout << m3;
    m3 = 0.5*m3;
    cout << "m3 = 0.5 * m3 =\n";
    cout << m3;

    //计算行列式
    matrix m4 = matrix::identity(2);
    cout << "m4 =\n";
    cout << m4;
    cout << "The determinant of an identity matrix is " << m4.det() << endl;

    //求逆测试
    matrix m5(2,2);
    m5[0] = 1;
    m5[1] = 1;
    m5[3] = 1;
    cout << "m5 =\n";
    cout << m5;
    matrix m6 = matrix::inverse(m5);
    cout << "m6 = the inverse of m5 =\n";
    cout << m6;

    //转置测试
    m5.trans();
    cout << "The transpose of m5 =\n";
    cout << m5;

    //矩阵输入测试
    matrix m7;
    cin >> m7;
    cout << "m7 =\n";
    cout << m7;

    //其他运算符测试
    matrix m8(2,2);
    m8[0] = 1;
    m8[1] = 2;
    m8[2] = 3;
    m8[3] = 4;
    cout << "m8 =\n";
    cout << m8;
    if (m8==m7) {
        cout << "m8 and m7 are identical" << endl;
    } else {
        cout << "m8 and m7 are not identical" << endl;
    }

    m7 += m8;
    cout << "m7 += m8, m7 =\n";
    cout << m7;
    m8 = m7 - m4;
    cout << "m8 = m7 - m4, m8 =\n";
    cout << m8;

    return 0;
}
