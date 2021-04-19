#ifndef PROJEKT1_CAR_H
#define PROJEKT1_CAR_H

#include <string>
#include "motorVehicle.h"
using namespace std;

#define FULL_TANK_C 50
#define FUEL_CAR 10 

class Car : public motorVehicle{
    int doors;


public:
    explicit Car (int capacity=0, int doors=0, const string &brand="", const string &color="", double fuel=FUEL_CAR);
    void printVehicle() override;

    void drive(int route) override;
};


#endif //PROJEKT1_CAR_H
