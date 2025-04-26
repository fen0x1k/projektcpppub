#include "BazaSamochodow.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <sstream>
using namespace std;

void BazaSamochodow::dodajSamochod() {
    string marka, model;
    int rocznik, przebieg;
    double cena;

    cout << "Podaj marke (lub wpisz ANULUJ, aby anulowac): ";
    cin >> marka;
    if (marka == "ANULUJ") {
        cout << "Dodawanie anulowane.\n";
        return;
    }

    cout << "Podaj model (lub wpisz ANULUJ, aby anulowac): ";
    cin >> model;
    if (model == "ANULUJ") {
        cout << "Dodawanie anulowane.\n";
        return;
    }

    cout << "Podaj rocznik (wpisz -1, aby anulowac): ";
    cin >> rocznik;
    if (rocznik == -1) {
        cout << "Dodawanie anulowane.\n";
        return;
    }

    cout << "Podaj przebieg w km (wpisz -1, aby anulowac): ";
    cin >> przebieg;
    if (przebieg == -1) {
        cout << "Dodawanie anulowane.\n";
        return;
    }

    cout << "Podaj cene w PLN (wpisz -1, aby anulowac): ";
    cena = wczytajDouble();
    if (cena == -1) {
        cout << "Dodawanie anulowane.\n";
        return;
    }

    samochody.push_back(Samochod(marka, model, rocznik, przebieg, cena));
    cout << "Samochod zostal dodany.\n";
}

void BazaSamochodow::edytujSamochod(int indeks) {
    if (indeks >= 0 && indeks < samochody.size()) {
        cout << "\n=== Edycja samochodu ===\n";
        wyswietlNaglowek();
        wyswietlSamochod(indeks, samochody[indeks]);

        cout << "\nCo chcesz edytowac?\n";
        cout << "1. Marka\n";
        cout << "2. Model\n";
        cout << "3. Rocznik\n";
        cout << "4. Przebieg\n";
        cout << "5. Cena\n";
        cout << "0. Anuluj\n";
        cout << "Twoj wybor: ";
        int wybor = wczytajInt();

        switch (wybor) {
        case 1: {
            cout << "Podaj nowa marke: ";
            string nowaMarka;
            cin >> nowaMarka;
            samochody[indeks].ustawMarke(nowaMarka);
            cout << "Marka zostala zmieniona.\n";
            break;
        }
        case 2: {
            cout << "Podaj nowy model: ";
            string nowyModel;
            cin >> nowyModel;
            samochody[indeks].ustawModel(nowyModel);
            cout << "Model zostal zmieniony.\n";
            break;
        }
        case 3: {
            cout << "Podaj nowy rocznik: ";
            int nowyRocznik = wczytajInt();
            if (nowyRocznik < 0) {
                cout << "Nieprawidlowy rocznik. Operacja anulowana.\n";
                return;
            }
            samochody[indeks].ustawRocznik(nowyRocznik);
            cout << "Rocznik zostal zmieniony.\n";
            break;
        }
        case 4: {
            cout << "Podaj nowy przebieg (w km): ";
            int nowyPrzebieg = wczytajInt();
            if (nowyPrzebieg < 0) {
                cout << "Nieprawidlowy przebieg. Operacja anulowana.\n";
                return;
            }
            samochody[indeks].ustawPrzebieg(nowyPrzebieg);
            cout << "Przebieg zostal zmieniony.\n";
            break;
        }
        case 5: {
            cout << "Podaj nowa cene (PLN): ";
            double nowaCena = wczytajDouble();
            if (nowaCena < 0) {
                cout << "Nieprawidlowa cena. Operacja anulowana.\n";
                return;
            }
            samochody[indeks].ustawCene(nowaCena);
            cout << "Cena zostala zmieniona.\n";
            break;
        }
        case 0:
            cout << "Edycja anulowana.\n";
            break;
        default:
            cout << "Nieprawidlowy wybor.\n";
            break;
        }
    }
    else {
        cout << "Nieprawidlowy indeks samochodu.\n";
    }
}

void BazaSamochodow::usunSamochod(int indeks) {
    if (indeks >= 0 && indeks < samochody.size()) {
        cout << "Wybrany samochod:\n";
        wyswietlNaglowek();
        wyswietlSamochod(indeks, samochody[indeks]);
        cout << "Czy na pewno chcesz usunac ten samochod? (T/N): ";
        char potwierdzenie;
        cin >> potwierdzenie;

        if (potwierdzenie == 'T' || potwierdzenie == 't') {
            samochody.erase(samochody.begin() + indeks);
            cout << "Samochod zostal usuniety.\n";
        }
        else {
            cout << "Usuwanie anulowane.\n";
        }
    }
    else {
        cout << "Nieprawidlowy indeks samochodu.\n";
    }
}

