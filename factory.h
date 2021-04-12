#ifndef PROJEKT1_FACTORY_H
#define PROJEKT1_FACTORY_H

#include "car.h"
#include "bicycle.h"
#include "motorcycle.h"
#include <string>

#define FUEL_MOTORCYCLE 5
#define FUEL_CAR 10

#define FACTORY_CAPACITY 20 //how many vehicles can be in a factory

using namespace std;

class Factory
{

private:
    Vehicle* array[FACTORY_CAPACITY];
    string brand;
    //a brand has specified capacity for its vehicles
    int motorcycleCapacity;
    int carCapacity;

public:
    explicit Factory (const string &brand= "", int motorcycleCapacity=0, int carCapacity=0);
    Vehicle* sell(string newOwner, int nr);
    void listVehicles();
    Vehicle* chooseVehicle(int nr);
    string whatBrand();         //returns brand name
    int nVehicles;              //number of vehicles stored in the factory

    //creating vehicles
    void newCar(int doors, const string &color);
    void newMotorcycle(const string &color);
    void newBicycle(const string &color, bool basket);
};


#endif //PROJEKT1_FACTORY_H
