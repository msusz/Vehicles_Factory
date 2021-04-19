#ifndef SUSZCZYKMARCELINA_EXCEPTIONS_H
#define SUSZCZYKMARCELINA_EXCEPTIONS_H

struct WrongContent : exception {

    std::string massage;
    virtual const char* what() const noexcept  {return "WrongContent";}
    explicit WrongContent(std::string msg) : massage(std::move(msg)) {}
};

struct NoFactories : public WrongContent {
    const char* what() const noexcept override {return "NoFactories";}
    explicit NoFactories() : WrongContent("No factories") {}
};

struct NoVehicles : public WrongContent {
    const char* what() const noexcept override {return "NoVehicles";}
    explicit NoVehicles() : WrongContent("No Vehicles") {}
};

#endif //SUSZCZYKMARCELINA_EXCEPTIONS_H
