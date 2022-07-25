class Truck : public Vehicle{
    bool Drive;

public:
    Truck(string Tname, int Tmiles, int Tyear)
        : Vehicle(Tname, Tmiles, Tyear)
        , Drive(false);
    {

    }
    void Miles(){
        std::cout << "Miles driven: ";
    }

    void Drive(float Driven){
        Tmiles += Driven;
        if (!Tmiles){
            Tmiles = 0;
        }
    }
    void drivenCar(){
        Drive = true;
    }
};