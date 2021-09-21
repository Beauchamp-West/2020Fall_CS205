#include <iostream>
#include <cstring>
using namespace std;
int main(){
    for (int i = 0; i < 7; i++)
    {
        string out;
        for (int j = 0; j <= i; j++)
        {
            int k = j+1;
            char a = k + '0';
            out += a;
        }
        while (out.size() != 7)
        {
            out += '*';
        }
        cout << out << endl;   
    }
    return 0;
}