void BazaSamochodow::wyswietlNaglowek() const {
    cout << left << setw(4) << "Lp."
        << setw(20) << "Marka"
        << setw(20) << "Model"
        << setw(10) << "Rocznik"
        << setw(12) << "Przebieg"
        << setw(12) << " Cena" << endl;
    cout << string(81, '-') << endl;
}

void BazaSamochodow::wyswietlSamochod(size_t indeks, const Samochod& s) const {
    cout << left << setw(4) << indeks + 1
        << setw(20) << s.pobierzMarke()
        << setw(20) << s.pobierzModel()
        << setw(10) << s.pobierzRocznik()
        << setw(10) << s.pobierzPrzebieg() << "km "
        << setw(10) << fixed << setprecision(2) << s.pobierzCene() << " PLN" << endl;
}

void BazaSamochodow::wyswietlWszystkie() const {
    if (samochody.empty()) {
        cout << "Brak samochodow w bazie do wyswietlenia.\n";
        return;
    }
    wyswietlNaglowek();
    for (size_t i = 0; i < samochody.size(); ++i) {
        wyswietlSamochod(i, samochody[i]);
    }
}

void BazaSamochodow::wyswietlWszystkieSortowanie() const {
    if (samochody.empty()) {
        cout << "Brak samochodow w bazie do wyswietlenia.\n";
        return;
    }
    vector<Samochod> kopia = samochody;
    sortujPoWybranymKryterium(kopia);
    wyswietlNaglowek();
    for (size_t i = 0; i < kopia.size(); ++i) {
        wyswietlSamochod(i, kopia[i]);
    }
}
void BazaSamochodow::wyswietlSamochodyFiltrowanie() const {
    if (samochody.empty()) {
        cout << "Brak samochodow w bazie.\n";
        return;
    }

    cout << "\n=== Filtrowanie wielokryterialne ===\n";

    bool filtrMarka = false, filtrPrzebieg = false, filtrCena = false, filtrRocznik = false;
    char wybor;

    cout << "Filtrowac po marce? (T/N): ";
    wybor = wczytajZnak();
    if (wybor == 'T') filtrMarka = true;

    cout << "Filtrowac po przebiegu? (T/N): ";
    wybor = wczytajZnak();
    if (wybor == 'T') filtrPrzebieg = true;

    cout << "Filtrowac po cenie? (T/N): ";
    wybor = wczytajZnak();
    if (wybor == 'T') filtrCena = true;

    cout << "Filtrowac po roczniku? (T/N): ";
    wybor = wczytajZnak();
    if (wybor == 'T') filtrRocznik = true;

    string litera;
    int przebiegOd = 0, przebiegDo = INT_MAX;
    double cenaOd = 0, cenaDo = 1e9;
    int rocznikOd = 0, rocznikDo = 9999;

    if (filtrMarka) {
        cout << "Podaj litere, od ktorej zaczyna sie marka: ";
        litera = wczytajZnak();
    }
    if (filtrPrzebieg) {
        cout << "Podaj minimalny przebieg (km): ";
        przebiegOd = wczytajInt();
        cout << "Podaj maksymalny przebieg (km): ";
        przebiegDo = wczytajInt();
        if (przebiegOd < 0 || przebiegDo < 0 || przebiegOd > przebiegDo) {
            cout << "Nieprawidlowe dane przebiegu. Anulowanie filtrowania.\n";
            return;
        }
    }
    if (filtrCena) {
        cout << "Podaj minimalna cene (PLN): ";
        cenaOd = wczytajDouble();
        cout << "Podaj maksymalna cene (PLN): ";
        cenaDo = wczytajDouble();
        if (cenaOd < 0 || cenaDo < 0 || cenaOd > cenaDo) {
            cout << "Nieprawidlowe dane ceny. Anulowanie filtrowania.\n";
            return;
        }
    }
    if (filtrRocznik) {
        cout << "Podaj minimalny rocznik: ";
        rocznikOd = wczytajInt();
        cout << "Podaj maksymalny rocznik: ";
        rocznikDo = wczytajInt();
        if (rocznikOd < 0 || rocznikDo < 0 || rocznikOd > rocznikDo) {
            cout << "Nieprawidlowe dane rocznika. Anulowanie filtrowania.\n";
            return;
        }
    }

    vector<Samochod> filtr;

    for (const auto& s : samochody) {
        bool pasuje = true;

        if (filtrMarka && toupper(s.pobierzMarke()[0]) != toupper(litera[0]))
            pasuje = false;
        if (filtrPrzebieg && !(s.pobierzPrzebieg() >= przebiegOd && s.pobierzPrzebieg() <= przebiegDo))
            pasuje = false;
        if (filtrCena && !(s.pobierzCene() >= cenaOd && s.pobierzCene() <= cenaDo))
            pasuje = false;
        if (filtrRocznik && !(s.pobierzRocznik() >= rocznikOd && s.pobierzRocznik() <= rocznikDo))
            pasuje = false;

        if (pasuje)
            filtr.push_back(s);
    }

    if (filtr.empty()) {
        cout << "Brak samochodow spelniajacych wszystkie kryteria.\n";
    }
    else {
        wyswietlNaglowek();
        for (size_t i = 0; i < filtr.size(); ++i) {
            wyswietlSamochod(i, filtr[i]);
        }

        cout << "\nCzy chcesz zapisac wyniki do pliku? (T/N): ";
        char decyzja = wczytajZnak();
        if (decyzja == 'T') {
            cout << "Podaj nazwe pliku: ";
            string nazwaPliku;
            cin >> nazwaPliku;
            ofstream plik(nazwaPliku);
            if (plik.is_open()) {
                for (const auto& s : filtr) {
                    plik << s.pobierzMarke() << ";" << s.pobierzModel() << ";"
                        << s.pobierzRocznik() << ";" << s.pobierzPrzebieg() << ";"
                        << s.pobierzCene() << endl;
                }
                cout << "Wyniki zapisane do pliku.\n";
            }
            else {
                cout << "Nie udalo sie otworzyc pliku do zapisu.\n";
            }
        }
    }
}

