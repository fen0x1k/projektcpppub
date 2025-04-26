#pragma once
#include <vector>
#include <string>
#include "Samochod.h"
using namespace std;

class BazaSamochodow {
private:
    vector<Samochod> samochody;
public:
    void dodajSamochod();
    void edytujSamochod(int indeks);
    void usunSamochod(int indeks);
    void wyswietlWszystkie() const;
    void wyswietlWszystkieSortowanie() const;
    void wyswietlSamochodyFiltrowanie() const;
    void posortujBaze();
    void zapiszDoPliku(const string& nazwaPliku) const;
    void wczytajZPliku(const string& nazwaPliku, bool dodaj = false);
    void generujStatystyki() const;
    int iloscSamochodow() const;

    void wyswietlNaglowek() const;
    void wyswietlSamochod(size_t indeks, const Samochod& samochod) const;

    int wczytajInt() const;
    double wczytajDouble() const;
    char wczytajZnak() const;
private:
    void generujSredniaCene() const;
    void generujNajtanszySamochod() const;
    void generujNajdrozszySamochod() const;
    void generujMedianePrzebiegu() const;
    void generujOdchylenieStandardoweCen() const;
    void generujWszystkieStatystyki() const;
    void sortujPoWybranymKryterium(vector<Samochod>& bazaDoSortowania) const;
};