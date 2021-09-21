#include <iostream>
using namespace std;

template <typename T>
T max5(T * array)
{
    T max = array[0];
    for (int i = 1; i < 5; i++)
    {
        max = array[i] > max? array[i]: max;
    }
    return max;
}

int main(){
    int ar1[5] = {1,2,3,4,5};
    double ar2[5] = {1.1,2,3,4,5.5};

    int max1 = max5(ar1);
    double max2 = max5(ar2);

    cout << "Max int = " << max1 << endl;
    cout << "Max double = " << max2 << endl;

    return 0;
}