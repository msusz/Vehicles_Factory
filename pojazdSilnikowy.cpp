#include "pojazdSilnikowy.h"
#include <iostream>
using namespace std;

pojazdSilnikowy::pojazdSilnikowy(int ladownosc, const string &kolor, const string &marka, double spalanie ) :
Pojazd(ladownosc, kolor, marka), spalanie(spalanie) {
this->przebieg=0;
this->iloscPaliwa=0;
}

void pojazdSilnikowy::jedz(int trasa) {

    if (trasa<0)
    {
        cout<<"\nPodales bledna ilosc kilometrow\n";
    }
    else if (iloscPaliwa < spalanie*trasa/100)
    {
        cout<<"\nMasz za malo paliwa, aby pokonac te trase.\nMozesz przejechac jeszcze "<<iloscPaliwa/spalanie*100<< "km.\n";
    }
    else
    {
        iloscPaliwa -= spalanie*trasa/100;
        przebieg+=trasa;
        cout<<"\nUdalo Ci sie dojechac do celu.\n";
    }
    if(iloscPaliwa<spalanie/100)
        cout<<"\n---------------------\n!      UWAGA       !\nJedziesz na rezerwie!\n---------------------\n";
}

void pojazdSilnikowy::wypiszPojazd() {
    Pojazd::wypiszPojazd();
    cout<<",\nIlosc paliwa: "<<iloscPaliwa<<"l, Spalanie: "<<spalanie<<"l na 100km,  Przebieg: "<<przebieg;
}

string pojazdSilnikowy::typPojazdu() {
    return "silnikowy";
}
