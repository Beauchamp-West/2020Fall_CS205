#include <iostream>
#include <cstring>
using namespace std;

struct box
{
    char maker [40];
    float height;
    float width;
    float length;
    float volume;
};

void show(box box1)
{
    cout << "Maker: " << box1.maker << endl;
    cout << "Height: " << box1.height << endl;
    cout << "Width: " << box1.width << endl;
    cout << "Length: " << box1.length << endl;
    cout << "Volume: " << box1.volume << endl;
}
void set(box &box2)
{
    box2.volume = box2.height * box2.length * box2.width;
}

int main()
{
    struct box box0;
    strcpy(box0.maker, "Jack Smith");
    box0.height = 3.4;
    box0.width = 4.5;
    box0.length = 5.6;
    box0.volume = 0;

    cout << "Before setting volume:\n";
    show(box0);
    cout << "After setting colume:\n";
    set(box0);
    show(box0);

    return 0;
}
