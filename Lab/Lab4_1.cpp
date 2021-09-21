#include <iostream>
#include <string>
using namespace std;

struct CandyBar{
    string name;
    float weight;
    int calories;
};

int main(){
    CandyBar candyBar;
    cout << "Enter brand name of a Candy bar: ";
    getline(cin, candyBar.name);
    cout << "Enter weight of the Candy bar: ";
    cin >> candyBar.weight;
    cout << "Enter calories (an integer value) in the Candy bar: ";
    cin >> candyBar.calories;

    cout << "Brand: " << candyBar.name << endl;
    cout << "Weight: " << candyBar.weight << endl;
    cout << "Calories: " << candyBar.calories << endl;
    return 0;
}