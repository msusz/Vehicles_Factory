
#include "fabryka.h"
#include <iostream>

using namespace std;

Pojazd* Fabryka::sprzedaj(string nowyWlasciciel, int nr) {

    Pojazd *pojazd=this->tablica[nr];   //zapisanie pojazdu z tablicy
    pojazd->zmienWlasciciela(nowyWlasciciel);   //zmiana wlasciciela
    //teraz trzeba usunac samochod z tablicy fabryki i przesunac pozostale samochody na wczesniejsze pozycje:
    for(int i=nr; i<ilePojazdow; i++)
    {
        tablica[i]=tablica[i+1];
    }
    ilePojazdow--;
    return pojazd;
}


void Fabryka::wypiszPojazdy() {
    if(!ilePojazdow)
        cout<<"! TA FABRYKA JEST PUSTA !\n";
    else {
        for (int i = 0; i < this->ilePojazdow; i++) {
            cout << "\nPojazd " << i + 1 << ": ";
            tablica[i]->wypiszPojazd();
        }
    }
}

Pojazd* Fabryka::wybierzPojazd(int nr) {
    return this->tablica[nr];
}

Fabryka::Fabryka(const string &marka, int ladownoscMotocykl, int ladownoscSamochod):
marka(marka), ladownoscMotocykl(ladownoscMotocykl), ladownoscSamochod(ladownoscSamochod) {
for(int i=0; i<POJEMNOSC_FABRYKI; i++)
    this->tablica[i]=nullptr;
this->ilePojazdow=0;
}

string Fabryka::jakaMarka() {
    return this->marka;
}


//__________________FUNKCJE TWORZACE NOWE POJAZDY____________________
void Fabryka::nowySamochod(int drzwi, const string &kolor) {

    Samochod* samochod=new Samochod(ladownoscSamochod, drzwi, marka, kolor, SPALANIE_S);
    samochod->ustalMarke(this->marka);
    tablica[this->ilePojazdow]=samochod;
    this->ilePojazdow++;
}

void Fabryka::nowyMotocykl(const string &kolor) {
    Motocykl* motocykl = new Motocykl(this->ladownoscMotocykl, kolor, this->marka, SPALANIE_M);
    motocykl->ustalMarke(this->marka);
    tablica[this->ilePojazdow]=motocykl;
    this->ilePojazdow++;
}

void Fabryka::nowyRower(const string &kolor, bool koszyk) {
    Rower* rower = new Rower(kolor, koszyk);
    rower->ustalMarke(this->marka);
    tablica[this->ilePojazdow]=rower;
    this->ilePojazdow++;
}
