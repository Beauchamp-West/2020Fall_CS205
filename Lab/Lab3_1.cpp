#include <iostream>
using namespace std;

int main(){
    int in,sum=0;
    do{
        cout << "Enter an integer number:";
        cin >> in;
        sum += in;
        cout << "The cumulative sum of the entries to date is :" << sum << endl;
    } while (in != 0);
    return 0;
}