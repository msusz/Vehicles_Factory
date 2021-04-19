#include "vehicle.h"

#include <utility>

int Vehicle::returnCapacity() const {
    return capacity;
}

Vehicle::Vehicle(const int capacity, string color, string brand) : capacity(capacity), color(std::move(color)), brand(std::move(brand)) {
 this->owner="FACTORY";
}

void Vehicle::printVehicle() {
    cout<<" Brand: "<<brand<<", Color: "<<color<<", Capacity: "<<capacity<<", Owner: "<<owner;
}

void Vehicle::changeOwner(const string &newOwner) {
    owner=newOwner;
}

void Vehicle::setBrand(string newBrand) {
    this->brand=std::move(newBrand);
}

void Vehicle::changeColor(const string &newColor) {
color=newColor;
}
