#include "Osoba.h"
#include <iostream>

Osoba::Osoba()
{
    //ctor
}

Osoba::Osoba(std::string sPrijmeni_in,std::string sJmeno_in, int nVek_in, float fVyska_in, string sVzdelani_in)
{
    sPrijmeni = sPrijmeni_in;
    sJmeno = sJmeno_in;
    nVek = nVek_in;
    fVyska = fVyska_in;
    sVzdelani = sVzdelani_in;
    //dtor
}

string Osoba::prijmeni() const
{
    return sPrijmeni;
}

string Osoba::jmeno() const
{
    return sJmeno;
}

int Osoba::vek() const
{
    return nVek;
}

float Osoba::vyska() const
{
    return fVyska;
}

string Osoba::vzdelani() const
{
    return sVzdelani;
}
