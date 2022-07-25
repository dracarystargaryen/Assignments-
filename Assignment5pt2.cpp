#include <iostream>

using namespace std;

class Car {
    public:

    Car(){
        cout << "default" << endl;

    }
    ~Car(){
        cout << "deconstructor" << end;
    }
};

int main(){
    Car (int year, int miles, string brand){
        m_year = year;
        m_mile = miles;
        m_brand = brand;
    }
    Car myCar (2020, 30, "Ford");

    Car *pCar = new Car (2020, 30, "Ford");
    delete pCar;
    pCar = nullptr;
}