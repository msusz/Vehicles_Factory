#ifndef SUSZCZYKMARCELINA_ETAP1_MOTOCYKL_H
#define SUSZCZYKMARCELINA_ETAP1_MOTOCYKL_H

#include "pojazdSilnikowy.h"

#define PELEN_BAKM 10    //ladownosc baku: 10l

class Motocykl : public pojazdSilnikowy {
public:
    Motocykl(int ladownosc, const string &kolor, const string &marka, double spalanie);
    void wypiszPojazd();
    void jedz(int trasa) override;
};

#endif //SUSZCZYKMARCELINA_ETAP1_MOTOCYKL_H
