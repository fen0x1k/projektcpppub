#include <iostream>
#include "BazaSamochodow.h"
using namespace std;

int main() {
    BazaSamochodow baza;

    baza.wczytajZPliku("samochody.txt", false);
    cout << "Wczytano domyslna baze danych.\n";

    int wybor;
    do {
        cout << "\n=== System zarzadzania samochodami w komisie ===\n";
        cout << "1. Dodaj samochod\n";
        cout << "2. Dodaj samochody z pliku\n";
        cout << "3. Wyswietl wszystkie samochody\n";
        cout << "4. Wyswietl wszystkie samochody (sortowanie)\n";
        cout << "5. Edytuj samochod\n";
        cout << "6. Usun samochod\n";
        cout << "7. Posortuj dane samochodow\n";
        cout << "8. Generuj statystyki\n";
        cout << "9. Zapisz baze do pliku\n";
        cout << "10. Wczytaj baze z pliku\n";
        cout << "0. Wyjscie\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            baza.dodajSamochod();
            break;
        case 2: {
            cout << "Podaj nazwe pliku (lub wpisz 'domyslna'): ";
            string nazwaPliku;
            cin >> nazwaPliku;
            if (nazwaPliku == "domyslna") nazwaPliku = "samochody.txt";
            baza.wczytajZPliku(nazwaPliku, true);
            break;
        }
        case 3:
            baza.wyswietlWszystkie();
            break;
        case 4:
            baza.wyswietlWszystkieSortowanie();
            break;
        case 5: {
            if (baza.iloscSamochodow() == 0) {
                cout << "Brak samochodow w bazie do edycji.\n";
            }
            else {
                baza.wyswietlWszystkie();
                cout << "Podaj numer samochodu do edycji (lub 0 aby anulowac): ";
                int nr = baza.wczytajInt();
                if (nr != 0)
                    baza.edytujSamochod(nr - 1);
                else
                    cout << "Edycja anulowana.\n";
            }
            break;
        }
        case 6: {
            if (baza.iloscSamochodow() == 0) {
                cout << "Brak samochodow w bazie do usuniecia.\n";
            }
            else {
                baza.wyswietlWszystkie();
                cout << "Podaj numer samochodu do usuniecia (lub 0 aby anulowac): ";
                int nr = baza.wczytajInt();
                if (nr != 0)
                    baza.usunSamochod(nr - 1);
                else
                    cout << "Usuwanie anulowane.\n";
            }
            break;
        }

        case 7:
            baza.posortujBaze();
            break;
        case 8:
            baza.generujStatystyki();
            break;
        case 9: {
            cout << "Podaj nazwe pliku (lub wpisz 'domyslna'): ";
            string nazwaPliku;
            cin >> nazwaPliku;
            if (nazwaPliku == "domyslna") nazwaPliku = "samochody.txt";
            baza.zapiszDoPliku(nazwaPliku);
            break;
        }
        case 10: {
            cout << "Podaj nazwe pliku (lub wpisz 'domyslna'): ";
            string nazwaPliku;
            cin >> nazwaPliku;
            if (nazwaPliku == "domyslna") nazwaPliku = "samochody.txt";
            baza.wczytajZPliku(nazwaPliku, false);
            break;
        }
        case 0:
            cout << "Wyjscie z programu.\n";
            break;
        default:
            cout << "Nieprawidlowy wybor.\n";
        }
    } while (wybor != 0);

    return 0;
}
