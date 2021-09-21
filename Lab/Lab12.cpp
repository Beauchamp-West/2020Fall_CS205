#include <iostream>
#define pai 3.1415926
using namespace std;

class CStereoShape {
private:
    static int numberOfObject;
public:
    CStereoShape() 
    {
        numberOfObject++;
    };
    
    virtual float GetArea() 
    {
        cout << "CStereoShape::GetArea()" << endl;
        return 0.0;
    }

    virtual float GetVolume() 
    {
        cout << "CStereoShape::GetVolume" << endl;
        return 0.0;
    }

    virtual void Show()
    {
        cout << "CStereoShape::Show" << endl;
    }

    int GetNumOfObject()
    {
        return numberOfObject;
    }
};

class CCube : public CStereoShape {
private:
    float length;
    float width;
    float height;
public:
    CCube()
    {
        length = 0;
        width = 0;
        height = 0;
    }
    CCube(float l, float w, float h)
    {
        length = l;
        width = w;
        height = h;
    }
    CCube(CCube &cube)
    {
        length = cube.length;
        width = cube.width;
        height = cube.height;
    }

    float GetArea()
    {
        return 2*(length*width+length*height+width*height);
    }

    float GetVolume()
    {
        return length*width*height;
    }

    void Show()
    {
        cout << "Cube's length = " << length << endl;
        cout << "Cube's width = " << width << endl;
        cout << "Cube's height = " << height << endl;
        cout << "Cube's surface area = " << GetArea() << endl;
        cout << "Cube's volume = " << GetVolume() << endl;
    }
};

class CSphere : public CStereoShape {
private:
    float radius;
public:
    CSphere()
    {
        radius = 0;
    }
    CSphere(float r)
    {
        radius = r;
    }
    CSphere(CSphere &s)
    {
        radius = s.radius;
    }

    float GetArea()
    {
        return 4*pai*radius*radius;
    }

    float GetVolume()
    {
        return 4/3 * pai * radius*radius*radius;
    }

    void Show()
    {
        cout << "Sphere's radius = " << radius << endl;
        cout << "Sphere's surface area = " << GetArea() << endl;
        cout << "Sphere's volume = " << GetVolume() << endl;
    }
};

int CStereoShape :: numberOfObject = 0;

int main()
{
    CCube a_cube(4,5,6);
    CSphere c_sphere(7.9);
 
    cout.precision(1);
    cout.setf(ios::fixed);

    CStereoShape * p = &a_cube;
    p->Show();

    p = &c_sphere;
    p->Show();

    cout << p->GetNumOfObject();

    return 0;
}