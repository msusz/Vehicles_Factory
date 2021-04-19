#include "comission.h"


Comission::Comission(const string &comissionName, double margin) : comissionName(comissionName), margin(margin) {}


void Comission::comissionBuys(motorVehicle *vehicle) {

    vehicle->changeOwner(comissionName);
    square.push_back(vehicle);
    cout<<"\nComission "<<comissionName<<" have bought a vehicle with features: \n";
    square[square.size()-1]->printVehicle();
    cout<<"\nYou earned "<<purchasePrice(vehicle)<<". \nSee you later!\n";
}

Vehicle* Comission::comissionSells(int nr, const string &owner) {
    Vehicle* vehicle = square[nr];
    vehicle->changeOwner(owner);
    square.erase(square.begin()+nr);
    return vehicle;
}

void Comission::printSquare() {
    cout<<"\n--------SQUARE OF "<<comissionName<<"--------";
for (int i=0; i<square.size(); i++)
{
    cout<<"\n\nVehicle "<<i+1<<":\n";
    square[i]->printVehicle();
    cout<<"\n_________PRICE: "<<sellingPrice(square[i])<<"_________";
}
cout<<"\n------------------------\n";
}

double Comission::purchasePrice(motorVehicle *vehicle) {
    return double(vehicle->returnCapacity())/double(vehicle->milleage+1)*100000;
}

double Comission::sellingPrice(motorVehicle *vehicle) {
    return purchasePrice(vehicle)+margin;
}

