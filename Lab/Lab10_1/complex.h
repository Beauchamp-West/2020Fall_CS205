#ifndef EXE_CANDYBAR_H
#define EXE_CANDYBAR_H

#include <iostream>
using namespace std;

class Complex
{
private:
    double real;
    double imag;
public:
    Complex();
    Complex(double re, double im);

    Complex operator+(Complex &other) const;
    Complex operator+(double real) const;
    Complex operator-(Complex &other) const;
    Complex operator*(Complex &other) const;
    Complex operator=(Complex &other) const;
    Complex operator~();
    bool operator==(Complex &other) const;
    bool operator!=(Complex &other) const;

    friend Complex operator+(double real, Complex &other);
    friend Complex operator*(double real, Complex &other);
    friend ostream &operator<<(ostream &os, const Complex &other);
    friend istream &operator>>(istream &is, Complex &other);

    double getReal();
    double getImag();
};

#endif