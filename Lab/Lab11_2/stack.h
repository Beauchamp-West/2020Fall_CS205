#ifndef EXE_CANDYBAR_H
#define EXE_CANDYBAR_H
typedef unsigned long Item;

#include <iostream>
using namespace std;

class Stack
{
private:
    enum {MAX = 10};
    Item * pitems;
    int size;
    int top;
    static int num;
public:
    Stack(int n = MAX);
    Stack(const Stack & st);
    ~Stack();

    bool isempty() const;
    bool isfull() const;
    bool push(const Item & item);
    bool pop();
    Stack &operator=(const Stack &st);

};

#endif