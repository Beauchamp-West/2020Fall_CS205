#include <iostream>
using namespace std;

int Fill_array(double arr[], int size)
{
    int i = 1;
    do{
        cout << "Enter Value #" << i << ": ";
        cin >> arr[i-1];
        if (cin.rdstate() != 0)
        {
            break;
        }
        i++;
    }while (i <= size);
   
   return i-1; 
}
void Show_array(double *arr, int size)
{
    int i = 0;
    while (i < size)
    {
        cout << arr[i] << " ";
        i++;
    }
    cout << "\n";
    
}
void Reverse_array(double *arr, int size)
{
    double tmp = *arr;
	*arr = *(arr+size-1);
    *(arr+size-1) = tmp;
	if(arr != arr+size-1) Reverse_array(arr+1,size-2);
} 

int main(){
    int size;
    cout << "Enter the size of an array: ";
    cin >> size;
    double ary[size];

    int trueSize = Fill_array(ary,size);
    // cout << trueSize << endl;
    Show_array(ary,trueSize);
    Reverse_array(ary,trueSize);
    Show_array(ary,trueSize);
    Reverse_array(ary+1,trueSize-2);
    Show_array(ary,trueSize);
    return 0;
}