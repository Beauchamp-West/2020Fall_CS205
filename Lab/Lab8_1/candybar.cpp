#include <iostream>
#include "candybar.h"
using namespace std;

void CandyBar :: setCandyBar()
{
    cout << "Enter the brand name of Candy bar: ";
    // cin.ignore();
    cin.getline(this -> brand,30);
    cout << "Enter the weight: ";
    cin >> this -> weight;
    cout << "Enter the calories: ";
    cin >> this -> calories;
    cin.ignore();
}

void CandyBar :: showCandyBar()
{
    cout << "Brand name: " << this -> brand << endl;
    cout << "Weight: " << this -> weight << endl;
    cout << "Calories: " << this -> calories << endl;
    
}