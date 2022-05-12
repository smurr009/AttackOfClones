#ifndef ROBOTS_H
#define ROBOTS_H

#include <location.h>

using namespace std;
class Robots : public location
{
    public:
        Robots();
        virtual ~Robots();

        int GetbatteryLife() { return batteryLife; }
        int GetrobotId() { return robotId; }
        Robots * GetNextRobot() { return next; }

        void SetbatteryLife(int val) { batteryLife = val; }
        void SetrobotId(int val) { robotId = val; }
        void SetNextRobot(Robots * val) { next  = val; }

        Display();

    protected:

    private:
        int batteryLife;
        int robotId;
        Robots * next;
};

#endif // ROBOTS_H
