#include <iostream>
#include <fstream>
#include "location.h"

using namespace std;
location::location()
{
    next = NULL;
}

location::~location()
{
    //dtor
}

location::Display()
{
    cout << "Location X: " << locationX << endl;
    cout << "Location Y: " << locationY << endl;
    cout << endl;
}

