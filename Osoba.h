#ifndef Osoba_H
#define Osoba_H
#include <iostream>

#include <vector>

using namespace std;

class Osoba

{
    public:
        Osoba();
        Osoba(string sPrijmeni_in, string sJmeno_in, int sVek_in, float fVyska_in, string sVzdelani_in);
        string prijmeni() const;
        string jmeno() const;
        int vek() const;
        float vyska() const;
        string vzdelani() const;

    protected:

    private:
        string sPrijmeni, sJmeno, sVzdelani;
        int nVek;
        float fVyska;
};

#endif // Osoba_H

