#include <iostream>
#include "stack.h"
#include <cstring>
using namespace std;

int Stack::num = 0;

Stack::Stack(int n)
{
    cout << num << endl;
    num++;
    size = n;
    top = 0;
    pitems = new Item[n];
}

Stack::Stack(const Stack & st)
{
    cout << "copy " << num << endl;
    num++;
    size = st.size;
    top = st.top;
    pitems = new Item[size];
    memcpy(pitems,st.pitems,st.size*sizeof(Item));
}

Stack::~Stack()
{
    delete [] pitems;
    cout << "destructor is called" << endl;
}

bool Stack::isempty() const
{
    if (top == 0)
    {
        return true;
    } else {
        return false;
    }
}

bool Stack::isfull() const
{
    if (top == size-1)
    {
        return true;
    } else {
        return false;
    }
}

bool Stack::push(const Item & item)
{
    if (isfull())
    {
        return false;
    }
    top++;
    pitems[top] = item;
    return true;
}
bool Stack::pop()
{
    if (isempty())
    {
        return false;
    }
    --top;
    return true;
}

// Stack &Stack::operator=(const Stack &st)
// {
//     size = st.size;
//     top = st.top;
//     pitems = new Item[size];
//     memcpy(pitems,st.pitems,st.size*sizeof(Item));
//     return *this;
// }