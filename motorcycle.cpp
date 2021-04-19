#include "motorcycle.h"

Motorcycle::Motorcycle(int capacity, const string &color, const string &brand, double fuel) : motorVehicle(capacity, color, brand, fuel) {
    this->fuelQuantity = FULL_TANK_M;
}

void Motorcycle::Motorcycle() {
    cout<<"\tMOTORCYCLE: "<<endl;
    motorVehicle::printVehicle();
    cout<<endl;
}

void MotoMotorcycle::drive(int route) {
    motorVehicle::drive(route);
}