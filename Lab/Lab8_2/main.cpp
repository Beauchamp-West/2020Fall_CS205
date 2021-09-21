#include <iostream>
#include "rectangle.h"
using namespace std;

int rectangle :: count = 0;

int main(){
    rectangle rec(4,40);
    
    cout << "Rectangle " << rec.count << endl;
    cout << "--------------\n";
    rec.display();

    rectangle rec1(3.5,35.9);
    
    cout << "Rectangle " << rec1.count << endl;
    cout << "--------------\n";
    rec1.display();
    
    return 0;
}