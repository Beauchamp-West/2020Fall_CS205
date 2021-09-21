#ifndef RECTANGLE_H
#define RECTANGLE_H

class rectangle
{
    private:
        double width;
        double height;
    public:
        int static count;
        rectangle();
        rectangle(double w, double h);
        double getArea();
        double getPerimeter();
        void display();
        ~rectangle();
};

#endif