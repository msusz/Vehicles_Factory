#ifndef SUSZCZYKMARCELINA_VEHICLE_H
#define SUSZCZYKMARCELINA_VEHICLE_H


#include <string>
#include <iostream>
using namespace std;

class Vehicle {
public:
    int returnCapacity() const;
    void setBrand(string newBrand);
    void changeOwner(const string &newOwner);
    void changeColor(const string &newColor);
    virtual void drive(int route)=0;

public:
    virtual void printVehicle();
    virtual string vehicleType() = 0;
    //constructor:
    explicit Vehicle (int capacity=0, string color="UNKNOWN", string brand="");

private:
    int capacity;
    string color;
    string owner;
    string brand;
};


#endif //SUSZCZYKMARCELINA_VEHICLE_H
