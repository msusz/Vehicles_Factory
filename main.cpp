#include <iostream>
#include <fstream>
#include <thread>
#include "car.h"
#include "factory.h"
#include "comission.h"
#include "varnisher.h"
#include "exceptions.h"

using namespace std;

#define MAX_FACTORIES 5
#define MAX_SOLD 100

//main menu:
void PrintFactories(Factory** consortium, const int *nFactories);
void NewFactories(Fabryka** consortium, int *nFactories);
void ListVehicles(Fabryka** consortium, int nFactories);
void NewVehicle(Fabryka** consortium, int nFactories);
void Sell(Fabryka** consortium, int nFactories, Pojazd** sold, int* nSold);
void Drive(Fabryka** consortium, int nFactories);
void ChangeColor(Fabryka** consortium, int nFactories, Lakiernik* lakiernik);
void BuyFromComission(Comission* comission, Pojazd** sold, int* nSold);
void SellToComission(Comission* comission, Pojazd** sold, int* nSold);

//choosing a vehicle:
Factory* chooseFactory(Factory** consortium, int nFactories);
int choseVehicle(Factory factory);

//creating vehicles:
void NewCar(Factory** consortium, int nr);
void NewMotorcycle(Factory** consortium, int nr);
void NewBicycle(Factory** consortium, int nr);

//input:
template <typename T> T read(bool t);
string read(bool t);

template<typename T> void Add(T* t, T** tab, int *tabSize) {
    tab[*tabSize]=t;
    (*tabSize)++;
}

//file handling
ifstream *textFile;
bool test = false;

