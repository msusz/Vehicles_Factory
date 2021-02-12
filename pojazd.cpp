#include "pojazd.h"

#include <utility>

int Pojazd::zwrocLadownosc() const {
    return ladownosc;
}

Pojazd::Pojazd(const int ladownosc, string kolor, string marka) : ladownosc(ladownosc), kolor(std::move(kolor)), marka(std::move(marka)) {
 this->wlasciciel="FABRYKA";
}

void Pojazd::wypiszPojazd() {
    cout<<" Marka: "<<marka<<", Kolor: "<<kolor<<", Ladownosc: "<<ladownosc<<", Wlasciciel: "<<wlasciciel;
}

void Pojazd::zmienWlasciciela(const string &nowyWlasciciel) {
    wlasciciel=nowyWlasciciel;
}

void Pojazd::ustalMarke(string nowaMarka) {
    this->marka=std::move(nowaMarka);
}

void Pojazd::zmienKolor(const string &nowyKolor) {
kolor=nowyKolor;
}
