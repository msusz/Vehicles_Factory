#ifndef SUSZCZYKMARCELINA_ETAP1_KOMIS_H
#define SUSZCZYKMARCELINA_ETAP1_KOMIS_H
#include "samochod.h"
#include "motocykl.h"
#include <vector>

class Komis {
public:
    vector<pojazdSilnikowy> plac;
    explicit Komis(const string &nazwaKomisu=" ", double marza=0);
    void komisKupuje(pojazdSilnikowy *pojazd);
    Pojazd* komisSprzedaje(int nr, const string &wlasciciel);
    void wypiszPlac();
    static inline double cenaSkupu(pojazdSilnikowy* pojazd);    //static bo nie zmienia zawartosci obiektu komis,
                                                                //inline bo ma jedna linijke i zadziala szybciej
    inline double cenaSprzedazy(pojazdSilnikowy* pojazd);
private:
    string nazwaKomisu;
    double marza;       //komis ma okreslana marze narzucana na sprzedawane pojazdy
};


#endif //SUSZCZYKMARCELINA_ETAP1_KOMIS_H
