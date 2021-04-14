#ifndef SUSZCZYKMARCELINA_MOTORCYCLE_H
#define SUSZCZYKMARCELINA_MOTORCYCLE_H

#include "motorVehicle.h"

#define FULL_TANT_M 10    //tank capacity: 10l

class Motorcycle : public pojazdSilnikowy {
public:
    Motorcycle(int capacity, const string &color, const string &brand, double fuel);
    void printVehicle();
    void drive(int route) override;
};

#endif //SUSZCZYKMARCELINA_MOTORCYCLE_H
