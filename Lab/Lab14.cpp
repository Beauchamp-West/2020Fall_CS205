#include <iostream>

using namespace std;

class OutOfRangeException
{
    public:
    int val;
    int par;
    OutOfRangeException(int i,int p) {val = i; par = p;};
};

float avg(int a, int b, int c, int d)
{
    if (a<0 || a>100)
    {
        throw OutOfRangeException(a,1);
    }
    if (b<0 || b>100)
    {
        throw OutOfRangeException(b,2);
    }
    if (c<0 || c>100)
    {
        throw OutOfRangeException(c,3);
    }
    if (d<0 || d>100)
    {
        throw OutOfRangeException(d,4);
    }
    
    float sum = a+b+c+d;
    return sum/4;
}

int main()
{
    char flag = 'y';
    int a,b,c,d;
    float res;

    do
    {
        cout << "Please enter marks for 4 courses: ";
        cin.ignore();
        cin >> a >> b >> c >> d;
        try
        {
           res = avg(a,b,c,d);
           cout << "The average of the four courses is " << res << endl; 
        }
        catch(const OutOfRangeException e)
        {
            cout << "The parameter " << e.par << " is " << e.val << " which out of range (0-100)." << endl;
        }
        
        cout << "Would you want to enter another marks for 4 courses(y/n)?";
        cin >> flag;

    } while (flag == 'y');

    cout << "Bye, see you next time." << endl;
    return 0;
}