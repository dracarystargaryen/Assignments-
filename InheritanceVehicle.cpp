#include <iostream>

class Vehicle{
    protected: 
        string name;
        int miles;
        int year;
        bool isMoving;
        bool mDistance;

    public:
        Car(string Cname, int Cmiles, int Cyear)
        : Cname(name);
        , Cmiles(miles);
        , Cyear(year);
        {
            
        }

        Truck(string Tname, int Tmiles, int Tyear)
        : Tname(name);
        , Tmiles(miles);
        , Tyear(year);

        {

        }

        Plane(string Pname, int Pmiles, int Pyear)
        : Pname(name);
        , Pmiles(miles);
        , Pyear(year);

        {

        }

        void Drive (int i, int j){

            position += i;
            position += j;
        }

        void Distance(float distance){
            if(!isMoving){
                mDistance -= distance;
        } else {
                mDistance += distance;
        }
    }
};