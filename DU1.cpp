#include <iostream>
#include <cmath>
#include <string>


using namespace std;

int main() {
/////////////////////////////
// Zadavani jmena a primeni//
/////////////////////////////

cout << "Zadejte Vase jmeno: ";
   string jmeno;
    cin >> jmeno;
    cout << "Zadejte Vase primeni: ";
    string primeni;
    cin >> primeni;

///////////////////////////////////
// Zadavani vysky a jeji kontrola//
///////////////////////////////////
    double vyska;
    char r;
    char rr;
    char rrr;
        cout << "Zadejte Vasi vysku v centimetrech: ";
        cin >> vyska;
        if (vyska < 100){
            cout << "Zadali jste vysku mensi nez 100 centimetru, jste si jisti, ze Vami zadana hodnota vysky je spravna? [Y/n]: ";
            cin >> r;
            } if (r == 'n'){
            cout << "Zadejte znovu Vasi vysku v centimetrech: ";
            cin >> vyska;
            }
        if (vyska > 280){
            cout << "Zadali jste vysku vetsi nez 280 centimetru, jste si jisti, ze Vami zadana hodnota vysky je spravna? [Y/n]: ";
            cin >> rr;
            } if (rr == 'n'){
            cout << "Zadejte znovu Vasi vysku v centimetrech: ";
            cin >> vyska;
            }
        if (vyska < 100 && r != 'Y'){
            cout << "Zadali jste vysku mensi nez 100 centimetru, jste si jisti, ze Vami zadana hodnota vysky je spravna? [Y/n]: ";
            cin >> rrr;
            } if (rrr== 'n'){
            cout << "Zadejte znovu Vasi vysku v centimetrech: ";
            cin >> vyska;
            }
///////////////////////////////////
// Zadavani veku a jeho kontrola//
///////////////////////////////////
    double vek;
    char m;
    char mm;
    char mmm;
        cout << "Zadejte Vas vek: ";
        cin >> vek;
        if (vek < 4){
            cout << "Zadali jste vek mensi nez 4, jste si jisti, ze Vami zadana hodnota veku je spravna? [Y/n]: ";
            cin >> m;
            } if (m == 'n'){
            cout << "Zadejte znovu Vas vek: ";
            cin >> vek;
            }
        if (vek > 120){
            cout << "Zadali jste vek vetsi nez 120, jste si jisti, ze Vami zadana hodnota veku je spravna? [Y/n]: ";
            cin >> mm;
            } if (mm == 'n'){
            cout << "Zadejte znovu Vas vek: ";
            cin >> vek;
            }
        if (vek < 4 && m != 'Y'){
            cout << "Zadali jste vek mensi nez 4, jste si jisti, ze Vami zadana hodnota veku je spravna? [Y/n]: ";
            cin >> mmm;
            } if (mmm == 'n'){
            cout << "Zadejte znovu Vas vek: ";
            cin >> vek;
            }
//////////////////////////////////////
// Zadavani vzdelani a jeho kontrola//
//////////////////////////////////////

string l;
cout << "Zadejte dosazene vzdelani z nabidky (zs,ss,vs): ";
cin >> l;
char ll = l[0];
if (ll !='z' || ll != !'s' || ll != 'v'){
    cout << "Nezadali jste zadnou z moznosti, prosim zadejte dosazene vzdelani z nabidky znovu (zs,ss,vs): ";
    cin >> l;
}
    cout << "Dobry den, jmenujete se " << jmeno << " " << primeni << ". Je vam " << vek << " a jste " << vyska << " centimetru vysoky. Vase dosazene vzdelani je " << l << "." << endl;
    return 0;
}
