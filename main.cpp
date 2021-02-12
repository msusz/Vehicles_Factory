#include <iostream>
#include <fstream>
#include <thread>
#include "samochod.h"
#include "fabryka.h"
#include "komis.h"
#include "lakiernik.h"
#include "wyjatki.h"

using namespace std;

#define MAX_FABRYK 5
#define MAX_SPRZEDANYCH 100

//funkcje obslugujace opcje z menu glownego:
void WypiszFabryki(Fabryka** koncern, const int *iloscFabryk);
void NowaFabryka(Fabryka** koncern, int *iloscFabryk);
void ListaPojazdow(Fabryka** koncern, int iloscFabryk);
void NowyPojazd(Fabryka** koncern, int iloscFabryk);
void Sprzedaj(Fabryka** koncern, int iloscFabryk, Pojazd** sprzedane, int* iloscSprzedanych);
void JedzPojazdem(Fabryka** koncern, int iloscFabryk);
void ZmienKolor(Fabryka** koncern, int iloscFabryk, Lakiernik* lakiernik);
void KupZKomisu(Komis* komis, Pojazd** sprzedane, int* iloscSprzedanych);
void SprzedajDoKomisu(Komis* komis, Pojazd** sprzedane, int* iloscSprzedanych);

//funkcje do wybierania konkretnej fabryki i samochodu:
Fabryka* wybierzFabryke(Fabryka** koncern, int iloscFabryk);
int wybierzPojazd(Fabryka fabryka);

//funkcje tworzace nowe pojazdy
void NowySamochod(Fabryka** koncern, int nr);
void NowyMotocykl(Fabryka** koncern, int nr);
void NowyRower(Fabryka** koncern, int nr);

//funkcje wczytujace
template <typename T> T wczytaj(bool t);
string wczytaj(bool t);


template<typename T> void Dopisz(T* t, T** tab, int *tabSize) {
    tab[*tabSize]=t;
    (*tabSize)++;
}

ifstream *plikTestowy;
bool test = false;

