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
//    union trans
//    {
//        float a;
//        unsigned int b;
//    };

    FILE* fp;
    float *vec;
    vec = new float[200000000];
    fp = fopen(fileName, "rb"); // 以二进制读取的形式打开
    fread(vec,sizeof(float), 200000000, fp); // 二进制读
    fclose(fp);

    return vec;
}

float *v1,*v2; // 向量定义为全局变量，防止栈内存不足，以及方便多个函数中引用

void compute(const int &a,const int &b,double &result){
    double init;
    for (int i = a; i < b; ++i) {
        init = double(v1[i])*v2[i];
        result += init;
//        cout << res << endl;
    }
}
void fcompute(const int &a,const int &b,float &result){
    float init;
    for (int i = a; i < b; ++i) {
        init = v1[i]*v2[i];
        result += init;
//        cout << res << endl;
    }
}

int main(){
//    cout << "random vectors are being read" << endl;
    auto start1 = chrono::system_clock::now();

    const char* name1 = "data1";
    const char* name2 = "data3";
    v1 = read(name1), v2 = read(name2);
//    vector<float> vector1=read(name1),vector2=read(name2);

    auto end1 = chrono::system_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
    cout << "The reading costs " << duration1.count() <<"ms" << endl;

    auto start = chrono::system_clock::now();

    float res = cblas_sdot(200000000,v1,1,v2,1); // 与openBLAS中cblas_sdot()函数比较
    cout << fixed;
    cout << res << endl;

    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "openBLAS costs " << duration.count() <<"ms" << endl;

    auto start2 = chrono::system_clock::now();
//    double res1=0,res2=0,res3=0,res4=0,res5=0,res6=0,res7=0,res8=0;
    double res0=0;
    float res9=0;
//    thread t1(compute,0,50000000,ref(res1)); // 4线程
//    thread t2(compute,50000000,100000000,ref(res2));
//    thread t3(compute,100000000,150000000,ref(res3));
//    thread t4(compute,150000000,200000000,ref(res4));
//    thread t1(compute,0,25000000,ref(res1)); // 8线程
//    thread t2(compute,25000000,50000000,ref(res2));
//    thread t3(compute,50000000,75000000,ref(res3));
//    thread t4(compute,75000000,100000000,ref(res4));
//    thread t5(compute,100000000,125000000,ref(res5));
//    thread t6(compute,125000000,150000000,ref(res6));
//    thread t7(compute,150000000,175000000,ref(res7));
//    thread t8(compute,175000000,200000000,ref(res8));
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
//    t5.join();
//    t6.join();
//    t7.join();
//    t8.join();
//    res0 = res1+res2+res3+res4;
//    res0 += res5+res6+res7+res8;
    compute(0,200000000,res0);

    cout << res0 << endl;

    auto end2 = chrono::system_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
    cout << "double costs " << duration2.count() <<"ms" << endl;

    auto start3 = chrono::system_clock::now();

    fcompute(0,200000000,res9);
    cout << res9 << endl;

    auto end3 = chrono::system_clock::now();
    auto duration3 = chrono::duration_cast<chrono::milliseconds>(end3 - start3);
    cout << "float costs " << duration3.count() <<"ms" << endl;

    delete [] v1;
    delete [] v2;
    return 0;
}