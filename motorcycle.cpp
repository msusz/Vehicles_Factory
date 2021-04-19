#include "motorcycle.h"

Motorcycle::Motorcycle(int capacity, const string &color, const string &brand, double fuel) : motorVehicle(capacity, color, brand, fuel) {
    this->fuelQuantity = FULL_TANK_M;
}

void Motorcycle::printVehicle() {
    cout<<"\tMOTORCYCLE: "<<endl;
    motorVehicle::printVehicle();
    cout<<endl;
}

void Motorcycle::drive(int route) {
    motorVehicle::drive(route);
}