//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    textFile = new ifstream();
    if (argc > 1) {
        cout<<"\nTESTING - values are read from a text file "<< argv[argc-1] << endl;
        textFile->open(argv[1]);
        if(textFile->is_open()) {
            cout<<"\nText file was successfully opened\n\n";
            test = true;
        }
    }

    //factories are storedin an array with size defined by MAX_FACTORIES
    Factory* consortium[MAX_FACTORIES];
    int nFactories=0;

    //an array for sold vehicles:
    Vehicles* sold[MAX_SOLD];
    int nSold = 0;

    auto* varnisher=new Varnisher();

    //----------------------------------------CREATING COMISSION
    cout<<"\n Welcome to the Vehicle Management app!\n"
          "Used cars can be bought and sold by a commission.\n\n"
          "What is your comissions name?\n>>";
    string comissionN = read(test);
    cout<<"What is your comissions margin?\n>>";
    auto margin = read<double>(test);
    while(margin<0||margin>100000)
    {
        if(margin<0)
            cout<<"\nThe specified margin is negative! Do you think that the commission surcharge for cars sold?\n";
        else
            cout<<"\nThe specified margin is to big and violates the principles of fair trade!\n";
        cout<<"Pass the right margin\n>>";
        margin = read<double>(test);
    }
    Comission comission(comissionN, margin);
    cout<<"\nThe comission was successfully created\n";
    //-------------------------------------------------------

    //main menu
    int nr=-1; //nr - nr of activity
    while (nr!=0) {         //0 ends the program
        cout << "\n\n___________________| MENU |___________________\n";
        cout << "Do you want to see a list of factories? Choose 1\n"
             << "Do you want to add a new factory? Choose 2\n"
             << "Do you want to see vehicles from a factory? Choose 3\n"
             << "Do you want to create new vehicle? Choose 4\n"
             << "Do you want to buy a vehicle from a factory? Choose 5\n"
             << "Do you want to do a test ride? Choose 6\n"
             << "Do you want to change vehicles color? Choose 7\n"
             << "Do you want to buy a vehicle from the comission? Choose 8\n"
             << "Do you want to sell a vehicle to the comission? Choose 9\n"
             << "To end the program choose 0\n";
        cout<<"______________________________________________\n\n";
        cout<<"Your number of choice:\n>>";
        nr=read<int>(test);

        switch (nr) {
            case 0:
                break;
            case 1:
                try {
                    PrintFactories(consortium, &nFactories);
                }
                catch(NoFactories &bf) {
                    cerr<<"Printing factories error: "<<bf.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                break;
            case 2:
                NewFactory(consortium, &nFactories);
                break;
            case 3:
                try {
                    PrintVehicles(consortium, nFactories);
                }
                catch(NoFactories &bf) {
                    cerr<<"Printing vehicles error: "<<bf.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                catch(NoVehicles &bp) {
                    cerr<<"Printing vehicles error: "<<bp.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                break;
            case 4:
                try {
                    NewVehicle(consortium, nFactories);
                }
                catch(NoFactories &bf) {
                  cerr<<"Creating vehicle error: "<<bf.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                break;
            case 5:
                Sell(consortium, nFactories, sold, &nSold);
                break;
            case 6:
                Drive(consortium, nFactories);
                break;
            case 7:
                ChangeColor(consortium, nFactories, varnisher);
                break;
            case 8:
                try{
                    BuyFromComission(&comission, sold, &nSold);
                }
                catch(NoVehicles &bp) {
                    cerr<<"Comission error: "<<bp.massage<<endl<<endl;
                    this_thread::sleep_for(1s);
                }
                break;
            case 9:
                SellToComiission(&comission, sold, &nSold);
                break;
            default:
                cout << "Wrong choice, try again"<<endl;
        }
    }


    cout<<"\n\n______________________________________________";
    cout<<"\nProgram is closing. Have a good day!\n";
    cout<<"______________________________________________\n";

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// data input
template <typename T>
T read(bool t) {
    T value;
    if(t) {
        *textFile>>value;
        cout<<value<<endl;
    }
    else cin>>value;
    return value;
}

string read(bool t) {
    string s;
    if(t) {
        while(s.empty())
            getline(*textFile, s, '\n');
        cout<<s<<endl;
    }
    else {
        while (s.empty())
            getline(cin, s, '\n');
    }
    return s;
}

//----------------------------------------------------------------------------------------------------------------------
// main menu functions
void PrintFactories(Factory** consortium, const int* nFactory) {
    if(*nFactory==0)
    {
        throw NoFactories();
    }
    else{
    cout<<"\n_______________| FACTORIES |_______________\n";
    for (int i=0; i<(*nFactories) ; i++)
    {
        cout << i+1 << ". "<<consortium[i]->whatBrand()<<endl;
    }
    cout<<"______________________________________________\n";
    }
}

void NewFactory(Factory** consortium, int* nFactories)
{
    if(*nFactories<MAX_FACTORIES) {
        cout << "New brand:\n>>";
        string brand=read(test);

        cout<<"What capacity do cars from this brand have?\n>>";
        int carCapacity=read<int>(test);
        while(carCapacity<50||carCapacity>500)
        {
            cout<<"Your capacity is incorrect, choose between 50 and 500 kg\n>>";
            carCapacity = read<int>(test);
        }

        cout<<"What capacity do motorcycles from this brand have?\n>>";
        int motorcycleCapacity = read<int>(test);
        while(motorcycleCapacity<0||motorcycleCapacity>200)
        {
            cout<<"Your capacity is incorrect, choose between 0 and 200 kg\n>>";
            motorcycleCapacity = read<int>(test);
        }

        auto *newFactory = new Factory(brand, motorcycleCapacity, carCapacity);

        Add(newFactory, consortium, nFactories);

        cout << "\nA new factory was created.\n";

        cout<<"Updated list of factories:\n";
        PrintFactories(consortium, nFactories);
    }
    else {
        cout<<"\nYou can't create more factories (the maximum number of factories is "<<MAX_FACTORIES<<").\n";
    }
}

void PrintVehicles(Factory** consortium, int nFactories)
{
    PrintFactories(consortium, &nFactories);
    cout<<"\nVehicles from which factory do you want to see?\n";
    cout<<"Write a number of chosen factory: \n>>";
    int nr = read<int>(test);
    while(nr-1<0||nr-1>nFactories)
    {
        cout<<"\nWrong value, choose a number between 1 and "<<nFactories<<"\n>>";
        nr = read<int>(test);
    }
    if(consortium[nr-1]->nVehicles==0)
    {
        throw NoVehicles();
    }
    else
    {
        cout<<"\n______________| VEHICLES |______________\n";
        consortium[nr-1]->printVehicles();
        cout<<"\n______________________________________________\n";
    }
}

void NewVehicle(Factory** consortium, int nFactories)
{
    PrintFactories(consortium, &nFactories);
    cout<<"\nIn which factory do you want to create a vehicle?\n";
    cout<<"Write a number of chosen factory:";
    int nr = read<int>(test);
    while(nr-1<0||nr>nFactories)
    {
        cout<<"\nWrong value, choose a number between 1 and "<<iloscFabryk<<"\n>>";
        nr = read<int>(test);
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

    cout<<"Do fabryki "<<consortium[nr-1]->jakaMarka()<<" dodano nowy pojazd.\n";
    cout<<"______________________________________________\n";
}

void Sprzedaj(Fabryka** consortium, int iloscFabryk, Pojazd** sprzedane, int* iloscSprzedanych)
{
    Fabryka* fabryka = wybierzFabryke(consortium, iloscFabryk);
    int pojazdNr = wybierzPojazd(*fabryka);

    cout<<"Podaj nowego wlasciciela: \n>>";
    string wlasciciel=wczytaj(test);

    Dopisz(fabryka->sprzedaj(wlasciciel, pojazdNr), sprzedane, iloscSprzedanych);
    cout<<"\nPojazd zostal sprzedany\n";
}

void JedzPojazdem(Fabryka** consortium, int iloscFabryk)
{
    cout<<"\nPodaj dlugosc trasy:\n>>";
    int trasa = wczytaj<int>(test);
    Fabryka* fabryka=wybierzFabryke(consortium, iloscFabryk);  //wybor fabryki z listy
    Pojazd* pojazd=fabryka->wybierzPojazd(wybierzPojazd(*fabryka)); //wybor pojazdu z fabryki
    pojazd->jedz(trasa);
}

void ZmienKolor(Fabryka** consortium, int iloscFabryk, Lakiernik* lakiernik)
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
