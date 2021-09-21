#include "rectangle.h"
#include <iostream>
using namespace std;

rectangle :: rectangle()
{
    count++;
    width = 1;
    height = 1;
}

rectangle :: rectangle(double w, double h)
{
    count++;
    width = w;
    height = h;
}

double rectangle :: getArea()
{
    double area = this->width * this->height;
    return area;
}

double rectangle :: getPerimeter()
{
    double per = 2 * (this->height + this->width);
    return per;
}

void rectangle :: display()
{
    cout << "Width:     " << this->width << endl;
    cout << "Height:    " << this->height << endl;
    cout << "Area:      " << this->getArea() << endl;
    cout << "Perimeter: " << this->getPerimeter() << endl;
}

rectangle :: ~rectangle()
{
    cout << "rectangle is been deleted." << endl;
}