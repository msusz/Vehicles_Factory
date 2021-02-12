#ifndef SUSZCZYKMARCELINA_ETAP1_POJAZD_H
#define SUSZCZYKMARCELINA_ETAP1_POJAZD_H


#include <string>
#include <iostream>
using namespace std;

class Pojazd {
public:
    int zwrocLadownosc() const;
    void ustalMarke(string nowaMarka);
    void zmienWlasciciela(const string &nowyWlasciciel);
    void zmienKolor(const string &nowyKolor);
    virtual void jedz(int trasa)=0;

public:
    virtual void wypiszPojazd();
    virtual string typPojazdu() = 0;
    //konstruktor:
    explicit Pojazd (int ladownosc=0, string kolor="NIEZNANY", string marka="");

private:
    int ladownosc;
    string kolor;
    string wlasciciel;
    string marka;
};


#endif //SUSZCZYKMARCELINA_ETAP1_POJAZD_H
