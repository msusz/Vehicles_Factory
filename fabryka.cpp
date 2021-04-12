
#include "factory.h"
#include <iostream>

using namespace std;

Vehicle* Factory::sell(string newOwner, int nr) {

    Vehicle *vehicle=this->array[nr];
    vehicle->changeOwner(newOwner);
    //delating vehicle from the factory:
    for(int i=nr; i<nVehicles; i++)
    {
        array[i]=array[i+1];
    }
    nVehicles--;
    return vehicle;
}


void Factory::listVehicles() {
    if(!nVehicles)
        cout<<"! THIS FACTORY IS EMPTY !\n";
    else {
        for (int i = 0; i < this->nVehicles; i++) {
            cout << "\nVehicle " << i + 1 << ": ";
            array[i]->printVehicle();
        }
    }
}

Vehicle* Factory::chooseVehicle(int nr) {
    return this->array[nr];
}

Factory::Factory(const string &brand, int motorcycleCapacity, int carCapacity):
brand(brand), motorcycleCapacity(motorcycleCapacity), carCapacity(carCapacity) {
for(int i=0; i<FACTORY_CAPACITY; i++)
    this->array[i]=nullptr;
this->nVehicles=0;
}

string Factory::whatBrand() {
    return this->brand;
}


//__________________FUNCTIONS FOR CREATING NEW VEHICLES____________________
void Factory::newCar(int doors, const string &color) {

    Car* car=new Car(carCapacity, doors, brand, color, FUEL_CAR);
    car->setBrand(this->brand);
    array[this->nVehicles]=car;
    this->nVehicles++;
}

void Factory::newMotorcycle(const string &color) {
    Motorcycle* motorcycle = new Motorcycle(this->motorcycleCapacity, color, this->brand, FUEL_MOTORCYCLE);
    motorcycle->setBrand(this->brand);
    array[this->nVehicles]=motorcycle;
    this->nVehicles++;
}

void Factory::newBicycle(const string &color, bool basket) {
    Bicycle* bicycle = new Bicycle(color, basket);
    bicycle->setBrand(this->brand);
    array[this->nVehicles]=bicycle;
    this->nVehicles++;
}
