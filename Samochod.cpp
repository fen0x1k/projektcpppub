#include "Samochod.h"
#include <iostream>

Samochod::Samochod() : marka(""), model(""), rocznik(0), przebieg(0), cena(0.0) {}

Samochod::Samochod(string marka, string model, int rocznik, int przebieg, double cena)
    : marka(marka), model(model), rocznik(rocznik), przebieg(przebieg), cena(cena) {}

void Samochod::ustawMarke(string marka) { this->marka = marka; }
void Samochod::ustawModel(string model) { this->model = model; }
void Samochod::ustawRocznik(int rocznik) { this->rocznik = rocznik; }
void Samochod::ustawPrzebieg(int przebieg) { this->przebieg = przebieg; }
void Samochod::ustawCene(double cena) { this->cena = cena; }

string Samochod::pobierzMarke() const { return marka; }
string Samochod::pobierzModel() const { return model; }
int Samochod::pobierzRocznik() const { return rocznik; }
int Samochod::pobierzPrzebieg() const { return przebieg; }
double Samochod::pobierzCene() const { return cena; }

void Samochod::wyswietl() const {
    cout << "Marka: " << marka << ", Model: " << model
        << ", Rocznik: " << rocznik << ", Przebieg: " << przebieg
        << " km, Cena: " << cena << " PLN" << endl;
}
