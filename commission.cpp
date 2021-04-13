#include "commission.h"


Commission::Commission(const string &comissionName, double margin) : comissionName(comissionName), margin(margin) {}


void Commission::CommissionBuys(motorVehicle *vehicle) {

    vehicle->changeOwner(comissionName);
    square.push_back(vehicle);
    cout<<"\nComission "<<comissionName<<" have bought a vehicle with features: \n";
    square[square.size()-1]->printVehicle();
    cout<<"\nYou earned "<<purchasePrize(vehicle)<<". \nSee you later!\n";
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
    cout<<"\n_________PRICE: "<<sellingPrize(&square[i])<<"_________";
}
cout<<"\n------------------------\n";
}

double Comission::purchasePrize(motorVehicle *vehicle) {
    return double(vehicle->returnCapacity())/double(vehicle->milage+1)*100000;
}

double Comission::sellingPrize(motorVehicle *vehicle) {
    return purchasePrize(vehicle)+margin;
}

