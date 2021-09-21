#ifndef EXE_CANDYBAR_H
#define EXE_CANDYBAR_H

#include <iostream>
using namespace std;

class Number{
    private:
        int num;
    public:
        Number();
        Number(int n);

        Number operator++();
        Number operator--();
        Number operator++(int);
        Number operator--(int);

        friend ostream &operator<<(ostream &os, const Number &other);
        friend istream &operator>>(istream &is, const Number &other);
};

#endif