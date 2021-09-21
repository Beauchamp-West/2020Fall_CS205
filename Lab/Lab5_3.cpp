#include <iostream>
#include <string>
using namespace std;

int main(){
    int *parray = new int[5];

    cout << "Enter 5 integers:\n";

    for (int i = 0; i < 5; i++)
    {
        cin >> parray[i];
    }

    cout << "The elements of the array in reverse order are: " << endl;

    int *point = &parray[4];
    int num=0;
    while (num < 5)
    {
        cout << *(point-num) << " ";
        num++;
    }
    cout << endl;

    delete [] parray;
    return 0;
}