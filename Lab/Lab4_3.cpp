#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ofstream myfile("f1.txt");
    string input;
    char in;
    if (myfile.is_open())
    {
        cout << "Please input a string: ";
        do{
        in=cin.get();
        if (in <'0' || in>'9')
        {
            input += in;
        }
        }while (in != 10);
        input.pop_back();
        
        
        // cout << input << endl;
        
        myfile << input;
        myfile.close();
    }

    for (int i=0;i<input.size();i++)
    {
        if (input[i] >= 'a' && input[i] <= 'z')
        {
            input[i] -= 32;
        }
        
        
    }
    
    ofstream myfile1("f2.txt");
    if (myfile1.is_open())
    {
        myfile1 << input;
        myfile1.close();
    }

    string content1,content2;
    ifstream myfile2("f1.txt");
    if (myfile2.is_open())
    {
        getline(myfile2,content1); 
        cout << content1 << endl;
    }
    ifstream myfile3("f2.txt");
    if (myfile3.is_open())
    {
        getline(myfile3,content2); 
        cout << content2 << endl;
    }
    return 0;
}