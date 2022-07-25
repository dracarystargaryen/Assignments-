#include <iostream>

using namespace std

class Car {
    private:
        int year;

    public:
        void setYear (int newYear){
            year = newYear;
        }
        int GetYear(){
            return year;
        }
        void Display(){
            cout << "Year: " << year << endl;
    }
};

int main(){
    Car myCar;
    myCar.setYear(2020);
    myCar.Display();
}