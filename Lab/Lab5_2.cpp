#include <iostream>
#include <string>
using namespace std;

struct CandyBar{
    string name;
    float weight;
    int calories;
};

int main(){
    CandyBar *candyBars = new CandyBar[3];
    cout << "Please input three CandyBar's information" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "Enter the brand name of Candy bar: ";
        cin.ignore();
        getline(cin, candyBars[i].name);
        cout << "Enter the weight: ";
        cin >> candyBars[i].weight;
        cout << "Enter the calories: ";
        cin >> candyBars[i].calories;
    }
    
    cout << "Display the CandyBar array contents" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Brand name: " << candyBars[i].name << endl;
        cout << "Weight: " << candyBars[i].weight << endl;
        cout << "Calories: " << candyBars[i].calories << endl;
    }

    delete [] candyBars;
    return 0;
}