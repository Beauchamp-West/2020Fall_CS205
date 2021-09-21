#include <iostream>
#include "number.h"
using namespace std;

Number::Number()
{
    num = 0;
}

Number::Number(int n)
{
    num = n;
}

Number Number::operator++()
{
    num += 1;
    return num;
}

Number Number::operator--()
{
    num -= 1;
    return num;
}

Number Number::operator++(int)
{
    int tmp = num;
    num += 1;
    return tmp;
}

Number Number::operator--(int)
{
    int tmp = num;
    num -= 1;
    return tmp;
}

ostream &operator<<(ostream &os, const Number &n)
{
    os << n.num << endl;
    return os;
}

istream &operator>>(istream &is, const Number &n)
{
    is >> n.num;
    return is;
}