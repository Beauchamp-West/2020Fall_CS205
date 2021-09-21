#include<opencv2/opencv.hpp>
using namespace cv;//下面的所有cv相关类型不用加上前缀了
int main(){
    Mat img =imread("/home/douxiao/Desktop/opencvtest/demo1/001.jpg");//声明Mat变量，并读取图片，imread中需要传入图片的绝对路径
    imshow("image",img);//在窗口中显示载入的图片
    waitKey();//等待按键
    return 0;
}