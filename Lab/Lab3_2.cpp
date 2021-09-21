#include <iostream>
#include <cstring>
using namespace std;

int main(){
    char in;
    int count = 0;
    string check;
    cout << "Enter words(to stop, type the word done):" << endl;
    do{
        cin >> noskipws >> in;
        check += in;
        // cout << check << endl;
        if (in == 32)
        {
            count++;
            check.clear();
        }
        
        if (check == "done")
        {
            break;
        }  
    } while (true);
    cout << "You entered a total of " << count << " words." << endl;
    return 0;
}