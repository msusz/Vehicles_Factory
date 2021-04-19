ektór#ifndef SUSZCZYKMARCELINA_BICYCLE_H
#define SUSZCZYKMARCELINA_BICYCLE_H

#include "vehicle.h"
#define BASKET_CAPACITY 10

class Bicycle : public Vehicle {
    bool basket;
public:
    explicit Bicycle(string color = "UNKNOWN", bool basket = false);
    void printVehicle();
    void drive(int route);
    string vehicleType() override;
};


#endif //SUSZCZYKMARCELINA_BICYCLE_H
