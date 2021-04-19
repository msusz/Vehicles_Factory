#ifndef SUSZCZYKMARCELINA_MOTORVEHICLE_H
#define SUSZCZYKMARCELINA_MOTORVEHICLE_H

#include "vehicle.h"

class motorVehicle : public Vehicle {
public:
    double fuelQuantity;
    double fuel;
    int milleage;
    void printVehicle() override;
    void drive(int route) override;
    string vehicleType() override;

    motorVehicle(int capacity, const string &color, const string &brand, double fuel = 0);

};


#endif //SUSZCZYKMARCELINA_MOTORVEHICLE_H