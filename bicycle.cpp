#include "bicycle.h"

Bicycle::Bicycle(string color, bool basket) : Vehicle(basket*BASKET_CAPACITY, color), basket(basket)
{}

void Bicycle::printVehicle() {
    cout<<"BICYCLE:\n";
    Vehicle::printVehicle();
    if(basket)
        cout<<", Basket: YES\n";
    else
        cout<<", Basket: NO\n";
}

void Bicycle::drive(int route) {
    cout<<"\nYou're riding a bike, you don't have to worry about fuel!\n"
          "If you have had enough energy, you have ridden "<<route<<"km.\n";
}

string Bicycle::vehicleType() {
    return "bicycle";
}
