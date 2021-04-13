#include "varnisher.h"

void Varnisher::varnish(Vehicle *vehicle, const string &newColor) {
vehicle->changeColor(newColor);
cout<<"\nYour vehicle is now "<<newColor<<". I hope you like it!\n";
}
