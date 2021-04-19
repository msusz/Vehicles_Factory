#ifndef SUSZCZYKMARCELINA_COMISSION_H
#define SUSZCZYKMARCELINA_COMISSION_H
#include "car.h"
#include "motorcycle.h"
#include <vector>

class Comission {
public:
    vector<motorVehicle*> square;
    explicit Comission(const string &comissionName=" ", double margin=0);
    void comissionBuys(motorVehicle *vehicle);
    Vehicle* comissionSells(int nr, const string &owner);
    void printSquare();
    static inline double purchasePrice(motorVehicle* vehicle);
    inline double sellingPrice(motorVehicle* vehicle);
private:
    string comissionName;
    double margin;
};


#endif //SUSZCZYKMARCELINA_COMISSION_H