//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    plikTestowy = new ifstream();
    if (argc > 1) {
        cout<<"\nTERAZ TESTUJEMY - wartosci beda wczytywane z pliku "<< argv[argc-1] << endl;
        plikTestowy->open(argv[1]);
        if(plikTestowy->is_open()) {
            cout<<"\nUdalo sie otworzyc plik testowy\n\n";
            test = true;
        }
    }

    //fabryki przechowywane sa w tablicy o dlugosci MAX_FABRYK,
    //ilosc fabryk juz dodanych zapisana jest w zmiennej iloscFabryk
    Fabryka* koncern[MAX_FABRYK];
    int iloscFabryk=0;

    //analogicznie przechowywane sa sprzedane pojazdy:
    Pojazd* sprzedane[MAX_SPRZEDANYCH];
    int iloscSprzedanych = 0;

    auto* lakiernik=new Lakiernik();

    //----------------------------------------TWORZENIE KOMISU
    cout<<"\n  Witaj w programie sluzacym do zarzadzania pojazdami!\n"
          "Uzywane samochody maga byc skupowane oraz sprzedawane przez komis.\n\n"
          "Jak nazywa sie komis, z ktorego zamierzasz korzystac?\n>>";
    string komisN = wczytaj(test);
    cout<<"Jaka jest marza narzucana przez ten komis?\n>>";
    auto marza = wczytaj<double>(test);
    while(marza<0||marza>100000)
    {
        if(marza<0)
            cout<<"\nPodana marza jest ujemna! Myslisz, ze komis doplaca do sprzedawanych samochodow?\n";
        else
            cout<<"\nTa marza jest za duza i godzi w zasady sprawiedliwego handlu!\n";
        cout<<"Podaj poprawna marze\n>>";
        marza = wczytaj<double>(test);
    }
    Komis komis(komisN, marza);
    cout<<"\nUdalo sie stworzyc komis\n";
    //-------------------------------------------------------

    //menu glowne - podaje podstawowe mozliwosci wykonywane za pomoca odpowiednich funkcji
    int nr=-1; //nr - numer czynnosci wybieranej przez uzytkownika w menu
    while (nr!=0) {         //po wybraniu 0 program konczy swoje dzialanie
        cout << "\n\n___________________| MENU |___________________\n";
        cout << "Chcesz zobaczyc liste marek? Wybierz 1\n"
             << "Chcesz dodac nowa fabryke? Wybierz 2\n"
             << "Chcesz zobaczyc liste pojazdow z ktorejs z fabryk? Wybierz 3\n"
             << "Chcesz stworzyc nowy pojazd? Wybierz 4\n"
             << "Chcesz sprzedac ktorys z pojazdow z fabryki? Wybierz 5\n"
             << "Chcesz gdzies pojechac? Wybierz 6\n"
             << "Chcesz zmienic kolor pojazdu? Wybierz 7\n"
             << "Chcesz kupic pojazd z komisu? Wybierz 8\n"
             << "Chcesz sprzedac pojazd do komisu? Wybierz 9\n"
             << "Aby zakonczyc wybierz 0\n";
        cout<<"______________________________________________\n\n";
        cout<<"Twoj wybor:\n>>";
        nr=wczytaj<int>(test);

        switch (nr) {
            case 0:
                break;
            case 1:
                try {
                    WypiszFabryki(koncern, &iloscFabryk);
                }
                catch(BrakFabryk &bf) {
                    cerr<<"Blad wypisywania fabryk: "<<bf.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                break;
            case 2:
                NowaFabryka(koncern, &iloscFabryk);
                break;
            case 3:
                try {
                    ListaPojazdow(koncern, iloscFabryk);
                }
                catch(BrakFabryk &bf) {
                    cerr<<"Blad wypisywania pojazdow: "<<bf.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                catch(BrakPojazdow &bp) {
                    cerr<<"Blad wypisywania pojazdow: "<<bp.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                break;
            case 4:
                try {
                    NowyPojazd(koncern, iloscFabryk);
                }
                catch(BrakFabryk &bf) {
                  cerr<<"Blad dodawania pojazdu: "<<bf.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                break;
            case 5:
                Sprzedaj(koncern, iloscFabryk, sprzedane, &iloscSprzedanych);
                break;
            case 6:
                JedzPojazdem(koncern, iloscFabryk);
                break;
            case 7:
                ZmienKolor(koncern, iloscFabryk, lakiernik);
                break;
            case 8:
                try{
                    KupZKomisu(&komis, sprzedane, &iloscSprzedanych);
                }
                catch(BrakPojazdow &bp) {
                    cerr<<"Blad komisu: "<<bp.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                break;
            case 9:
                SprzedajDoKomisu(&komis, sprzedane, &iloscSprzedanych);
                break;
            default:
                cout << "Niepoprawny wybor, sproboj jeszcze raz."<<endl;
        }
    }


    cout<<"\n\n______________________________________________";
    cout<<"\nZakonczono korzystanie z programu. Milego dnia!\n";
    cout<<"______________________________________________\n";

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// funkcje do pobierania danych
template <typename T>
T wczytaj(bool t) {
    T wartosc;
    if(t) {
        *plikTestowy>>wartosc;
        cout<<wartosc<<endl;
    }
    else cin>>wartosc;
    return wartosc;
}

string wczytaj(bool t) {
    string s;
    if(t) {
        while(s.empty())
            getline(*plikTestowy, s, '\n');
        cout<<s<<endl;
    }
    else {
        while (s.empty())
            getline(cin, s, '\n');
    }
    return s;
}

//----------------------------------------------------------------------------------------------------------------------
//funkcje do obslugi menu
void WypiszFabryki(Fabryka** koncern, const int* iloscFabryk) {
    if(*iloscFabryk==0)     //jezeli nie ma fabryk w koncernie, rzucany jest wyjątek
    {
        throw BrakFabryk();
    }
    else{
    cout<<"\n_______________| LISTA FABRYK |_______________\n";
    for (int i=0; i<(*iloscFabryk) ; i++)
    {
        cout << i+1 << ". "<<koncern[i]->jakaMarka()<<endl;
    }
    cout<<"______________________________________________\n";
    }
}

void NowaFabryka(Fabryka** koncern, int* iloscFabryk)
{
    if(*iloscFabryk<MAX_FABRYK) {
        cout << "Podaj nazwe marki:\n>>";
        string marka=wczytaj(test);

        cout<<"Podaj ladownosc dla samochodow tej marki\n>>";
        int ladownoscSamochod=wczytaj<int>(test);
        while(ladownoscSamochod<50||ladownoscSamochod>500)
        {
            cout<<"Podana ladownosc jest niepoprawna, podaj inna (pomiedzy 50 a 500 kg)\n>>";
            ladownoscSamochod = wczytaj<int>(test);
        }

        cout<<"Podaj ladownosc dla motocykli tej marki\n>>";
        int ladownoscMotocykl = wczytaj<int>(test);
        while(ladownoscMotocykl<0||ladownoscMotocykl>200)
        {
            cout<<"Podana ladownosc jest niepoprawna, podaj inna (pomiedzy 0 a 200 kg)\n>>";
            ladownoscMotocykl = wczytaj<int>(test);
        }

        auto *nowaFabryka = new Fabryka(marka, ladownoscMotocykl, ladownoscSamochod);

        Dopisz(nowaFabryka, koncern, iloscFabryk);

        cout << "\nUtworzono nowa fabryke.\n";
        //(*iloscFabryk)++;
        cout<<"Aktualna lista fabryk:\n";
        WypiszFabryki(koncern, iloscFabryk);
    }
    else {
        cout<<"\nNie mozesz dodac wiecej fabryk (maksymalna ilosc fabryk wynosi "<<MAX_FABRYK<<").\n";
    }
}

void ListaPojazdow(Fabryka** koncern, int iloscFabryk)
{
    WypiszFabryki(koncern, &iloscFabryk);
    cout<<"\nZ ktorej fabryki wypisac pojazdy?\n";      //wypisanie listy fabryk do wyboru, w przypadu ich braku daje mozliwosc dodania nowej
    cout<<"Podaj numer fabryki: \n>>";
    int nr = wczytaj<int>(test);
    while(nr-1<0||nr-1>iloscFabryk)
    {
        cout<<"\nPodana bledna wartosc, wybierz liczbe od 1 do "<<iloscFabryk<<"\n>>";
        nr = wczytaj<int>(test);
    }
    if(koncern[nr-1]->ilePojazdow==0)
    {
        throw BrakPojazdow();
    }
    else
    {
        cout<<"\n______________| LISTA POJAZDOW |______________\n";
        koncern[nr-1]->wypiszPojazdy();             //wypisanie pojazdow przy pomocy metody z fabryki
        cout<<"\n______________________________________________\n";
    }
}

void NowyPojazd(Fabryka** koncern, int iloscFabryk)
{
    WypiszFabryki(koncern, &iloscFabryk);
    cout<<"\nDo ktorej fabryki chcesz dodac pojazd?\n";
    cout<<"Podaj numer fabryki:\n>>";
    int nr = wczytaj<int>(test);
    while(nr-1<0||nr>iloscFabryk)
    {
        cout<<"\nPodana bledna wartosc, wybierz liczbe od 1 do "<<iloscFabryk<<"\n>>";
        nr = wczytaj<int>(test);
    }
    cout<<"\nJaki rodzaj pojazdu chcesz wyprodukowac?\nSamochod - Wybierz 1\nMotocykl - Wybierz 2\nRower - Wybierz 3\n"
          "To pomylka, nie chcesz produkowac nic - Wybierz 0\n>>";
    int wybor=wczytaj<int>(test);

    while (wybor!=1&&wybor!=2&&wybor!=3)
    {
        cout<<"Podana bledna wartosc, wybierz liczbe od 1 do 3\n>>";
        wybor=wczytaj<int>(test);
    }

    switch (wybor) {
        case 1:
            NowySamochod(koncern, nr);
            break;
        case 2:
            NowyMotocykl(koncern, nr);
            break;
        case 3:
            NowyRower(koncern, nr);
            break;
        default:
            cout<<"\nBledna wartosc\n";
        }

    cout<<"Do fabryki "<<koncern[nr-1]->jakaMarka()<<" dodano nowy pojazd.\n";
    cout<<"______________________________________________\n";
}

void Sprzedaj(Fabryka** koncern, int iloscFabryk, Pojazd** sprzedane, int* iloscSprzedanych)
{
    Fabryka* fabryka = wybierzFabryke(koncern, iloscFabryk);
    int pojazdNr = wybierzPojazd(*fabryka);

    cout<<"Podaj nowego wlasciciela: \n>>";
    string wlasciciel=wczytaj(test);

    Dopisz(fabryka->sprzedaj(wlasciciel, pojazdNr), sprzedane, iloscSprzedanych);
    cout<<"\nPojazd zostal sprzedany\n";
}

void JedzPojazdem(Fabryka** koncern, int iloscFabryk)
{
    cout<<"\nPodaj dlugosc trasy:\n>>";
    int trasa = wczytaj<int>(test);
    Fabryka* fabryka=wybierzFabryke(koncern, iloscFabryk);  //wybor fabryki z listy
    Pojazd* pojazd=fabryka->wybierzPojazd(wybierzPojazd(*fabryka)); //wybor pojazdu z fabryki
    pojazd->jedz(trasa);
}

void ZmienKolor(Fabryka** koncern, int iloscFabryk, Lakiernik* lakiernik)
{
    cout<<"\nWitaj, jestes u lakiernika!\nJaki kolor ma miec Twoj pojazd?\n>>";
    string nowyKolor = wczytaj(test);
    Fabryka* fabryka = wybierzFabryke(koncern, iloscFabryk);
    lakiernik->lakieruj(fabryka->wybierzPojazd(wybierzPojazd(*fabryka)), nowyKolor);
}

void KupZKomisu(Komis *komis, Pojazd **sprzedane, int *iloscSprzedanych)
{
    if(komis->plac.empty())
        throw BrakPojazdow();
    komis->wypiszPlac();
    cout<<"\nKtory pojazd chcesz kupic? Podaj jego numer\n>>";
    int nr=wczytaj<int>(test);

    while(nr-1>komis->plac.size()||nr-1<0)
    {
        cout<<"Podano nieprawidlowy numer. Podaj numer z zakresu 1 - "<<komis->plac.size()<<"\n>>";
        nr=wczytaj<int>(test);
    }
    nr--;       //zmiana indeksowania (od 0)
    cout<<"\nWybrales pojazd o parametrach: ";
    komis->plac[nr].wypiszPojazd();
    cout<<"\nJego cena wynosi "<<komis->cenaSprzedazy(&(komis->plac[nr]))<<"zl. Czy chcesz zakupic ten pojazd?\n"
                                                                           "Tak - wybierz 1, NIE - wybierz 0\n>>";
    bool transakcja = wczytaj<bool>(test);
    if(transakcja)
    {
        cout<<"Podaj nowego wlasciciela:\n>>";
        string wlasciciel = wczytaj(test);
        Dopisz(komis->komisSprzedaje(nr, wlasciciel), sprzedane, iloscSprzedanych);
        cout<<"\nKupiles pojazd. Szerokiej drogi!\n";
    }
    else
        cout<<"\nZrezygnowales z zakupu pojazdu. Do widzenia!\n";

}

void SprzedajDoKomisu(Komis *komis, Pojazd **sprzedane, int *iloscSprzedanych)
{
    if(*iloscSprzedanych>0) {
        cout << "\nPojazdy do wyboru: \n";
        for (int i = 0; i < *iloscSprzedanych; i++) {
            cout << "\nPojazd " << i + 1 << ":\n";
            sprzedane[i]->wypiszPojazd();
        }
        cout << "\nKtory pojazd chcesz sprzedac? Podaj numer:\n>>";
        int nr = wczytaj<int>(test);
        while(nr-1<0||nr-1>*iloscSprzedanych|| sprzedane[nr-1]->typPojazdu()=="rower")
        {
            cout<<"\nPodana wartosc jest bledna, wybierz pojazd od 1 do "<<*iloscSprzedanych<<
            "\nWez pod uwage, ze komis nie skupuje rowerow.\n>>";
            nr = wczytaj<int>(test);
        }
        nr--;       //zmiana indeksowania
        komis->komisKupuje(dynamic_cast<pojazdSilnikowy *>(sprzedane[nr]));
        sprzedane[nr] = nullptr;
        for (int i = nr; i < *iloscSprzedanych; i++) {
            sprzedane[i] = sprzedane[i + 1];
        }
        (*iloscSprzedanych)--;
    }
    else
        cout<<"\nBrak pojazdow do sprzedania\n";
}

//----------------------------------------------------------------------------------------------------------------------
//funkcje do tworzenia nowych pojazdow

void NowySamochod(Fabryka** koncern, int nr)
{
    cout<<"Ile Twoj samochod ma drzwi?\n>>";
    int drzwi=wczytaj<int>(test);
    while (drzwi<1||drzwi>6)
    {
        cout<<"\nPodano bledna ilosc drzwi, sprobuj jeszcze raz (wybierz liczbe od 1 do 6)\n>>";
        drzwi=wczytaj<int>(test);
    }

    cout<<"Jaki ma kolor?\n>>";
    string kolor = wczytaj(test);
    koncern[nr-1]->nowySamochod(drzwi, kolor);
}

void NowyMotocykl(Fabryka** koncern, int nr)
{
    cout<<"Jaki kolor ma Twoj motocykl?\n>>";
    string kolor = wczytaj(test);
    koncern[nr-1]->nowyMotocykl(kolor);
}

void NowyRower(Fabryka** koncern, int nr)
{
    cout<<"Jaki kolor ma Twoj rower?\n>>";
    string kolor = wczytaj(test);
    cout<<"\nCzy ma koszyk?\nTAK - 1, NIE - 0\n>>";
    bool koszyk = wczytaj<bool>(test);
    koncern[nr-1]->nowyRower(kolor, koszyk);
}


//----------------------------------------------------------------------------------------------------------------------
//funkcje pomocnicze do funkcji menu
Fabryka* wybierzFabryke(Fabryka** koncern, int iloscFabryk) {
    WypiszFabryki(koncern, &iloscFabryk);
    cout << "Z ktorej fabryki chcesz wybrac pojazd?\n";
    cout << "Podaj numer fabryki:\n>>";
    int nr = wczytaj<int>(test);
    while(nr-1<0||nr-1>iloscFabryk)
    {
        cout<<"Podana bledna wartosc, wybierz liczbe od 1 do "<<iloscFabryk<<"\n>>";
        nr = wczytaj<int>(test);
    }
    return koncern[nr-1];
}

int wybierzPojazd(Fabryka fabryka)
{
    cout<<"\n\nPojazdy w fabryce:\n";
    fabryka.wypiszPojazdy();
    cout<<"\nKtory pojazd z fabryki wybierasz?\n>>";
    int nr = wczytaj<int>(test);
    return nr-1;
}