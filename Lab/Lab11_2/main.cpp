#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
    // Stack a;
    Stack b(2);
    Stack c = b;

    // if (a.isempty())
    // {
    //     cout << "a is empty" << endl;
    // }
    
    // if(!a.pop())
    // {
    //     cout << "a cannot pop" << endl;
    // }
    // for (size_t i = 0; i < 10; i++)
    // {
    //     a.push(i);
    // }
    // if (a.isfull())
    // {
    //     cout << "a is full" << endl;
    // }
    // if (!a.push(10))
    // {
    //     cout << "a cannot push" << endl;
    // }

    for (size_t i = 0; i < 2; i++)
    {
        b.push(i);
    }
    if (b.isfull())
    {
        cout << "b is full" << endl;
    }

    for (size_t i = 0; i < 2; i++)
    {
        c.push(i);
    }
    if (c.isfull())
    {
        cout << "c is full" << endl;
    }
    
}