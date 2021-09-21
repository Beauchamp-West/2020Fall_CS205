#ifndef EXE_CANDYBAR_H
#define EXE_CANDYBAR_H
#include <iostream>

const int LEN = 30;
class CandyBar
{
    private:
        char brand[LEN];
        double weight;
        int calories;
    public:
        void setCandyBar();
        void showCandyBar();

};

#endif