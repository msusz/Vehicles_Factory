#ifndef SUSZCZYKMARCELINA_ETAP1_POJAZDSILNIKOWY_H
#define SUSZCZYKMARCELINA_ETAP1_POJAZDSILNIKOWY_H

#include "pojazd.h"

class pojazdSilnikowy : public Pojazd {
public:
    double iloscPaliwa;
    double spalanie;
    int przebieg;
    void wypiszPojazd() override;
    void jedz(int trasa) override;   //zwieksza przebieg o podana trase, zmniejsza paliwo o spalanie*trasa
    string typPojazdu() override;

    //konstruktor:
    pojazdSilnikowy(int ladownosc, const string &kolor, const string &marka, double spalanie = 0);  //ladownosc, kolor i marka dla konstruktora pojazdu

};


#endif //SUSZCZYKMARCELINA_ETAP1_POJAZDSILNIKOWY_H