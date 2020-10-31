//
// Created by 陆彦青 on 2020/10/1.
//

#include <iostream>
#include <string>
#include <chrono>
#include <cstdio>
#include <thread>
#include </usr/local/Cellar/openblas/0.3.10_1/include/cblas.h>
using namespace std;

float* read(const char* fileName){ //将生成的数组读入存入vector
    FILE *fp;
    float *vec;
    vec = new float[200000000];
    fp = fopen(fileName, "rb"); // 以二进制读取的形式打开
    fread(vec,sizeof(float), 200000000, fp); // 二进制读
    fclose(fp);

    return vec;
}

float *v1,*v2; // 向量定义为全局变量，防止栈内存不足，以及方便多个函数中引用

string add(string& a, string& b){ //高精度加法
    string sub(string& a, string b);
    string str;
    if (a[0] == '-'){
        if (b[0] == '-'){
            str = '-'+ add(a.erase(0,1),b.erase(0,1));
            return str;
        } else {
            return sub(b,a.erase(0,1));
        }
    } else {
        if (b[0] == '-'){
            return sub(a,b.erase(0,1));
        } else {
            string :: size_type a_int = a.find('.'),b_int = b.find('.'); //比较整数、小数部分，补0
            string :: size_type a_dec,b_dec;
            if (a_int == string::npos){
                a_int = a.size();
                a_dec = 0;
            } else {
                a_dec = a.size()-a_int-1;
            }
            if (b_int == string::npos){
                b_int = b.size();
                b_dec = 0;
            } else {
                b_dec = b.size()-b_int-1;
            }
            if (a_int > b_int){
                for (int i = 0; i < a_int-b_int; ++i)
                    b = '0' + b;
            } else if (a_int < b_int){
                for (int i = 0; i < b_int-a_int; ++i)
                    a = '0' + a;
            }
            if (a_dec > b_dec){
                if (b_dec == 0) b += '.';
                for (int i = 0; i < a_dec-b_dec; ++i)
                    b += '0';
            } else if (a_dec < b_dec){
                if (a_dec == 0) a += '.';
                for (int i = 0; i < b_dec-a_dec; ++i)
                    a += '0';
            }

            int carry = 0,res;
            for (int i = a.size()-1; i > -1; --i) {
                if (a[i] == '.'){
                    str = '.' + str;
                } else {
                    res = (a[i] - '0' + b[i] - '0' + carry) % 10;
                    carry = (a[i] - '0' + b[i] - '0' + carry) / 10;
                    str = char(res + '0') + str;
                }
            }
            if (carry != 0) str = char(carry + '0') + str;

            return str;
        }
    }
}
string sub(string& a, string b){ //高精度减法
    string str;
    if (b[0] == '-'){
        return add(a,b.erase(0,1));
    } else {
        if (a[0] == '-'){
            str = '-' + add(a.erase(0,1),b);
            return str;
        } else {
            if (stod(a) < stod(b)) return '-' + sub(b,a);
            else {
                string::size_type a_int = a.find('.'), b_int = b.find('.'); //比较整数、小数部分，补0
                string::size_type a_dec, b_dec;
                if (a_int == string::npos) {
                    a_int = a.size();
                    a_dec = 0;
                } else {
                    a_dec = a.size() - a_int - 1;
                }
                if (b_int == string::npos) {
                    b_int = b.size();
                    b_dec = 0;
                } else {
                    b_dec = b.size() - b_int - 1;
                }
                if (a_int > b_int) {
                    for (int i = 0; i < a_int - b_int; ++i)
                        b = '0' + b;
                } else if (a_int < b_int) {
                    for (int i = 0; i < b_int - a_int; ++i)
                        a = '0' + a;
                }
                if (a_dec > b_dec) {
                    if (b_dec == 0) b += '.';
                    for (int i = 0; i < a_dec - b_dec; ++i)
                        b += '0';
                } else if (a_dec < b_dec) {
                    if (a_dec == 0) a += '.';
                    for (int i = 0; i < b_dec - a_dec; ++i)
                        a += '0';
                }

                int carry = 0, res;
                for (int i = a.size() - 1; i > 0; --i) {
                    char c = a[i], d = b[i];
                    if (a[i] == '.') {
                        str = '.' + str;
                    } else {
                        res = c - d - carry;
                        if (res < 0) {
                            res += 10;
                            carry = 1;
                        } else carry = 0;
                        str = char(res + '0') + str;
                    }
                }
                if (a[0] != '.') {
                    res = a[0] - b[0] - carry;
                    str = to_string(res) + str;
                } else if (carry == 0) {
                    str = "0." + str;
                } else {
                    str = "-1." + str;
                }
                return str;
            }
        }
    }
}

void lcompute(const int &a,const int &b,long double &result){ // 用long double计算
    long double init;
    for (int i = a; i < b; ++i) {
        init = (long double)v1[i]*v2[i];
        result += init;
    }
}
void compute(const int &a,const int &b,string &result) { // 高精度计算
    string init = "0";
    for (int i = a; i < b; ++i) {
        init = to_string(double(v1[i]) * v2[i]);
        result = add(init, result);
    }
}
void fcompute(const int &a,const int &b,float &result){ //用float计算
    float init;
    for (int i = a; i < b; ++i) {
        init = v1[i]*v2[i];
        result += init;
    }
}

int main(){
    auto start1 = chrono::system_clock::now();

    const char * name1 = "data1";
    const char * name2 = "data3";
    v1 = read(name1), v2 = read(name2);

    auto end1 = chrono::system_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
    cout << "The reading costs " << duration1.count() <<"ms" << endl;

    auto start = chrono::system_clock::now();

    float res = cblas_sdot(200000000,v1,1,v2,1); // 与OpenBLAS中cblas_sdot()函数比较
    cout << fixed;
    cout << res << endl;

    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "openBLAS costs " << duration.count() <<"ms" << endl;

    auto start2 = chrono::system_clock::now();
    long double result[8]={0};
    long double res0=0;
    long double res9=0;
    thread t1(lcompute,0,25000000,ref(result[0])); // 8线程
    thread t2(lcompute,25000000,50000000,ref(result[1]));
    thread t3(lcompute,50000000,75000000,ref(result[2]));
    thread t4(lcompute,75000000,100000000,ref(result[3]));
    thread t5(lcompute,100000000,125000000,ref(result[4]));
    thread t6(lcompute,125000000,150000000,ref(result[5]));
    thread t7(lcompute,150000000,175000000,ref(result[6]));
    thread t8(lcompute,175000000,200000000,ref(result[7]));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    for (long double & i : result) {
        res0 += i;
    }
//    compute(0,200000000,res0);

    cout << res0 << endl;


    auto end2 = chrono::system_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
    cout << "8 thread long double costs " << duration2.count() <<"ms" << endl;

    auto start3 = chrono::system_clock::now(); // 用long double类型存储计算结果

    lcompute(0,200000000,res9);
    cout << res9 << endl;

    auto end3 = chrono::system_clock::now();
    auto duration3 = chrono::duration_cast<chrono::milliseconds>(end3 - start3);
    cout << "long double costs " << duration3.count() <<"ms" << endl;

    delete [] v1;
    delete [] v2;
    return 0;
}