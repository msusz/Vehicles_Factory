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
void NewFactories(Factory** consortium, int *nFactories);
void ListVehicles(Factory** consortium, int nFactories);
void NewVehicle(Factory** consortium, int nFactories);
void Sell(Factory** consortium, int nFactories, Vehicle** sold, int* nSold);
void Drive(Factory** consortium, int nFactories);
void ChangeColor(Factory** consortium, int nFactories, Vanisher* vanisher);
void BuyFromComission(Comission* comission, Vehicle** sold, int* nSold);
void SellToComission(Comission* comission, Vehicle** sold, int* nSold);

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
        cout<<"\nWrong value, choose a number between 1 and "<<nFactories<<"\n>>";
        nr = read<int>(test);
    }
    cout<<"\nWhat kind of vehicle do you want to create?\nCar - choose 1\nMotorcycle - choose 2\nBicycle - choose 3\n"
          "You changed your mind and don't want to create any vehicle - choose 0\n>>";
    int choice=read<int>(test);

    while (choice!=1&&choice!=2&&choice!=3)
    {
        cout<<"You have chosen a wrong number, choose between 1 and 3\n>>";
        choice=read<int>(test);
    }

    switch (choice) {
        case 1:
            NewCar( consortium, nr);
            break;
        case 2:
            NewMotorcycle( consortium, nr);
            break;
        case 3:
            NewBicycle( consortium, nr);
            break;
        default:
            cout<<"\nWrong value\n";
        }

    cout<<"Factory "<<consortium[nr-1]->whatBrand()<<" has created a new vehicle.\n";
    cout<<"______________________________________________\n";
}

void Sell(Factory** consortium, int nFactories, Vehicle** sold, int* nSold)
{
    Factory* factory = chooseFactory(consortium, nFactories);
    int nVehicle = chooseVehicle(*factory);

    cout<<"New owner: \n>>";
    string owner=read(test);

    Add(factory->sell(owner, nVehicle), sold, nSold);
    cout<<"\nThe vehicle has been sold.\n";
}

void Drive(Factory** consortium, int nFactories)
{
    cout<<"\nWhat is your route length:\n>>";
    int route = read<int>(test);
    Factory* factory=chooseFactory(consortium, nFactories);  //wybor fabryki z listy
    Vehicle* vehicle=factory->chooseVehicle(chooseVehicle(*factory)); //wybor pojazdu z fabryki
    vehicle->drive(route);
}

void ChangeColor(Factory** consortium, int nFactories, Varnisher* varnisher)
{
    cout<<"\nWelcome, you visited the varnisher.\nWhat color do you want your vehicle to be?\n>>";
    string newColor = read(test);
    Factory* factory = chooseFactory( consortium, nFactories);
    varnisher->varnish(factory->chooseVehicle( chooseVehicle(*factory)), newColor);
}

void BuyFromComission(Comission *comission, Vehicle **sold, int *nSold)
{
    if(comission->square.empty())
        throw NoVehicles();
    comission->printSquare();
    cout<<"\nWhich vehicle do you want to buy\n>>";
    int nr=read<int>(test);

    while(nr-1>comission->square.size()||nr-1<0)
    {
        cout<<"You have chosen a wrong number. Choose between 1 - "<<comission->square.size()<<"\n>>";
        nr=read<int>(test);
    }
    nr--;
    cout<<"\nYou have chosen a vehicle with parameters: ";
    comission->square[nr].printVehicle();
    cout<<"\nIt costs "<<comission->sellingPrice(&(comission->square[nr]))<<". Do you want to buy this vehicle?\n"
                                                                           "Yes - choose 1, No - choose 0\n>>";
    bool transaction = read<bool>(test);
    if(transaction)
    {
        cout<<"New owner:\n>>";
        string owner = read(test);
        Add(comission->comissionSells(nr, owner), sold, nSold);
        cout<<"\nYou have bought the vehicle.\n";
    }
    else
        cout<<"\nYou have cancel the purchase.\n";

}

void SellToComission(Comission *comission, Vehicle **sold, int *nSold)
{
    if(*nSold>0) {
        cout << "\nAvialable vehicles: \n";
        for (int i = 0; i < *nSold; i++) {
            cout << "\Vehicle " << i + 1 << ":\n";
            sold[i]->printVehicle();
        }
        cout << "\nWhich vehicle do you want to sell?\n>>";
        int nr = read<int>(test);
        while(nr-1<0||nr-1>*nSold|| sold[nr-1]->vehicleType()=="bicycle")
        {
            cout<<"\nThis value is wrong, choose between 1 and "<<*nSold<<
            "\nRemember, that the comission doesn't but bicycles.\n>>";
            nr = read<int>(test);
        }
        nr--;       //zmiana indeksowania
        comission->comissionBuys(dynamic_cast<motorVehicle *>(sold[nr]));
        sold[nr] = nullptr;
        for (int i = nr; i < *nSold; i++) {
            sold[i] = sold[i + 1];
        }
        (*nSold)--;
    }
    else
        cout<<"\nThere are no vehicles to sell.\n";
}

//----------------------------------------------------------------------------------------------------------------------
//creating new vehicles

void NewCar(Factory** consortium, int nr)
{
    cout<<"How many doors has this car?\n>>";
    int doors=read<int>(test);
    while (doors<1||doors>6)
    {
        cout<<"\nA car can't have that many doors! Choose between 1 and 6\n>>";
        doors=read<int>(test);
    }

    cout<<"What color does it have?\n>>";
    string color = read(test);
    consortium[nr-1]->newCar(doors, color);
}

void NewMotorcycle(Factory** consortium, int nr)
{
    cout<<"What color does your motorcycle have?\n>>";
    string color = read(test);
    consortium[nr-1]->newMotorcycle(color);
}

void NewBicycle(Factory** consortium, int nr)
{
    cout<<"What color does your bicycle have?\n>>";
    string color = read(test);
    cout<<"\nDoes this bicycle have a basket?\nYes - 1, No - 0\n>>";
    bool basket = read<bool>(test);
    consortium[nr-1]->newBicycle(color, basket);
}


//----------------------------------------------------------------------------------------------------------------------
//funkcje pomocnicze do funkcji menu
Factory* chooseFactory(Factory** consortium, int nFactories) {
    PrintFactories( consortium, &nFactories);
    cout << "From which factory do you want to choose a vehicle?\n";
    cout << "Choose a factory number:\n>>";
    int nr = read<int>(test);
    while(nr-1<0||nr-1>nFactories)
    {
        cout<<"This value is wrong, choose between 1 and "<< nFactories <<"\n>>";
        nr = read<int>(test);
    }
    return consortium[nr-1];
}

int chooseVehicle(Factory factory)
{
    cout<<"\n\nVehicles in this factory:\n";
    factory.printVehicles();
    cout<<"\nWhich vehicle do you want to choose?\n>>";
    int nr = read<int>(test);
    return nr-1;
}
