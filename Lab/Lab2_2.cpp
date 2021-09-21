#include <iostream>
using namespace std;

int main(){
    long long second;
    cout << "Enter the number of seconds:";
    cin >> second;
    int day = second/3600/24;
    int hour = second%(3600*24*day)/3600;
    int mins = second%(3600*24*day)%(3600*hour)/60;
    int sec = second%(3600*24*day)%(3600*hour)%(60*mins);
    cout << second << " seconds = " << day << " days, " << hour << " hours, " << mins << "minutes, " << sec << " seconds" << endl;
    return 0;
}