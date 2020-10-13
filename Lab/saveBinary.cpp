#include <iostream>
#include <random>
#include <vector>
using namespace std;

float generateRand(){ //生成随机数组
    float a1;
    random_device r1;
    a1 = r1() / float(RAND_MAX / 100);
    return a1;
}


int main()
{
   FILE * fp= NULL;
   
   fp = fopen("/Users/leolu/Downloads/C++/Assignments/cmake-build-debug/data3", "wb"); // 以二进制写入的形式打开
   if (fp == NULL)
   {
      cout << "wrong\n";
      return -1;
   }
   
   float *ran;
   ran = new float[200000000]; // 动态分配数组
   for (int i =0 ; i < 200000000; ++i)
   {
      ran[i] = generateRand();
   }

   fwrite(ran,sizeof(float), 200000000, fp); //二进制写

   delete []ran;
   fclose(fp);
   return 0; 
}