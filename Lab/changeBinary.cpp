#include <iostream>
using namespace std;

int main()
{
   FILE * fp;
   fp = fopen("/Users/leolu/Downloads/C:C++/Assignments/cmake-build-debug/data1.txt", "r"); // 以二进制写入的形式打开

   float *ran;
   ran = new float[200000000]; // 动态分配数组
  
   fread(ran,sizeof(float), 200000000, fp); //二进制写

   FILE * fp1;
   fp1 = fopen("/Users/leolu/Downloads/C:C++/Assignments/cmake-build-debug/data3", "wb");
   fwrite(ran,sizeof(float), 200000000, fp1); 

   delete []ran;
   fclose(fp);
   fclose(fp1);
   return 0; 
}