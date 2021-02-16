# Fabryka pojazdów
### Wstęp
Program służy do zarządzania pojazdami: samochodami, motocyklami i rowerami. Każdy z pojazdów musi być najpierw wyprodukowany przez daną fabrykę. Potem może zostać sprzedany prywatnemu właścicielowi. Prywatne pojazdy mogą zostać przelakierowane przez lakiernika, wykorzystane do pokonania trasy (tylko jeśli mają odpowiednią ilość paliwa albo go nie potrzebują) lub sprzedane do komisu, skąd mogą zostać ponownie zakupione.

### main
Po uruchomieniu programu użytkownik podaje nazwę komisu oraz narzucaną przez niego marżę (będzie ona później wykorzystywana do obliczania cen samochodów sprzedawanych z komisu). Następnie użytkownik dostaje możliwość wyboru działania z menu. Może stworzyć fabrykę, wyprodukować pojazd w którejś z istniejących fabryk etc.

### Pojazdy
Program daje możliwość stworzenia trzech typów pojazdów: samochodów, motocykli oraz rowerów. Pojazdy mają wiele powtarzających się cech, dlatego zastosowane zostało dziedziczenie. Motocykle oraz samochody są pochodnymi klasy "Pojazd silnikowy", ponieważ oba typy pojazdów potrzebują m. in. pojemności baku, spalania czy przebiegu. Klasy "Rower" oraz "Pojazd silnikowy" są pochodnymi klasy "Pojazd" (atrybuty potrzebne dla wszystkich klas to np. kolor, ładowność, marka, właściciel).

### Uruchamianie
Program może być uruchomiony bez argumentów i obsługiwany bezpośrednio przez użytkownika lub z wykorzystaniem pliku zawierającego kolejne wartości wczytywane przez program (przykładowy plik: stdinMS.txt).
