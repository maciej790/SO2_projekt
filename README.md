Problem Filozofów przy Kolacji (Implementacja SpinLock)

Opis

Ten projekt implementuje klasyczny Problem Filozofów przy Kolacji z wykorzystaniem SpinLock zaimplementowanego za pomocą std::mutex w C++. Program symuluje filozofów, którzy na przemian myślą i jedzą, zapewniając poprawne pobieranie i zwalnianie widelców (pałeczek), aby uniknąć zakleszczeń i warunków wyścigu.

Funkcje

Wykorzystuje wątki (std::thread) do symulacji filozofów.

Implementuje klasę SpinLock do zarządzania dostępem do zasobów współdzielonych.

Zapobiega zakleszczeniom poprzez zapewnienie, że filozofowie o parzystych indeksach podnoszą najpierw lewy widelec, a filozofowie o nieparzystych indeksach podnoszą najpierw prawy widelec.

Wykorzystuje std::chrono do wprowadzenia opóźnień dla realistycznej symulacji.

Jak to działa?

Każdy filozof najpierw myśli przez sekundę.

Następnie próbuje podnieść oba widelce.

Jeśli mu się to uda, je przez sekundę.

Odkłada widelce i wraca do myślenia.

Proces powtarza się określoną liczbę razy.

Wymagania

Kompilator C++ obsługujący C++11 lub nowszy (np. g++, clang++).

Instalacja i Kompilacja

Sklonuj to repozytorium i skompiluj kod za pomocą kompilatora C++:

$ g++ -std=c++11 philosophers.cpp -o philosophers -pthread

Uruchamianie

Uruchom program i podaj liczbę filozofów oraz liczbę iteracji:

$ ./philosophers
Podaj liczbę filozofów (co najmniej 2): 5
Podaj liczbę iteracji (co najmniej 1): 3

Struktura Kodu

Klasa SpinLock

class SpinLock {
private:
    mutex mtx;
public:
    void acquire() { mtx.lock(); }
    void release() { mtx.unlock(); }
};

Ta klasa zapewnia wzajemne wykluczanie za pomocą std::mutex.

Zachowanie Filozofów

void philosopher_task(int id) {
    for (int i = 0; i < max_iterations; ++i) {
        cout << "Filozof " << id << " myśli.\n";
        this_thread::sleep_for(chrono::seconds(1));
        
        if (id % 2 == 0) { // Filozofowie parzyści najpierw podnoszą lewy widelec
            chopsticks[id].acquire();
            chopsticks[(id + 1) % philosopher_count].acquire();
        } else { // Filozofowie nieparzyści najpierw podnoszą prawy widelec
            chopsticks[(id + 1) % philosopher_count].acquire();
            chopsticks[id].acquire();
        }
        
        cout << "Filozof " << id << " je.\n";
        this_thread::sleep_for(chrono::seconds(1));
        
        chopsticks[(id + 1) % philosopher_count].release();
        chopsticks[id].release();
    }
}

Każdy filozof podnosi swoje widelce w sposób zapobiegający zakleszczeniom.

Funkcja Główna

int main() {
    cin >> philosopher_count >> max_iterations;
    chopsticks = new SpinLock[philosopher_count];
    thread* philosophers = new thread[philosopher_count];
    
    for (int i = 0; i < philosopher_count; ++i) {
        philosophers[i] = thread(philosopher_task, i);
    }
    
    for (int i = 0; i < philosopher_count; ++i) {
        philosophers[i].join();
    }
    
    delete[] chopsticks;
    delete[] philosophers;
    return 0;
}

Funkcja ta inicjalizuje wątki filozofów, czeka na ich zakończenie i zwalnia pamięć.

Możliwe Ulepszenia

Wykrywanie zakleszczeń: Implementacja monitora do wykrywania i obsługi zakleszczeń.

Mechanizm limitu czasu: Wprowadzenie limitów czasu dla oczekiwania filozofów.

System priorytetów: Możliwość nadawania priorytetów niektórym filozofom, aby uniknąć zagłodzenia.

Licencja

Ten projekt jest open-source i dostępny na licencji MIT.

Zachęcam do współtworzenia i modyfikowania projektu według potrzeb!

