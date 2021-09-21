#include <iostream>
#include <string>
using namespace std;

struct Pizza
{
    string name;
    int diameter;
    float weight;
};

int main(){
    Pizza *pizza = new Pizza;

    cout << "Enter the name of pizza company: ";
    getline(cin,pizza->name);
    cout << "Enter the diameter of the pizza(inches): ";
    cin >> pizza->diameter;
    cout << "Enter the weight of the pizza(g): ";
    cin >> pizza->weight;

    cout << "Display the information of the pizza\n";
    cout << "Company name: " << pizza->name << endl;
    cout << "Pizza diameter: " << pizza->diameter << " inches" << endl;
    cout << "Pizza weight: " << pizza->weight << " g" << endl;

    delete pizza;
    return 0;
}