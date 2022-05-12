#include <iostream>
#include <fstream>
#include "robots.h"

using namespace std;
Robots::Robots()
{
    next = NULL;
}

Robots::~Robots()
{
    //dtor
}

Robots::Display()
{
    cout << "robotId: " << robotId << endl;
    cout << "batteryLevel: " << batteryLife << endl;
}

