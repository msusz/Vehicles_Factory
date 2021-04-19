#include "motorVehicle.h"
#include <iostream>
using namespace std;

motorVehicle::motorVehicle(int capacity, const string &color, const string &brand, double fuel ) :
Vehicle(capacity, color, brand), fuel(fuel) {
this->mileage=0;
this->fuelQuantity=0;
}

void motorVehicle::drive(int route) {

    if (route<0)
    {
        cout<<"\nDo you really want to drive backwards? Please choose a positive number of kilometers.\n";
    }
    else if (fuelQuantity < fuel*route/100)
    {
        cout<<"\nYou don't have enough fuel to drive this far.\nYou can drive only "<<fuelQuantity/fuel*100<< "km.\n";
    }
    else
    {
        fuelQuantity -= fuel*route/100;
        milleage+=route;
        cout<<"\nYou managed to complete your journey.\n";
    }
    if( fuelQuantity <fuel/100)
        cout<<"\n---------------------\n!      CAUTION       !\nYou are running out of fuel!\n---------------------\n";
}

void motorVehicle::printVehicle() {
    Vehicle::printVehicle();
    cout<<",\nFuel quantity: "<< fuelQuantity <<"l, Fuel consumption: "<<fuel<<"l per 100km,  Milleage: "<<przebieg;
}

string motorVehicle::vehicleType() {
    return "motor";
}
