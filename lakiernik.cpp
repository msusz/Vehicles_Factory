#include "lakiernik.h"

void Lakiernik::lakieruj(Pojazd *pojazd, const string &nowyKolor) {
pojazd->zmienKolor(nowyKolor);
cout<<"\nProsze, oto Twoj pojazd. Jest teraz "<<nowyKolor<<". Mam nadzieje, ze Ci sie podoba!\n";
}
