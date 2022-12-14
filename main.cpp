#include <iostream>
#include <fstream>
#include <vector>
#include "Osoba.h"
#include <algorithm>

using namespace std;

vector<Osoba> nacti(vector<Osoba> osoby)
{

cout << "Zadejte Vase jmeno: ";
   string sJmeno;
    cin >> sJmeno;
    cout << "Zadejte Vase primeni: ";
    string sPrijmeni;
    cin >> sPrijmeni;

    float fVyska;
    char chTest;
    char chTest2;
    char chTest3;
        cout << "Zadejte Vasi vysku v centimetrech: ";
        cin >> fVyska;
        if (fVyska < 100){
            cout << "Zadali jste vysku mensi nez 100 centimetru, jste si jisti, ze Vami zadana hodnota vysky je spravna? [Y/n]: ";
            cin >> chTest;
            } if (chTest == 'n'){
            cout << "Zadejte znovu Vasi vysku v centimetrech: ";
            cin >> fVyska;
            }
        if (fVyska > 280){
            cout << "Zadali jste vysku vetsi nez 280 centimetru, jste si jisti, ze Vami zadana hodnota vysky je spravna? [Y/n]: ";
            cin >> chTest2;
            } if (chTest2 == 'n'){
            cout << "Zadejte znovu Vasi vysku v centimetrech: ";
            cin >> fVyska;
            }
        if (fVyska < 100 && chTest != 'Y'){
            cout << "Zadali jste vysku mensi nez 100 centimetru, jste si jisti, ze Vami zadana hodnota vysky je spravna? [Y/n]: ";
            cin >> chTest3;
            } if (chTest3== 'n'){
            cout << "Zadejte znovu Vasi vysku v centimetrech: ";
            cin >> fVyska;
            }
    int nVek;
    char chTest4;
    char chTest5;
    char chTest6;
        cout << "Zadejte Vas vek: ";
        cin >> nVek;
        if (nVek < 4){
            cout << "Zadali jste vek mensi nez 4, jste si jisti, ze Vami zadana hodnota veku je spravna? [Y/n]: ";
            cin >> chTest4;
            } if (chTest4 == 'n'){
            cout << "Zadejte znovu Vas vek: ";
            cin >> nVek;
            }
        if (nVek > 120){
            cout << "Zadali jste vek vetsi nez 120, jste si jisti, ze Vami zadana hodnota veku je spravna? [Y/n]: ";
            cin >> chTest5;
            } if (chTest5 == 'n'){
            cout << "Zadejte znovu Vas vek: ";
            cin >> nVek;
            }
        if (nVek < 4 && chTest != 'Y'){
            cout << "Zadali jste vek mensi nez 4, jste si jisti, ze Vami zadana hodnota veku je spravna? [Y/n]: ";
            cin >> chTest6;
            } if (chTest6 == 'n'){
            cout << "Zadejte znovu Vas vek: ";
            cin >> nVek;
            }
string sVzdelani;
cout << "Zadejte dosazene vzdelani z nabidky (zakladka,stredni,vysoka): ";
cin >> sVzdelani;
cout << sVzdelani[0];
if (sVzdelani[0] == 'z' || sVzdelani[0] == 115 || sVzdelani[0] == 'v'){
    cout << "Dobry den, jmenujete se " << sJmeno << " " << sPrijmeni << ". Je vam " << nVek << " a jste " << fVyska << " centimetru vysoky. Vase dosazene vzdelani je " << sVzdelani << "." << endl;
    }
    else{
        cout << "Nezadali jste zadnou z moznosti, prosim zadejte dosazene vzdelani z nabidky znovu (zakladka,stredni,vysoka): ";
    cin >> sVzdelani;
    }

    osoby.push_back(Osoba(sPrijmeni,sJmeno,nVek,fVyska,sVzdelani));

    return osoby;
}


void ukladani(vector<Osoba> osoby)
{
    ofstream ulozTo ("osoby.txt");

    for(Osoba k : osoby)
    {
        ulozTo << k.prijmeni();
        ulozTo << " ";
        ulozTo << k.jmeno();
        ulozTo << " ";
        ulozTo << k.vek();
        ulozTo << " ";
        ulozTo << k.vyska();
        ulozTo << " ";
        ulozTo << k.vzdelani();
        ulozTo << "\n";
    }
    return;
}

struct Trideni
{
    bool operator()(class Osoba& a1 , class Osoba& a2) const
    {
        return a1.prijmeni() < a2.prijmeni();
    }

};

vector<Osoba> serazeno(vector<Osoba> a)
{
    sort(a.begin(),a.end(), Trideni());
    return a;
}

int main()
{
    int u;
    vector<Osoba> osoby;

    do
    {
        u = 0;
        osoby = nacti(osoby);
        cout << "Pro nacteni dalsi osoby napiste 1: ";
        cin >> u;
    }while(u==1);

    vector<Osoba> osoby2;
    osoby2 = serazeno(osoby);

    ukladani(osoby2);

return 0;
}
