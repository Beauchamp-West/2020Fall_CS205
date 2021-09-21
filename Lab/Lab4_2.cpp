#include <iostream>
#include <string>
using namespace std;

struct CandyBar{
    string name;
    float weight;
    int calories;
};

int main(){
    CandyBar candyBars[3];
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

    cout << "The greatest calories per weight is:" << endl;
    double max = 0;
    int number = 0;
    for (int i = 0; i < 3; i++)
    {
        double per = candyBars[i].calories/candyBars[i].weight;
        if (per > max)
        {
            max = per;
            number = i;
        }
    }
    cout << "Brand name: " << candyBars[number].name << endl;
    cout << "Calories per weight: " << max << endl;
    
    return 0;
}