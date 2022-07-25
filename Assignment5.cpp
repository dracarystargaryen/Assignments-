#include <iostream>

using namespace std;

    class Car{
      public:
        int year;
        int miles;
        string brand;

        void Display(){
            cout << "Brand: " << endl;
            cout << "Year: " << endl;
            cout << "Miles: " << endl;
        }
        void Drive(int m_miles){
            miles = miles + m_miles;
        }
    };
