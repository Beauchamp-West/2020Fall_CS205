#include <iostream>
using namespace std;

string smile()
{
    return "Smile!";
}

int main()
{   
    cout << smile() << smile() << smile() << endl;
    cout << smile() << smile() << endl;
    cout << smile() << endl;
    return 0;
}
