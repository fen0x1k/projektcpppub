#pragma once
#include <string>
using namespace std;

class Samochod {
private:
    string marka;
    string model;
    int rocznik;
    int przebieg;
    double cena;

public:
    Samochod();
    Samochod(string marka, string model, int rocznik, int przebieg, double cena);

    void ustawMarke(string marka);
    void ustawModel(string model);
    void ustawRocznik(int rocznik);
    void ustawPrzebieg(int przebieg);
    void ustawCene(double cena);

    string pobierzMarke() const;
    string pobierzModel() const;
    int pobierzRocznik() const;
    int pobierzPrzebieg() const;
    double pobierzCene() const;

    void wyswietl() const;
};