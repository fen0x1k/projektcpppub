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
    if (indeks < 0 || indeks >= samochody.size()) {
        cout << "Nieprawidlowy indeks samochodu.\n";
        return;
    }

    cout << "\n=== Edycja samochodu ===\n";
    wyswietlNaglowek();
    wyswietlSamochod(indeks, samochody[indeks]);
    cout << "Wpisz nowa wartosc lub '-' aby pozostawic bez zmian.\n";

    string input;

    cout << "Nowa marka: ";
    cin >> input;
    if (input != "-") samochody[indeks].ustawMarke(input);

    cout << "Nowy model: ";
    cin >> input;
    if (input != "-") samochody[indeks].ustawModel(input);

    while (true) {
        cout << "Nowy rocznik: ";
        cin >> input;
        if (input == "-") break;
        try {
            int rocznik = stoi(input);
            samochody[indeks].ustawRocznik(rocznik);
            break;
        }
        catch (...) {
            cout << "Niepoprawny rocznik. Sprobuj ponownie lub wpisz '-' aby pominac.\n";
        }
    }

    while (true) {
        cout << "Nowy przebieg (km): ";
        cin >> input;
        if (input == "-") break;
        try {
            int przebieg = stoi(input);
            samochody[indeks].ustawPrzebieg(przebieg);
            break;
        }
        catch (...) {
            cout << "Niepoprawny przebieg. Sprobuj ponownie lub wpisz '-' aby pominac.\n";
        }
    }

    while (true) {
        cout << "Nowa cena (PLN): ";
        cin >> input;
        if (input == "-") break;
        try {
            double cena = stod(input);
            samochody[indeks].ustawCene(cena);
            break;
        }
        catch (...) {
            cout << "Niepoprawna cena. Sprobuj ponownie lub wpisz '-' aby pominac.\n";
        }
    }

    cout << "Dane zostaly zaktualizowane.\n";
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

    cout << "\n=== Generowanie statystyk ===\n";
    cout << "Wybierz pole:\n";
    cout << "1. Cena\n";
    cout << "2. Przebieg\n";
    cout << "Twoj wybor: ";
    int poleWybor = wczytajInt();
    string pole = (poleWybor == 1) ? "cena" : "przebieg";

    cout << "\nWybierz statystyke:\n";
    cout << "1. Minimum\n";
    cout << "2. Maksimum\n";
    cout << "3. Mediana\n";
    cout << "4. Odchylenie standardowe\n";
    cout << "Twoj wybor: ";
    int typWybor = wczytajInt();

    switch (typWybor) {
    case 1: generujStatystyke(pole, "min"); break;
    case 2: generujStatystyke(pole, "max"); break;
    case 3: generujStatystyke(pole, "mediana"); break;
    case 4: generujStatystyke(pole, "odchylenie"); break;
    default: cout << "Nieprawidlowy wybor.\n"; break;
    }
}

void BazaSamochodow::generujStatystyke(const string& pole, const string& typ) const {
    if (samochody.empty()) {
        cout << "Brak danych do analizy.\n";
        return;
    }

    if (typ == "min" || typ == "max") {
        auto comparator = [&](const Samochod& a, const Samochod& b) {
            double valA = (pole == "cena") ? a.pobierzCene() : a.pobierzPrzebieg();
            double valB = (pole == "cena") ? b.pobierzCene() : b.pobierzPrzebieg();
            return valA < valB;
            };

        auto it = (typ == "min")
            ? min_element(samochody.begin(), samochody.end(), comparator)
            : max_element(samochody.begin(), samochody.end(), comparator);

        int indeks = distance(samochody.begin(), it);

        cout << "\n" << (typ == "min" ? "Minimum" : "Maksimum") << " dla pola " << pole << ":\n";
        wyswietlNaglowek();
        wyswietlSamochod(indeks, *it);
    }
    else if (typ == "mediana") {
        vector<double> dane;
        for (const auto& s : samochody) {
            dane.push_back(pole == "cena" ? s.pobierzCene() : s.pobierzPrzebieg());
        }
        sort(dane.begin(), dane.end());
        double mediana;
        if (dane.size() % 2 == 0)
            mediana = (dane[dane.size() / 2 - 1] + dane[dane.size() / 2]) / 2.0;
        else
            mediana = dane[dane.size() / 2];

        cout << "Mediana dla pola " << pole << ": " << fixed << setprecision(2) << mediana << endl;
    }
    else if (typ == "odchylenie") {
        vector<double> dane;
        for (const auto& s : samochody) {
            dane.push_back(pole == "cena" ? s.pobierzCene() : s.pobierzPrzebieg());
        }
        double suma = accumulate(dane.begin(), dane.end(), 0.0);
        double srednia = suma / dane.size();
        double suma_kwadratow = 0.0;
        for (double x : dane)
            suma_kwadratow += (x - srednia) * (x - srednia);
        double odchylenie = sqrt(suma_kwadratow / dane.size());

        cout << "Odchylenie standardowe dla pola " << pole << ": " << fixed << setprecision(2) << odchylenie << endl;
    }
    else {
        cout << "Nieznany typ statystyki.\n";
    }
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
