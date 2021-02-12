#ifndef PROJEKT1_SAMOCHOD_H
#define PROJEKT1_SAMOCHOD_H

#include <string>
#include "pojazdSilnikowy.h"
using namespace std;

#define PELEN_BAK 50    //pojemnosc baku: 50l
#define SPALANIE_S 10   //spalanie dla samochodu

class Samochod : public pojazdSilnikowy{
    int drzwi;


public:
    explicit Samochod (int ladownosc=0, int drzwi=0, const string &marka="", const string &kolor="", double spalanie=SPALANIE_S);  //konstruktor
    void wypiszPojazd() override;

    void jedz(int trasa) override;
};


#endif //PROJEKT1_SAMOCHOD_H
