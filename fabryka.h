#ifndef PROJEKT1_FABRYKA_H
#define PROJEKT1_FABRYKA_H

#include "samochod.h"
#include "rower.h"
#include "motocykl.h"
#include <string>

#define SPALANIE_M 5
#define SPALANIE_S 10

#define POJEMNOSC_FABRYKI 20 //maksymalna ilosc pojazdow w fabryce

using namespace std;

class Fabryka
{

private:
    Pojazd* tablica[POJEMNOSC_FABRYKI];
    string marka;
    //marka z gory zaklada jaka ladownosc maja jej pojazdy:
    int ladownoscMotocykl;
    int ladownoscSamochod;

public:
    explicit Fabryka (const string &marka= "", int ladownoscMotocykl=0, int ladownoscSamochod=0);
    Pojazd* sprzedaj(string nowyWlasciciel, int nr);
    void wypiszPojazdy();
    Pojazd* wybierzPojazd(int nr);
    string jakaMarka();       //zwraca marke fabryki
    int ilePojazdow;        //ilosc pojazdow aktualnie przechowywanych w fabryce (na poczatku 0)

    //dodawanie pojazdow do fabryki
    void nowySamochod(int drzwi, const string &kolor);
    void nowyMotocykl(const string &kolor);
    void nowyRower(const string &kolor, bool koszyk);
};


#endif //PROJEKT1_FABRYKA_H
