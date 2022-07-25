class Plane : public Vehicle{
    bool Drive;

public:
     Plane(string Pname, int Pmiles, int Pyear)
        : Vehicle(Pname, Pmiles, Pyear)
        , Drive(false);
    {

    }
    void Miles(){
        std::cout << "Miles driven: ";
    }

    void Drive(float Driven){
        Pmiles += Driven;
        if (!Pmiles){
            Pmiles = 0;
        } else {
            Pmiles = 1;
        }
    }
    void PlaneDriven(){
        Drive = true;
    }
};