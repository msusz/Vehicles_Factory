#include "motocykl.h"

Motocykl::Motocykl(int ladownosc, const string &kolor, const string &marka, double spalanie) : pojazdSilnikowy(ladownosc, kolor, marka, spalanie) {
    this->iloscPaliwa = PELEN_BAKM;
}

void Motocykl::wypiszPojazd() {
    cout<<"\tMOTOCYKL: "<<endl;
    pojazdSilnikowy::wypiszPojazd();
    cout<<endl;
}

void Motocykl::jedz(int trasa) {
    pojazdSilnikowy::jedz(trasa);
}