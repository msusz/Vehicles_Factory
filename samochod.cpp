#include "samochod.h"
#include <iostream>


Samochod::Samochod(const int ladownosc, const int drzwi, const string &marka, const string &kolor, const double spalanie) : pojazdSilnikowy(ladownosc, kolor, marka, spalanie), drzwi(drzwi)
{
    this->iloscPaliwa=PELEN_BAK;
}

void Samochod::wypiszPojazd() {
    cout<<"\tSAMOCHOD\n"<<"Ilosc drzwi: "<<drzwi<<", ";
    pojazdSilnikowy::wypiszPojazd();
    cout<<endl;
}

void Samochod::jedz(int trasa) {
    pojazdSilnikowy::jedz(trasa);
}