void BazaSamochodow::posortujBaze() {
    sortujPoWybranymKryterium(samochody);
    cout << "Baza danych zostala posortowana.\n";
}

void BazaSamochodow::wczytajZPliku(const string& nazwaPliku, bool dodaj) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cout << "Brak pliku o podanej nazwie.\n";
        return;
    }

    if (plik.peek() == ifstream::traits_type::eof()) {
        cout << "Plik jest pusty.\n";
        return;
    }

    if (!dodaj) {
        samochody.clear();
    }

    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        string marka, model, rocznikStr, przebiegStr, cenaStr;
        if (!getline(ss, marka, ';') ||
            !getline(ss, model, ';') ||
            !getline(ss, rocznikStr, ';') ||
            !getline(ss, przebiegStr, ';') ||
            !getline(ss, cenaStr, ';')) {
            cout << "Bledny format danych w pliku. Linia pominieta.\n";
            continue;
        }

        try {
            int rocznik = stoi(rocznikStr);
            int przebieg = stoi(przebiegStr);
            double cena = stod(cenaStr);
            samochody.push_back(Samochod(marka, model, rocznik, przebieg, cena));
        }
        catch (...) {
            cout << "Bledny format danych w pliku. Linia pominieta.\n";
            continue;
        }
    }

    cout << "Wczytywanie zakonczone.\n";
}

void BazaSamochodow::zapiszDoPliku(const string& nazwaPliku) const {
    ofstream plik(nazwaPliku);
    if (plik.is_open()) {
        for (const auto& samochod : samochody) {
            plik << samochod.pobierzMarke() << ";" << samochod.pobierzModel() << ";"
                << samochod.pobierzRocznik() << ";" << samochod.pobierzPrzebieg() << ";"
                << samochod.pobierzCene() << endl;
        }
        cout << "Zapis do pliku zakonczony.\n";
        plik.close();
    }
}

void BazaSamochodow::generujStatystyki() const {
    if (samochody.empty()) {
        cout << "Brak samochodow w bazie. Nie mozna wygenerowac statystyk.\n";
        return;
    }

    int wybor;
    do {
        cout << "\n=== Generowanie statystyk ===\n";
        cout << "1. Srednia cena\n";
        cout << "2. Najtanszy samochod\n";
        cout << "3. Najdrozszy samochod\n";
        cout << "4. Mediana przebiegu\n";
        cout << "5. Odchylenie standardowe cen\n";
        cout << "6. Wszystkie statystyki\n";
        cout << "0. Powrot do menu glownego\n";
        cout << "Twoj wybor: ";
        wybor = wczytajInt();

        switch (wybor) {
        case 1: generujSredniaCene(); break;
        case 2: generujNajtanszySamochod(); break;
        case 3: generujNajdrozszySamochod(); break;
        case 4: generujMedianePrzebiegu(); break;
        case 5: generujOdchylenieStandardoweCen(); break;
        case 6: generujWszystkieStatystyki(); break;
        case 0: cout << "Powrot do menu glownego.\n"; break;
        default: cout << "Nieprawidlowy wybor.\n"; break;
        }
    } while (wybor != 0);
}

void BazaSamochodow::generujSredniaCene() const {
    double suma = 0;
    for (const auto& samochod : samochody) {
        suma += samochod.pobierzCene();
    }
    cout << fixed << setprecision(2);
    cout << "Srednia cena: " << suma / samochody.size() << " PLN\n";
}

