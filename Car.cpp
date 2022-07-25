class Car : public Vehicle{
    bool Drive;

public:
    Car(string Cname, int Cmiles, int Cyear)
        : Vehicle(Cname, Cmiles, Cyear)
        , Drive(false);
    {

    }
    void Miles(){
        std::cout << "Miles driven: ";
    }

    void Drive(float Driven){
        Cmiles += Driven;
        if (!cMiles){
            cMiles = 0;
        }
    }
    void drivenCar(){
        Drive = true;
    }
};