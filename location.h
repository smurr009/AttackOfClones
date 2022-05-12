#ifndef LOCATION_H
#define LOCATION_H


class location
{
    public:
        location();
        virtual ~location();

        int GetlocationX() { return locationX; }
        int GetlocationY() { return locationY; }
        location * GetNextLocation() { return next; }

        void SetlocationX(int val) { locationX = val; }
        void SetlocationY(int val) { locationY = val; }
        void SetNextLocation (location * val) { next = val; }

        Display();

    protected:

    private:
        int locationX;
        int locationY;
        location * next;
};

#endif // LOCATION_H
