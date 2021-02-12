#ifndef SUSZCZYKMARCELINA_ETAP3_WYJATKI_H
#define SUSZCZYKMARCELINA_ETAP3_WYJATKI_H

struct BlednaZawartosc : exception {

    std::string massage;
    virtual const char* what() const noexcept  {return "BlednaZawartosc";}
    explicit BlednaZawartosc(std::string msg) : massage(std::move(msg)) {}  //funkcja move przenosi string z jednego miejsca w inne,
                                                                            //czyli w tym przypadku tresc argumentu msg jest przeniesiona
                                                                            //do atrybutu massage
};

struct BrakFabryk : public BlednaZawartosc {
    const char* what() const noexcept override {return "BrakFabryk";}
    explicit BrakFabryk() : BlednaZawartosc("Brak fabryk") {}
};

struct BrakPojazdow : public BlednaZawartosc {
    const char* what() const noexcept override {return "BrakPojazdow";}
    explicit BrakPojazdow () : BlednaZawartosc("Brak pojazdow") {}
};

#endif //SUSZCZYKMARCELINA_ETAP3_WYJATKI_H
