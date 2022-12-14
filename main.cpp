#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <stdio.h>
#include <Windows.h>

/// //////////////////////////////////////////////////////////////
///          Obecne promenne
/// //////////////////////////////////////////////////////////////

int nSirkaPlochy = 120;
int nVyskaPlochy = 30;
string dilek[7];
int nSirkaHracihoPole = 12;
int nVyskaHracihoPole = 18;
char *pHraciPole = nullptr;

/// //////////////////////////////////////////////////////////////
///          Funkce na rotaci
/// //////////////////////////////////////////////////////////////

int Rotace(int nSouradniceUvnitrDilkuX, int nSouradniceUvnitrDilkuY, int r)     // excel
{
	int nSouradniceUvnitrDilku_i = 0;
	switch (r % 4)
	{
	case 0: // 0 stupnu
		nSouradniceUvnitrDilku_i = nSouradniceUvnitrDilkuY * 4 + nSouradniceUvnitrDilkuX;
		break;

	case 1: // 90 stupnu
		nSouradniceUvnitrDilku_i = 12 + nSouradniceUvnitrDilkuY - (nSouradniceUvnitrDilkuX * 4);
		break;

	case 2: // 180 stupnu
		nSouradniceUvnitrDilku_i = 15 - (nSouradniceUvnitrDilkuY * 4) - nSouradniceUvnitrDilkuX;
		break;

	case 3: // 270 stupnu
		nSouradniceUvnitrDilku_i = 3 - nSouradniceUvnitrDilkuY + (nSouradniceUvnitrDilkuX * 4);
		break;
	}

	return nSouradniceUvnitrDilku_i;
}

/// //////////////////////////////////////////////////////////////
///          Funkce na detekci kolize
/// //////////////////////////////////////////////////////////////

bool Kolize(int nDilek, int nRotace, int nPoziceX, int nPoziceY)
{
	for (int nSouradniceUvnitrDilkuX = 0; nSouradniceUvnitrDilkuX < 4; nSouradniceUvnitrDilkuX++)           // prochazime cely array dilku
		for (int nSouradniceUvnitrDilkuY = 0; nSouradniceUvnitrDilkuY < 4; nSouradniceUvnitrDilkuY++)
		{
			int nSouradniceUvnitrDilku_i = Rotace(nSouradniceUvnitrDilkuX, nSouradniceUvnitrDilkuY, nRotace);

			int nSouradnicePole_i = (nPoziceY + nSouradniceUvnitrDilkuY) * nSirkaHracihoPole + (nPoziceX + nSouradniceUvnitrDilkuX);

			if (nPoziceX + nSouradniceUvnitrDilkuX >= 0 && nPoziceX + nSouradniceUvnitrDilkuX < nSirkaHracihoPole) // kontrola okraju
			{
				if (nPoziceY + nSouradniceUvnitrDilkuY >= 0 && nPoziceY + nSouradniceUvnitrDilkuY < nVyskaHracihoPole)
				{
                	if (dilek[nDilek][nSouradniceUvnitrDilku_i] != '.' && pHraciPole[nSouradnicePole_i] != 0)
						return false;
				}
			}
		}

	return true;
}

/// //////////////////////////////////////////////////////////////
///          MAIN
/// //////////////////////////////////////////////////////////////

