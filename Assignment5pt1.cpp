#include <iostream>

using namespace std;

    class Car{
        public:
   
        int year;
        int miles;
        string brand;

        Car* myCar = new Car;
        myCar->brand = "BMW";
        myCar->miles = 30;
        myCar->year = 2020;
        myCar->Drive(10);
        myCar->Display();
        delete myCar;
        myCar = nullptr;

        void Display(){
            cout << "Brand: " << endl;
            cout << "Year: " << endl;
            cout << "Miles: " << endl;
        }
        void Drive(int m_miles){
            miles = miles + m_miles;
        }
    };

    int main(){

    }