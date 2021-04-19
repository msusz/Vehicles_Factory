#include "car.h"
#include <iostream>


Car::Car(const int capacity, const int doors, const string &brand, const string &color, const double fuel) : motorVehicle(capacity, color, brand, fuel), doors(doors)
{
    this->fuelQuantity=FULL_TANK_C;
}

void Car::printVehicle() {
    cout<<"\nCAR\n"<<"Doors quantity: "<<doors<<", ";
    motorVehicle::printVehicle();
    cout<<endl;
}

void Car::drive(int route) {
    motorVehicle::drive(route);
}