int main()
{
	///tvorba plochy
	char *plocha = new char[nSirkaPlochy*nVyskaPlochy];
	for (int i = 0; i < nSirkaPlochy*nVyskaPlochy; i++) plocha[i] = ' ';

	//void* hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	//unsigned long dwBytesWritten = 0;

    /// tvorba dilku
	dilek[0].append("..X.");
	dilek[0].append("..X.");
	dilek[0].append("..X.");
	dilek[0].append("..X.");

	dilek[1].append("..X.");
	dilek[1].append(".XX.");
	dilek[1].append(".X..");
	dilek[1].append("....");

	dilek[2].append(".X..");
	dilek[2].append(".XX.");
	dilek[2].append("..X..");
	dilek[2].append("....");

	dilek[3].append("....");
	dilek[3].append(".XX.");
	dilek[3].append(".XX.");
	dilek[3].append("....");

	dilek[4].append("..X.");
	dilek[4].append(".XX.");
	dilek[4].append("..X.");
	dilek[4].append("....");

	dilek[5].append(".XX.");
	dilek[5].append("..X.");
	dilek[5].append("..X.");
	dilek[5].append("....");

	dilek[6].append(".XX.");
	dilek[6].append(".X..");
	dilek[6].append(".X..");
	dilek[6].append("....");

    /// tvorba hraciho pole
    pHraciPole = new char[nSirkaHracihoPole*nVyskaHracihoPole];
	for (int x = 0; x < nSirkaHracihoPole; x++)
		for (int y = 0; y < nVyskaHracihoPole; y++)
			if (pHraciPole[y*nSirkaHracihoPole + x] = (x == 0 || x == nSirkaHracihoPole - 1 || y == nVyskaHracihoPole - 1))
            {
                pHraciPole[y*nSirkaHracihoPole + x] = 9; // hranice je rovna 9, coz odpovida "-"
            }
            else
            {
                pHraciPole[y*nSirkaHracihoPole + x] = 0; // vnitrek je roven 0
            }

	/// deklarace hracich/stavovych promennych
	bool bKlavesa[4];
	int nPracovniDilek = 0;
	int nPracovniRotace = 0;
	int nPracovniX = nSirkaHracihoPole / 2;
	int nPracovniY = 0;
	int nRychlost = 20;
	int nPocitadloRychlosti = 0;
	bool bDolu = false;
	bool bRotaceJednou = true;
	vector<int> vLajny;
	bool bGameOver = false;

	/// hlavní herni cyklus
	while (!bGameOver)
	{
		///casovani
		this_thread::sleep_for(50ms);
		nPocitadloRychlosti++;
		bDolu =(nPocitadloRychlosti == nRychlost);

		/// Uživatelske ovladani
		for (int k = 0; k < 4; k++)
			bKlavesa[k] = (0x8000 & GetAsyncKeyState((char)("\x27\x25\x28\x26"[k]))) != 0;

		if(bKlavesa[0])
        {
            if (Kolize(nPracovniDilek, nPracovniRotace, nPracovniX + 1, nPracovniY))
            {
            nPracovniX = nPracovniX + 1;
            }
        }

        if(bKlavesa[1])
        {
            if (Kolize(nPracovniDilek, nPracovniRotace, nPracovniX - 1, nPracovniY))
            {
            nPracovniX = nPracovniX - 1;
            }
        }

        if(bKlavesa[2])
        {
            if (Kolize(nPracovniDilek, nPracovniRotace, nPracovniX, nPracovniY + 1))
            {
            nPracovniY = nPracovniY + 1;
            }
        }

		if (bKlavesa[3])    //rotace
		{
			if(bRotaceJednou && Kolize(nPracovniDilek, nPracovniRotace + 1, nPracovniX, nPracovniY))
			{
                nPracovniRotace = nPracovniRotace + 1;
			}
			bRotaceJednou = false;
		}
		else
        {
            bRotaceJednou = true;
        }

		///Pohyb dolu
		if (bDolu)
		{
			nPocitadloRychlosti = 0;
			/// test kolize
			if (Kolize(nPracovniDilek, nPracovniRotace, nPracovniX, nPracovniY + 1))
				nPracovniY++;
			else
			{
				/// Dilek koliduje - stava se polem
				for (int nSouradniceUvnitrDilkuX = 0; nSouradniceUvnitrDilkuX < 4; nSouradniceUvnitrDilkuX++)       // prochazime cely array dilku
					for (int nSouradniceUvnitrDilkuY = 0; nSouradniceUvnitrDilkuY < 4; nSouradniceUvnitrDilkuY++)
						if (dilek[nPracovniDilek][Rotace(nSouradniceUvnitrDilkuX, nSouradniceUvnitrDilkuY, nPracovniRotace)] != '.')
							pHraciPole[(nPracovniY + nSouradniceUvnitrDilkuY) * nSirkaHracihoPole + (nPracovniX + nSouradniceUvnitrDilkuX)] = nPracovniDilek + 1;
				/// kontrola lajn
				for (int nSouradniceUvnitrDilkuY = 0; nSouradniceUvnitrDilkuY < 4; nSouradniceUvnitrDilkuY++)
					if(nPracovniY + nSouradniceUvnitrDilkuY < nVyskaHracihoPole - 1) // kontrola okraju
					{
						bool bLajna = true;
						for (int nSouradniceUvnitrDilkuX = 1; nSouradniceUvnitrDilkuX < nSirkaHracihoPole - 1; nSouradniceUvnitrDilkuX++)
							if (pHraciPole[(nPracovniY + nSouradniceUvnitrDilkuY) * nSirkaHracihoPole + nSouradniceUvnitrDilkuX] == 0)
                            {
                                bLajna = false;
                            }

						if (bLajna)
						{
							for (int nSouradniceUvnitrDilkuX = 1; nSouradniceUvnitrDilkuX < nSirkaHracihoPole - 1; nSouradniceUvnitrDilkuX++)
								pHraciPole[(nPracovniY + nSouradniceUvnitrDilkuY) * nSirkaHracihoPole + nSouradniceUvnitrDilkuX] = 0;
							vLajny.push_back(nPracovniY + nSouradniceUvnitrDilkuY);
						}
					}

                /// generace noveho dilku
				nPracovniX = nSirkaHracihoPole / 2;
				nPracovniY = 0;
				nPracovniRotace = 0;
				nPracovniDilek = rand() % 7;

				/// Hrac prohrava
				bGameOver = !Kolize(nPracovniDilek, nPracovniRotace, nPracovniX, nPracovniY);
			}
		}
		/// Herni pole
		for (int x = 0; x < nSirkaHracihoPole; x++)
			for (int y = 0; y < nVyskaHracihoPole; y++)
				plocha[(y + 2)*nSirkaPlochy + (x + 2)] = " ABCDEFG-&"[pHraciPole[y*nSirkaHracihoPole + x]]; // soubor pouivanych znaku

		/// Pracovni dilek
		for (int nSouradniceUvnitrDilkuX = 0; nSouradniceUvnitrDilkuX < 4; nSouradniceUvnitrDilkuX++)
			for (int nSouradniceUvnitrDilkuY = 0; nSouradniceUvnitrDilkuY < 4; nSouradniceUvnitrDilkuY++)
				if (dilek[nPracovniDilek][Rotace(nSouradniceUvnitrDilkuX, nSouradniceUvnitrDilkuY, nPracovniRotace)] != '.')
					plocha[(nPracovniY + nSouradniceUvnitrDilkuY + 2)*nSirkaPlochy + (nPracovniX + nSouradniceUvnitrDilkuX + 2)] = nPracovniDilek + 65;

		/// odstraneni a posun lajny
		if (!vLajny.empty())
		{
			for (auto &v : vLajny)
				for (int nSouradniceUvnitrDilkuX = 1; nSouradniceUvnitrDilkuX < nSirkaHracihoPole - 1; nSouradniceUvnitrDilkuX++)
				{
					for (int nSouradniceUvnitrDilkuY = v; nSouradniceUvnitrDilkuY > 0; nSouradniceUvnitrDilkuY--)
						pHraciPole[nSouradniceUvnitrDilkuY * nSirkaHracihoPole + nSouradniceUvnitrDilkuX] = pHraciPole[(nSouradniceUvnitrDilkuY - 1) * nSirkaHracihoPole + nSouradniceUvnitrDilkuX];
					pHraciPole[nSouradniceUvnitrDilkuX] = 0;
				}
			vLajny.clear();
		}

        /// display
		WriteConsoleOutputCharacter(hConsole, plocha, nSirkaPlochy * nVyskaPlochy, { 0,0 }, &dwBytesWritten);
	}
	/// konec hry
	CloseHandle(hConsole);
	cout << "Game Over" << endl;
	system("pause");
	return 0;
}


