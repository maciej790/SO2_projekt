# Problem Filozofów (Implementacja SpinLock) - mutexy

## Opis
Ten projekt implementuje klasyczny **Problem Filozofów przy Kolacji** z wykorzystaniem **SpinLock** zaimplementowanego za pomocą `std::mutex` w C++. Program symuluje filozofów, którzy na przemian **myślą** i **jedzą**, zapewniając poprawne pobieranie i zwalnianie widelców, aby uniknąć zakleszczeń i warunków wyścigu.

## Funkcje
- Wykorzystuje **wątki** (`std::thread`) do symulacji filozofów.
- Implementuje klasę **SpinLock** do zarządzania dostępem do zasobów współdzielonych.
- Zapobiega zakleszczeniom poprzez zapewnienie, że **filozofowie o parzystych indeksach** podnoszą najpierw lewy widelec, a **filozofowie o nieparzystych indeksach** podnoszą najpierw prawy widelec.
- Wykorzystuje `std::chrono` do wprowadzenia opóźnień dla realistycznej symulacji.

## Jak to działa?
1. Każdy filozof najpierw **myśli** przez sekundę.
2. Następnie próbuje podnieść **oba** widelce.
3. Jeśli mu się to uda, **je** przez sekundę.
4. Odkłada widelce i wraca do **myślenia**.
5. Proces powtarza się określoną liczbę razy.

## Wymagania
- Kompilator C++ np. gcc
- System Linux np. Ubuntu

## Kompilacja i uruchomienie
- $ g++ -std=c++11 projekt_1.cpp -o projekt_1 -pthread
- $ ./projekt_1


