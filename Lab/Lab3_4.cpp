#include <iostream>
#include <string>
using namespace std;

int main(){
    cout << "Enter the quiz, mid-term and final scores:";
    string numbers;
    double total = 0,count = 0;
    double in1,in2,in3;
        cin >> in1;
        cin >> in2;
        cin >> in3;
    double avg = (in1+in2+in3)/3;
    cout << "average score = " << avg;
    if (avg >= 90)
    {
        cout << " grade = A" << endl;
    }else if (avg >= 70 && avg < 90)
    {
        cout << " grade = B" << endl;
    }else if (avg >= 50 && avg < 70)
    {
        cout << " grade = C" << endl;
    }else if (avg < 50)
    {
        cout << " grade = F" << endl;
    }
    

}