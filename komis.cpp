#include "komis.h"


Komis::Komis(const string &nazwaKomisu, double marza) : nazwaKomisu(nazwaKomisu), marza(marza) {}


void Komis::komisKupuje(pojazdSilnikowy *pojazd) {

    pojazd->zmienWlasciciela(nazwaKomisu);
    plac.push_back(*pojazd);
    cout<<"\nKomis "<<nazwaKomisu<<" zakupil pojazd o nastepujacych parametrach: \n";
    plac[plac.size()-1].wypiszPojazd();
    cout<<"\nOtrzymujesz "<<cenaSkupu(pojazd)<<"zl. \nDo widzenia!\n";
}

Pojazd* Komis::komisSprzedaje(int nr, const string &wlasciciel) {
    Pojazd* pojazd = &plac[nr];
    pojazd->zmienWlasciciela(wlasciciel);
    plac.erase(plac.begin()+nr);
    return pojazd;
}

void Komis::wypiszPlac() {
    cout<<"\n--------PLAC KOMISU "<<nazwaKomisu<<"--------";
for (int i=0; i<plac.size(); i++)
{
    cout<<"\n\nMiejsce "<<i+1<<":\n";
    plac[i].wypiszPojazd();
    cout<<"\n_________CENA: "<<cenaSprzedazy(&plac[i])<<"_________";
}
cout<<"\n------------------------\n";
}

double Komis::cenaSkupu(pojazdSilnikowy *pojazd) {
    //przebieg zwiekszamy o 1, bo gdyby byl 0 to nie da sie przez niego podzielic, a cena ma byc odwrotnie proporcjonalna do przebiegu
    //kazda marka ma swoja okreslona ladownosc, wiec wyznaczajac cene proporcjonalna do ladownosci uzalezniam ja od marki
    return double(pojazd->zwrocLadownosc())/double(pojazd->przebieg+1)*100000;
}

double Komis::cenaSprzedazy(pojazdSilnikowy *pojazd) {
    return cenaSkupu(pojazd)+marza;
}

