#ifndef SUSZCZYKMARCELINA_ETAP1_ROWER_H
#define SUSZCZYKMARCELINA_ETAP1_ROWER_H

#include "pojazd.h"
#define LADOWNOSC_KOSZYKA 10

class Rower : public Pojazd {
    bool koszyk;
public:
    explicit Rower(string kolor = "NIEZNANY", bool koszyk = false);
    void wypiszPojazd();
    void jedz(int trasa);
    string typPojazdu() override;
};


#endif //SUSZCZYKMARCELINA_ETAP1_ROWER_H