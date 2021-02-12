#include "rower.h"

Rower::Rower(string kolor, bool koszyk) : Pojazd(koszyk*LADOWNOSC_KOSZYKA, kolor), koszyk(koszyk)
{}

void Rower::wypiszPojazd() {
    cout<<"ROWER:\n";
    Pojazd::wypiszPojazd();
    if(koszyk)
        cout<<", Koszyk: TAK\n";
    else
        cout<<", Koszyk: NIE\n";
}

void Rower::jedz(int trasa) {
    cout<<"\nJedziesz rowerem, nie musisz martwic sie o paliwo!\n"
          "Jezeli masz dosc sil, przejedziesz nawet "<<trasa<<"km.\n";
}

string Rower::typPojazdu() {
    return "rower";
}