void BazaSamochodow::generujNajtanszySamochod() const {
    auto it = min_element(samochody.begin(), samochody.end(), [](const Samochod& a, const Samochod& b) {
        return a.pobierzCene() < b.pobierzCene();
        });
    cout << fixed << setprecision(2);
    cout << "Najtanszy samochod: " << it->pobierzMarke() << " " << it->pobierzModel() << " (" << it->pobierzCene() << " PLN)\n";
}

void BazaSamochodow::generujNajdrozszySamochod() const {
    auto it = max_element(samochody.begin(), samochody.end(), [](const Samochod& a, const Samochod& b) {
        return a.pobierzCene() < b.pobierzCene();
        });
    cout << fixed << setprecision(2);
    cout << "Najdrozszy samochod: " << it->pobierzMarke() << " " << it->pobierzModel() << " (" << it->pobierzCene() << " PLN)\n";
}

void BazaSamochodow::generujMedianePrzebiegu() const {
    vector<int> przebiegi;
    for (const auto& samochod : samochody) {
        przebiegi.push_back(samochod.pobierzPrzebieg());
    }
    sort(przebiegi.begin(), przebiegi.end());
    double mediana;
    if (przebiegi.size() % 2 == 0) {
        mediana = (przebiegi[przebiegi.size() / 2 - 1] + przebiegi[przebiegi.size() / 2]) / 2.0;
    }
    else {
        mediana = przebiegi[przebiegi.size() / 2];
    }
    cout << fixed << setprecision(2);
    cout << "Mediana przebiegu: " << mediana << " km\n";
}

void BazaSamochodow::generujOdchylenieStandardoweCen() const {
    double suma = 0;
    vector<double> ceny;
    for (const auto& samochod : samochody) {
        suma += samochod.pobierzCene();
        ceny.push_back(samochod.pobierzCene());
    }
    double srednia = suma / ceny.size();
    double sumaOdchylen = 0;
    for (double cena : ceny) {
        sumaOdchylen += (cena - srednia) * (cena - srednia);
    }
    cout << fixed << setprecision(2);
    cout << "Odchylenie standardowe cen: " << sqrt(sumaOdchylen / ceny.size()) << " PLN\n";
}

void BazaSamochodow::generujWszystkieStatystyki() const {
    generujSredniaCene();
    generujNajtanszySamochod();
    generujNajdrozszySamochod();
    generujMedianePrzebiegu();
    generujOdchylenieStandardoweCen();
}

void BazaSamochodow::sortujPoWybranymKryterium(vector<Samochod>& bazaDoSortowania) const {
    int wybor;
    cout << "\n=== Wybierz kryterium sortowania ===\n";
    cout << "1. Cena\n";
    cout << "2. Rocznik\n";
    cout << "3. Przebieg\n";
    cout << "4. Marka\n";
    cout << "5. Model\n";
    cout << "Wybierz opcje: ";
    wybor = wczytajInt();

    int kierunek;
    cout << "1. Rosnaco\n";
    cout << "2. Malejaco\n";
    cout << "Wybierz kierunek: ";
    kierunek = wczytajInt();

    bool rosnaco = (kierunek == 1);
    switch (wybor) {
    case 1:
        if (rosnaco)
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzCene() < b.pobierzCene(); });
        else
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzCene() > b.pobierzCene(); });
        break;
    case 2:
        if (rosnaco)
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzRocznik() < b.pobierzRocznik(); });
        else
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzRocznik() > b.pobierzRocznik(); });
        break;
    case 3:
        if (rosnaco)
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzPrzebieg() < b.pobierzPrzebieg(); });
        else
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzPrzebieg() > b.pobierzPrzebieg(); });
        break;
    case 4:
        if (rosnaco)
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzMarke() < b.pobierzMarke(); });
        else
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzMarke() > b.pobierzMarke(); });
        break;
    case 5:
        if (rosnaco)
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzModel() < b.pobierzModel(); });
        else
            sort(bazaDoSortowania.begin(), bazaDoSortowania.end(), [](const Samochod& a, const Samochod& b) { return a.pobierzModel() > b.pobierzModel(); });
        break;
    default:
        cout << "Nieprawidlowy wybor.\n";
        break;
    }
}

int BazaSamochodow::iloscSamochodow() const {
    return samochody.size();
}
int BazaSamochodow::wczytajInt() const {
    int wartosc;
    while (!(cin >> wartosc)) {
        cout << "Blad! Podaj liczbe calkowita: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return wartosc;
}

double BazaSamochodow::wczytajDouble() const {
    double wartosc;
    while (!(cin >> wartosc)) {
        cout << "Blad! Podaj liczbe zmiennoprzecinkowa: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return wartosc;
}

char BazaSamochodow::wczytajZnak() const {
    string input;
    while (true) {
        cin >> input;
        if (input.length() == 1) {
            return toupper(input[0]);
        }
        cout << "Blad! Podaj pojedynczy znak: ";
    }
}
