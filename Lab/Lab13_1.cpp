
/****************************************************
*
* FileName: maxTemplate.cpp
* Purpose: Demonstrate the use of function templates
*
********************************************************/
#include <iostream>
#include <string>
using namespace std;

template <typename T> T Max(T one, T two);

int main()
{
    int i_one = 3, i_two = 5;
    cout << "The max of " << i_one << " and " << i_two << " is "
    << Max(i_one, i_two) << endl;

    double d_one = 3.3, d_two = 5.5;
    cout << "The max of " << d_one << " and " << d_two << " is "
    << Max(d_one, d_two) << endl;

    string s_one = "Hello", s_two = "World";
    cout << "The max of " << s_one << " and " << s_two << " is "
    << Max(s_one, s_two) << endl;

return 0;
}

template <typename T> T Max (T one, T two)
{
T biggest;
if (one < two)
{
biggest = two;
}
else
{
biggest = one;
}
return biggest;
}