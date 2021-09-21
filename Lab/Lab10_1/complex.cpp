#include <iostream>
#include "complex.h"
using namespace std;

Complex::Complex()
{
    real = 0;
    imag = 0;

}
Complex::Complex(double re, double im)
{
    real = re;
    imag = im;
}

Complex Complex::operator+(Complex &other) const
{
    double real1 = real+other.real;
    double imag1 = imag+other.imag;
    return Complex(real1,imag1);
}

Complex Complex::operator+(double real) const
{

}

Complex Complex::operator-(Complex &other) const
{
    double real1 = real-other.real;
    double imag1 = imag-other.imag;
    return Complex(real1,imag1);
}

Complex Complex::operator*(Complex &other) const
{
    double real1 = real*other.real - imag*other.imag;
    double imag1 = real*other.imag + imag*other.real;
    return Complex(real1,imag1);
}

Complex Complex::operator=(Complex &other) const
{
    return Complex(other.real,other.imag);
}

Complex Complex::operator~()
{
    return Complex(real,0-imag);
}

bool Complex::operator==(Complex &other) const
{
    if (real == other.real && imag == other.imag)
    {
        return true;
    }
    return false;
}

bool Complex::operator!=(Complex &other) const
{
    if (real == other.real && imag == other.imag)
    {
        return false;
    }
    return true;
}

double Complex::getReal()
{
    double r = real;
    return r;
}

double Complex::getImag()
{
    double i = imag;
    return i;
}

Complex operator+(double real, Complex &other)
{
    double real1 = real+other.real;
    double imag1 = other.imag;
    return Complex(real1,imag1);
}
Complex operator*(double real, Complex &other)
{
    double real1 = real*other.real;
    double imag1 = real*other.imag;
    return Complex(real1,imag1);
}
ostream &operator<<(ostream &os, const Complex &other)
{
    os << other.real << "+" << other.imag << "i" << endl;
    return os;
}

istream &operator>>(istream &is, Complex &other)
{
    double r = other.real, i = other.imag;
    cout << "real: ";
    is >> other.real;
    cout << "imaginary: ";
    is >> other.imag;

    return is;
}