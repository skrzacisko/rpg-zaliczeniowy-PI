#include <iostream>
#include <time.h>
#include <windows.h>//sleep
#include <cstdlib>
#include <string>
#include <conio.h>

using namespace std;

bool wygrana = false;
struct potwor //deklaracja struktury
{
	//opis struktur
	string nazwa;
	int poziom;
	int dmg;
	int hp;
	string status; //umarly, nieumarly
	string opis;
};

struct bohater
{
	string rasa;
	string plec;
	string klasa;
	int hp;
	int dmg;
	int lvl;
	int exp;
	int hajs;
	int wiek;
	int maleapteczki = 0;
	int srednieapteczki = 0;
	int duzeapteczki = 0;
	int zaklecia = 0;
	int poziomhelmu = 0;
	int poziomkirysu = 0;
	int poziomtrzewik = 0;
	int poziombroni = 0;
};

void menu();
void gra(bool s);
int kartapostaci(bohater& jakis);
void arena(bohater& jakis);//wybor przecinika, moze trening
void sklep_zbroj(bohater& jakis);
int zdobywanie_poziomu(bohater& jakis);
int trening(bohater& jakis);
void intro();
void poruszanie(bohater& jakis);
//do walki
int poprawnedane(bohater& jakis);
void walka(bohater& jakis, potwor* temp);
void walka1(bohater& jakis);
void sklep_drugi(bohater& jakis);
//do gry w treningu
typedef COORD PunktNaMapie;
constexpr auto ESCAPE = 27;
constexpr auto ZEGAR = 2719;

void Kursor(PunktNaMapie Wspolrzedne);
void StworzMape();
void Menu(int& zakoncz);
void Sterowanie(PunktNaMapie& Waz, double& Czas, PunktNaMapie Owoc, bool& strzal);
void RysujOwoc(PunktNaMapie& Owoc, PunktNaMapie Waz, int& NumerOwoca, bool& losuj);
bool CzyZebrano(PunktNaMapie Waz, PunktNaMapie Owoc, int& Wynik, bool& losuj, bool& strzal);
void snake(bohater& jakis);
//do gry w treningu

const int DLUGOSC = 42, WYSOKOSC = 11;
int x = 20, y = 5;

void rysujmape();

void kolorZielen();

void kolorNeutral();

void kolorCzerwien();

void kolorNiebieski();

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	menu();


	return 0;
}

void menu()
{
	int w;
	cout << "Wciśnij 1, aby zacząć przygodę" << endl
		<< "Wciśnij 2, aby wyłączyć grę" << endl;
	cin >> w;
	cin.clear();
	cin.ignore(1000, '\n');

	if (w == 1)
	{
		gra(wygrana);
	}
	else if (w == 2)
	{
		cout << "Gra zostanie wyłączona" << endl;
		Sleep(2000);
		exit(0);
	}
	else
	{
		cout << "Nie wpisałeś 1 ani 2. Nie martw się, następnym razem się uda." << endl;
		Sleep(2000);
		system("cls");
		menu();
	}


}

void gra(bool s)
{
	system("cls");
	bohater bohater;
	bohater.klasa = "nikt";
	kartapostaci(bohater);
	kartapostaci(bohater); //teraz to wypisanie tylko
	Sleep(5000);
	cout << "Witaj wojowniku!" << endl << "Loading...";
	intro();
	do
	{

		poruszanie(bohater);


	} while (s == false);
}

int kartapostaci(bohater& jakis)
{
	int w;
	string klasa[4] = { "wojownik", "mag", "złodziej", "kapłan" };
	string rasa[4] = { "człowiek", "krasnolud", "elf", "ork" };
	string plec[2] = { "kobieta", "mężczyzna" };
	if (jakis.klasa == "nikt")
	{
		jakis.rasa = rasa[rand() % 4];

		cout << "Jeśli chcesz być kobietą, wciśnij 1" << endl;
		cout << "Jeśli chcesz być mezczyzną, wciśnij 2" << endl;
		cin >> w;
		cin.clear();
		cin.ignore(1000, '\n');
		if (w == 1 || w == 2)
		{
			jakis.plec = plec[w - 1];
		}
		else
		{
			cout << "Wybrałeś inną opcję." << endl;
			Sleep(2000);
			system("cls");
			jakis.klasa = "nikt";
			kartapostaci(jakis);
		}

		cout << "Jeśli chcesz być wojownikiem, wciśnij 1" << endl;
		cout << "Jeśli chcesz być magiem, wciśnij 2" << endl;
		cout << "Jeśli chcesz być złodziejem, wciśnij 3" << endl;
		cout << "Jeśli chcesz być kapłanem, wciśnij 4" << endl;
		cin >> w;
		cin.clear();
		cin.ignore(1000, '\n');
		jakis.klasa = klasa[w - 1];

		switch (w)
		{
		case 1:
		{
			jakis.hp = 10;
			jakis.dmg = 10;
			break;
		}
		case 2:
		{
			jakis.hp = 7;
			jakis.dmg = 13;
			break;
		}
		case 3:
		{
			jakis.hp = 12;
			jakis.dmg = 8;
			break;
		}
		case 4:
		{
			jakis.hp = 16;
			jakis.dmg = 4;
			break;
		}
		default:
		{
			cout << "Nie ma takiej klasy." << endl;
			Sleep(2000);
			system("cls");
			jakis.klasa = "nikt";
			kartapostaci(jakis);
		}
		}


		int wiek = rand() % 60 + 15;
		jakis.wiek = wiek;

		system("cls");
		cout << "Masz " << wiek << " lat." << endl;
		if (wiek >= 60)
		{
			cout << "Jesteś dość star";
			if (jakis.plec == "kobieta")
				cout << "a" << endl;
			else
				cout << "y" << endl;

			jakis.wiek -= 3;
		}


		jakis.lvl = 1;
		jakis.exp = 0;
		jakis.hajs = 100;
	}
	else
	{
		cout << "*********************************" << endl
			<< "                                 " << endl
			<< "           " << jakis.rasa << endl
			<< "           " << jakis.klasa << endl
			<< "           " << jakis.plec << endl
			<< "   hp:  " << jakis.hp;
		if (jakis.hp < 10)
			cout << " ";
		cout << "                       " << endl
			<< "   dmg: " << jakis.dmg;
		if (jakis.dmg < 10)
			cout << " ";
		cout << "                       " << endl
			<< "   lvl: " << jakis.lvl;
		if (jakis.lvl < 10)
			cout << " ";
		cout << "                       " << endl
			<< "   exp: " << jakis.exp;
		if (jakis.exp < 10)
			cout << " ";
		cout << "                      " << endl
			<< "   monety: " << jakis.hajs;
		if (jakis.hajs < 10)
			cout << " ";
		cout << "                   " << endl
			<< "                               " << endl
			<< "*********************************" << endl;
	}

	return 0;
}

void intro()
{
	system("cls");
	string tekst1 = "Tu się zaczyna twoja historia...";
	string tekst2 = "Z powodu twojej hańbiącej przeszłości cała rodzina się ciebie wyrzekła. \nJedyne co możesz zrobić by odzyskać ''normalne życie'' to walka.";
	string tekst3 = "Postanawiasz odzyskać godność, dlatego ruszasz na arenę by walczyć.";
	string tekst4 = "Wcześniej jednak przydałoby się zaopatrzyć w jakąś zbroję i broń.";

	int dlugosc1 = tekst1.length();
	for (int i = 0; i < dlugosc1; i++)
	{
		cout << tekst1[i];
		Sleep(30);
	}
	Sleep(2000);
	cout << endl;



	int dlugosc2 = tekst2.length();
	for (int i = 0; i < dlugosc2; i++)
	{
		cout << tekst2[i];
		Sleep(30);
	}
	Sleep(2000);
	cout << endl;



	int dlugosc3 = tekst3.length();
	for (int i = 0; i < dlugosc3; i++)
	{
		cout << tekst3[i];
		Sleep(30);
	}
	Sleep(2000);
	cout << endl;


	int dlugosc4 = tekst4.length();
	for (int i = 0; i < dlugosc4; i++)
	{
		cout << tekst4[i];
		Sleep(30);
	}
	Sleep(2000);


}

int zdobywanie_poziomu(bohater& jakis)
{

	if (jakis.exp >= 5 * jakis.lvl + 5)
	{
		while (jakis.lvl <= 10)
		{
			(jakis.lvl)++;
			(jakis.dmg) += 3;
			(jakis.hajs) += 100 * jakis.lvl;
			cout << "Świetnie! Jesteś od teraz na " << jakis.lvl << " poziomie!" << endl;
			break;
		}

	}

	if (jakis.lvl == 10)
	{
		cout << "Udalo ci sie odzyskac honor i pokonac prawnikow. To byla swietna przygoda." << endl;
		cout << "Dzieki za gre" << endl;
		wygrana = true;
		Sleep(8000);
	}


	return 0;
}

void sklep_zbroj(bohater& jakis)
{
	system("cls");
	string text1 = "Witaj podróżniku, w mieście roi się od plotek na twój temat. Podobno masz zamiar stać się najpotężniejszym wojownikiem w całej krainie! Mam tu co uczyni cię mocniejszym";
	string text2 = "Wybierz przedmioty, które chcesz zobaczyć: ";
	string text3 = "1: hełmy";
	string text4 = "2: kirysy";
	string text5 = "3: trzewiki";
	string text6 = "4: miecze";
	int decyzja;
	int kontynuacja = 1;
	//wpisywanie powitalnego tekstu
	int dlug1 = text1.length();
	for (int i = 0; i < dlug1; i++)
	{
		cout << text1[i];

	}
	Sleep(2000);
	cout << endl;

	int dlug2 = text2.length();
	for (int i = 0; i < dlug2; i++)
	{
		cout << text2[i];

	}
	Sleep(2000);

	//----------------------------------------
	//wybór zakupu


	int helm[10];		helm[0] = 100;			helm[1] = 200;
	int kirys[10];		kirys[0] = 250;			kirys[1] = 400;
	int trzewiki[10];	trzewiki[0] = 80;		trzewiki[1] = 150;
	int miecz[10];      miecz[0] = 120;         miecz[1] = 250;
	do
	{
		cout << endl;
		int dlug3 = text3.length();
		for (int i = 0; i < dlug3; i++)
		{
			cout << text3[i];

		}
		cout << endl;

		int dlug4 = text4.length();
		for (int i = 0; i < dlug4; i++)
		{
			cout << text4[i];

		}
		cout << endl;

		int dlug5 = text5.length();
		for (int i = 0; i < dlug5; i++)
		{
			cout << text5[i];

		}
		cout << endl;
		int dlug6 = text6.length();
		for (int i = 0; i < dlug6; i++)
		{
			cout << text6[i];

		}
		cout << endl;


		cin >> decyzja;
		cin.clear();
		cin.ignore(1000, '\n');
		system("cls");
		switch (decyzja)
		{

		case 1:
			//hełmy
		{
			cout << "Żeby zakupić któryś z tych hełmów musisz mieć odpowiedni poziom " << endl << "Oto hełmy które proponuję: " << endl;
			for (int i = 0; i < 10; i++)
			{
				if (i == 0 || i == 1)
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << helm[i] << "   boost:   " << helm[i] / (10) << endl;

				else
				{
					helm[i] = helm[i - 1] + helm[i - 2];
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << helm[i] << "   boost:   " << helm[i] / (3 * (i + 1)) << endl;
				}
			}

			cout << "Wybierz numer przedmiotu, który chcesz zakupić: " << endl;
			int numer = 0;
			cin >> numer;
			cin.clear();
			cin.ignore(1000, '\n');
			if ((numer > jakis.lvl) || (helm[numer - 1] > jakis.hajs))
				cout << "Nie osiągnąłeś wystarczającego poziomu, lub jesteś zbyt biedny by zakupić ten przedmiot! " << endl;
			else

			{
				if (jakis.poziomhelmu > numer)
				{
					cout << "masz już ten lub lepszy hełm" << endl;
				}
				else
				{
					cout << "Gratulacje, udało ci się zakupić hełm " << numer << " poziomu! " << endl;
					jakis.hajs -= helm[numer - 1];
					cout << endl << "piniądze jakie ci pozostały: " << jakis.hajs << endl;


					if (jakis.poziomhelmu > 0)
					{
						if (jakis.poziomhelmu < 3)
							jakis.hp -= helm[jakis.poziomhelmu - 1] / 10;
						else
							jakis.hp -= helm[jakis.poziomhelmu - 1] / (3 * (jakis.poziomhelmu));
					}
					jakis.poziomhelmu = numer;
					if (jakis.poziomhelmu < 3)
						jakis.hp += helm[jakis.poziomhelmu - 1] / 10;
					else
						jakis.hp += helm[jakis.poziomhelmu - 1] / (3 * (jakis.poziomhelmu));
					jakis.poziomhelmu = numer;
				}
			}

			break;

		}


		case 2:
			//kirysy
		{
			cout << "Żeby zakupić któryś z tych kirysów musisz mieć odpowiedni poziom " << endl << "Oto kirysy które proponuję: " << endl;
			for (int i = 0; i < 10; i++)
			{
				if (i == 0 || i == 1)
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << kirys[i] << "   boost:   " << kirys[i] / 10 << endl;

				else
				{
					kirys[i] = kirys[i - 1] + kirys[i - 2];
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << kirys[i] << "   boost:   " << kirys[i] / (5 * (i + 1)) + 15 << endl;
				}
			}

			cout << "Wybierz numer przedmiotu, który chcesz zakupić: " << endl;
			int numer = 0;
			cin >> numer;
			cin.clear();
			cin.ignore(1000, '\n');

			if ((numer > jakis.lvl) || (kirys[numer - 1] > jakis.hajs))
				cout << "Nie osiągnąłeś wystarczającego poziomu, lub jesteś zbyt biedny by zakupić ten przedmiot! " << endl;
			else

			{
				if (jakis.poziomkirysu > numer)
				{
					cout << "masz już ten lub lepszy kirys" << endl;
				}
				else
				{
					cout << "Gratulacje, udało ci się zakupić kirys " << numer << " poziomu! " << endl;
					jakis.hajs -= kirys[numer - 1];
					cout << endl << "piniądze jakie ci pozostały: " << jakis.hajs << endl;


					if (jakis.poziomkirysu > 0)
					{
						if (jakis.poziomkirysu < 3)
							jakis.hp -= kirys[jakis.poziomkirysu - 1] / 10;
						else
							jakis.hp -= kirys[jakis.poziomkirysu - 1] / (5 * jakis.poziomkirysu) + 15;
					}
					jakis.poziomkirysu = numer;
					if (jakis.poziomkirysu < 3)
						jakis.hp += kirys[jakis.poziomkirysu - 1] / 10;
					else
						jakis.hp += kirys[jakis.poziomkirysu - 1] / (5 * jakis.poziomkirysu) + 15;
					jakis.poziomkirysu = numer;

				}
			}

			break;
		}






		case 3:
			//trzewiki
		{
			cout << "Żeby zakupić któryś z tych kirysów musisz mieć odpowiedni poziom " << endl << "Oto kirysy które proponuję: " << endl;
			for (int i = 0; i < 10; i++)
			{
				if (i == 0 || i == 1)
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << trzewiki[i] << "   boost:   " << trzewiki[i] / 10 << endl;

				else
				{
					trzewiki[i] = trzewiki[i - 1] + trzewiki[i - 2];
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << trzewiki[i] << "   boost:   " << trzewiki[i] / (3 * (i + 1)) - 2 << endl;
				}
			}

			cout << "Wybierz numer przedmiotu, który chcesz zakupić: " << endl;
			int numer = 0;
			cin >> numer;
			cin.clear();
			cin.ignore(1000, '\n');


			if ((numer > jakis.lvl) || (trzewiki[numer - 1] > jakis.hajs))
				cout << "Nie osiągnąłeś wystarczającego poziomu, lub jesteś zbyt biedny by zakupić ten przedmiot! " << endl;
			else

			{
				if (jakis.poziomtrzewik > numer)
				{
					cout << "masz już te lub lepsze trzewiki" << endl;
				}
				else
				{
					cout << "Gratulacje, udało ci się zakupić trzewiki " << numer << " poziomu! " << endl;
					jakis.hajs -= trzewiki[numer - 1];
					cout << endl << "piniądze jakie ci pozostały: " << jakis.hajs << endl;


					if (jakis.poziomtrzewik > 0)
					{
						if (jakis.poziomtrzewik < 3)
							jakis.hp -= trzewiki[jakis.poziomtrzewik - 1] / 10;
						else
							jakis.hp -= trzewiki[jakis.poziomtrzewik - 1] / (3 * jakis.poziomtrzewik) - 2;
					}
					jakis.poziomtrzewik = numer;
					if (jakis.poziomtrzewik < 3)
						jakis.hp += trzewiki[jakis.poziomtrzewik - 1] / 10;
					else
						jakis.hp += trzewiki[jakis.poziomtrzewik - 1] / (3 * jakis.poziomtrzewik) - 2;
					jakis.poziomtrzewik = numer;
				}
			}

			break;
		}

		case 4:
			//miecze
		{
			cout << "Żeby zakupić któryś z tych mieczy musisz mieć odpowiedni poziom " << endl << "Oto miecze które proponuję: " << endl;
			for (int i = 0; i < 10; i++)
			{
				if (i == 0 || i == 1)
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << miecz[i] << "   boost:   " << miecz[i] / (10) << endl;

				else
				{
					miecz[i] = miecz[i - 1] + miecz[i - 2];
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << miecz[i] << "   boost:   " << miecz[i] / (3 * (i + 1)) << endl;
				}
			}

			cout << "Wybierz numer przedmiotu, który chcesz zakupić: " << endl;
			int numer = 0;
			cin >> numer;
			cin.clear();
			cin.ignore(1000, '\n');
			if ((numer > jakis.lvl) || (miecz[numer - 1] > jakis.hajs))
				cout << "Nie osiągnąłeś wystarczającego poziomu, lub jesteś zbyt biedny by zakupić ten przedmiot! " << endl;
			else

			{
				if (jakis.poziomhelmu > numer)
				{
					cout << "masz już ten lub lepszy miecz" << endl;
				}
				else
				{
					cout << "Gratulacje, udało ci się zakupić miecz " << numer << " poziomu! " << endl;
					jakis.hajs -= miecz[numer - 1];
					cout << endl << "piniądze jakie ci pozostały: " << jakis.hajs << endl;


					if (jakis.poziombroni > 0)
					{
						if (jakis.poziombroni < 3)
							jakis.hp -= miecz[jakis.poziombroni - 1] / 10;
						else
							jakis.hp -= miecz[jakis.poziombroni - 1] / (3 * (jakis.poziombroni));
					}
					jakis.poziombroni = numer;
					if (jakis.poziombroni < 3)
						jakis.hp += miecz[jakis.poziombroni - 1] / 10;
					else
						jakis.hp += miecz[jakis.poziombroni - 1] / (3 * (jakis.poziombroni));
					jakis.poziombroni = numer;
				}
			}

			break;

		}
		default:
		{
			cout << "Nie ma takiej opcji :-( " << endl;
			break;
		}
		}

		cout << "czy chcesz kontynuować zakupy? Wciśnij   1   jeśli tak, lub dowolny inny numer jeśli nie" << endl;
		kontynuacja = 1;
		cin >> kontynuacja;
		cin.clear();
		cin.ignore(1000, '\n');
	} while (kontynuacja == 1);
	system("cls");
}

void arena(bohater& jakis)
{

	int w = 0;
	cout << "Chcesz walczyć z potworem? Wpisz 1" << endl;
	cout << "Chcesz potrenować? Wpisz 2" << endl;
	cout << "Chcesz wyjść z areny? Wpisz 3" << endl;
	cin >> w;
	cin.clear();
	cin.ignore(1000, '\n');

	Sleep(1500);
	system("cls");
	if (w == 1)
	{
		walka1(jakis);
	}
	else if (w == 2)
	{
		cout << "Zaczynamy trening!" << endl;
		snake(jakis);
		zdobywanie_poziomu(jakis);
	}
	else if (w == 3)
	{
		return;
	}
	else
	{
		cout << "Nie masz zbyt dużego wyboru. Zostaniesz zapytany ponownie." << endl;
		Sleep(1500);
		arena(jakis);
	}
}

void snake(bohater& jakis)
{
	PunktNaMapie Waz;
	PunktNaMapie Owoc;
	PunktNaMapie Zegarek;
	PunktNaMapie TablicaWyniku;
	MSG Komunikat; // MSG - wiadomosc. Zmienna przechowujaca zdarzenia programu.
				   //Potrzebujemy jej do wlaczenia stopera
	//miejsca poczatkowe
	Waz.X = 3;
	Waz.Y = 2;
	Zegarek.X = 18;
	Zegarek.Y = 23;
	TablicaWyniku.X = 9;
	TablicaWyniku.Y = 21;
	Owoc.X = 6;
	Owoc.Y = 17;


	int Wynik = 0;
	double Czas;
	const WORD Zegar = ZEGAR; // Utworzenie stopera o nazwie zegar, z numerem
							  //identyfikacyjnym ZEGAR czyli 2719
	int NumerOwoca = 0;; // Zmienna do numerowania owocow.
	bool losuj = true;
	bool punkt = false;
	bool strzal = false;

	srand(time(NULL));

	for (; ;)
	{
		system("cls");
		int zakoncz = 0;
		Menu(zakoncz);

		if (zakoncz == 0)
		{
			return;
		}

		///poczatkowe wartosci zmiennych
		NumerOwoca = 0;
		Wynik = 0;
		Czas = 60;
		losuj = true;

		StworzMape();

		SetTimer(NULL, Zegar, 10, NULL); // Wlaczenie stopera, ktory nada komunikat co 10 ms

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		cout << "\nWynik:   ";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << Wynik << '\n' << '\n';

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		cout << "Pozostaly czas:   ";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << Czas << '\n' << '\n';

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		cout << "\n\nWcisnij e, aby zakonczyc.";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		Kursor(Waz);
		cout << "X";


		while (Czas > 0)
		{
			if (GetMessage(&Komunikat, NULL, 0, 0) == 1)
			{

				if (Komunikat.message == WM_TIMER)
				{
					Czas -= 0.01;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					Kursor(Zegarek);
					cout << Czas;
				}

				RysujOwoc(Owoc, Waz, NumerOwoca, losuj);

				if (_kbhit()) //jestli zostal wcisniety klawisz, funkcja przyjmuje wartosc 1, jesli nie 0
				{
					Sterowanie(Waz, Czas, Owoc, strzal);
				}

				punkt = 0;
				punkt = CzyZebrano(Waz, Owoc, Wynik, losuj, strzal);

				if (punkt == true)
				{

					Kursor(TablicaWyniku);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << Wynik; // Nadpisanie
				}

			}

		}

		system("cls");

		jakis.exp += 0.5 * Wynik;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << "\n\t\tZdobyto ";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		cout << Wynik;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << " punktow czyli ";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		cout << 0.5 * Wynik;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << " exp! Super!";

		Sleep(3000);
		//_getch();
		cout << "\n\n";

	}

	return;
}

void Kursor(PunktNaMapie Wspolrzedne)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Wspolrzedne);
}

void StworzMape()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	for (int i = 0; i < 20; i++)
	{
		if (i == 0 || i == 19)
		{
			for (int j = 0; j < 40; j++)
			{
				cout << "*";
			}
			cout << endl;
		}
		else
		{
			cout << "*                                      *" << '\n';
		}

	}
}

void Menu(int& zakoncz)
{
	int wybor;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	cout << "\tTrening zrecznosci i szybkosci ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "\tZa 1 zdobyty punkt otrzymujesz w zaokragleniu 0,5 exp\n\n";


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "\t\t\t\tMENU \n\n";
	cout << "\t\t\t[1] \t";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << " Rozpocznij gre\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "\t\t\t[2] \t";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << " Wyjdz\n\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "\tProtip: Strzelasz z procy wciskajac p, poruszasz celownikiem uzywajac klawiszy w s a d\n";

	cin >> wybor;
	cin.clear();
	cin.ignore(1000, '\n');
	switch (wybor)
	{
	case 1:
	{
		system("cls");
		zakoncz = 1;
		break;
	}
	case 2:
	{
		zakoncz = 0;
		break;
	}
	default:
	{
		cout << wybor << endl;
		cout << "Ups! Pomylka, wybierz jeszcze raz!" << endl;
		Sleep(2000);
		system("cls");
		Menu(zakoncz);
		break;
	}

	}
}

void Sterowanie(PunktNaMapie& Waz, double& Czas, PunktNaMapie Owoc, bool& strzal)
{
	char kierunek = _getch(); // alternatywnie kierunek = cin.get()

	switch (kierunek)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	case 'w': // Strzalka w gore.
		Kursor(Waz);
		cout << " "; //usuniecie starej pozycji

		if (Waz.Y > 1) //Zabezpieczenie, ze waz nie wyjdzie poza mape
		{
			Waz.Y -= 1; //Jeden wiersz w gore
		}
		else if (Waz.Y == 1)
		{
			Czas = 0;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		Kursor(Waz); // Przejscie do nowej pozycji weza.
		cout << "X"; // Nadpisanie
		break;

	case 's': // Strzalka w dol
		Kursor(Waz);
		cout << " ";

		if (Waz.Y < 18)//zeby nie wyjsc poza plansze
		{
			Waz.Y += 1; //Jeden wiersz w dol.
		}
		else if (Waz.Y == 18)
		{
			Czas = 0;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		Kursor(Waz);
		cout << "X";
		break;

	case 'a': //Strzalka w lewo
	{
		Kursor(Waz);
		cout << " ";

		if (Waz.X > 1)
		{
			Waz.X -= 1; //Jedna kolumna w lewo
		}
		else if (Waz.X == 1)
		{
			Czas = 0;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		Kursor(Waz);
		cout << "X";
		break;
	}
	case 'd': // Strzalka w prawo.
	{
		Kursor(Waz);
		cout << " ";

		if (Waz.X < 38)
		{
			Waz.X += 1; // Jedna kolumna w prawo
		}
		else if (Waz.X == 38)
		{
			Czas = 0;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		Kursor(Waz);
		cout << "X";
		break;
	}
	case 'p':
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		Kursor(Waz);
		cout << "o";

		if (Waz.X == Owoc.X && Waz.Y == Owoc.Y)
		{
			strzal = true;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		if (Waz.Y < 17)
		{
			Waz.Y = Waz.Y + 1;
			Kursor(Waz);
			cout << "X";

			break;
		}
		else
		{
			Waz.Y = Waz.Y - 1;
			Kursor(Waz);
			cout << "X";
			break;
		}
	}
	case 'e':
	{
		Czas = 0;
		break;
	}
	default:
		break;

	}
}

void RysujOwoc(PunktNaMapie& Owoc, PunktNaMapie Waz, int& NumerOwoca, bool& losuj)
{
	if (losuj == true && Owoc.X != Waz.X)
	{
		Owoc.X = rand() % 38 + 1;
		Owoc.Y = rand() % 18 + 1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		Kursor(Owoc);
		cout << "O";
		losuj = false;
		NumerOwoca++;

	}
}

bool CzyZebrano(PunktNaMapie Waz, PunktNaMapie Owoc, int& Wynik, bool& losuj, bool& strzal)
{

	if (Waz.Y + 1 == Owoc.Y && Waz.X == Owoc.X && strzal == true)
	{
		Wynik++;
		strzal = false;
		losuj = true;

		return true;
	}
	else if (Waz.Y - 1 == Owoc.Y && Waz.X == Owoc.X && strzal == true)
	{
		Wynik++;
		strzal = false;
		losuj = true;

		return true;
	}
	else
	{
		return false;
	}
}

void walka1(bohater& jakis)
{


	string nazwa[10] = { "slimak", "waz boa", "maly wilkolak", "mucholapka", "ogromny chomik", "krwiopijca", "jakis ogr", "zombie", "Wielka Stopa","prawnik" };
	string status[2] = { "umarly", "nieumarly" };
	string opis[10] = { "niezbyt szybki, ale grozny", "owinie sobie ciebie wokol palca", "glownie warczy", "lubi ludzkie mieso", "strach sie bac",
			"uwielbia ksiazki i krwawa Mary", "nie Shrek", "wieczorami wpatruje sie w sciane", "wcale nie ma az tak wiekich stop", "jesli cie dopadnie to koniec" };


	cout << "Wpisz poziom potwora, z którym chcesz walczyc" << endl;
	cout << "Wybrany poziom musi być mniejszy lub rowny twojemu" << endl;

	potwor* temp = new potwor; //wskaźnik *temp na strukturę

	temp->poziom = poprawnedane(jakis);//to samo co (*temp).poziom
	temp->nazwa = nazwa[temp->poziom];
	temp->opis = opis[temp->poziom];

	int losowosc = rand() % 2;
	temp->dmg = 2 + 2 * temp->poziom + losowosc;
	temp->hp = 13 + 4 * temp->poziom + losowosc;
	temp->status = status[losowosc];
	losowosc = rand() % 2;


	if (losowosc == 1)
	{
		cout << "=^..^=   =^..^=   =^..^=    =^..^=" << endl;
		cout << temp->nazwa << endl << temp->opis << endl << "lvl:  " << temp->poziom << endl << "hp:  " << temp->hp << endl << "max dmg:  " << temp->dmg << endl
			<< temp->status << endl;
		cout << "=^..^=   =^..^=   =^..^=    =^..^=" << endl;

		cout << endl << "Powodzenia!" << endl;
		Sleep(4000);
		walka(jakis, temp);
	}
	else
	{
		cout << "Nie znaleziono potwora gotowego do walki" << endl;
	}
	zdobywanie_poziomu(jakis);

	delete temp; // usuwanie obiektu potwor temp;
}

int poprawnedane(bohater& jakis)
{
	int a;
	cin >> a;
	while (cin.fail() || jakis.lvl < a || a < 0)
	{
		cout << "Wprowadziles bledne dane" << endl;

		cin.clear();
		cin.ignore(1000, '\n');

		cout << "Wprowadz ponownie:" << endl;;
		cin >> a;
	}
	return a;
}

void walka(bohater& jakis, potwor* temp)
{
	int atak;
	bool pokonany = false;
	bool wygrana = false;
	bool cios = false; //sprawdza, czy byl cios krytyczny
	int licznik = 0; //sprawdza liczbe rzuconych zaklec
	bool ciosp = false;
	int licznikp = 0;
	int zdrowie = jakis.hp;
	while (pokonany == false && wygrana == false)
	{
		cout << "Co chcesz zrobić" << endl << "1. Zwykły atak\n2. Cios krytyczny\n3. Rzucenie klatwy\n4. Leczenie" << endl;
		int wybor;
		cin >> wybor;
		cin.clear();
		cin.ignore(1000, '\n');
		switch (wybor)
		{

		case 1:
			atak = jakis.lvl + rand() % (jakis.dmg - jakis.lvl + 1);
			cout << "Atakujesz potwora z mocą " << atak << "!" << endl;
			temp->hp -= atak;
			cout << "Potwor ma teraz " << temp->hp << " punktow zycia" << endl;

			if (temp->hp <= 0)
			{
				wygrana = true;
				cout << "Skopal";
				if (jakis.plec == "kobieta")
					cout << "a";
				else
					cout << "e";
				cout << "s mu tylek. Gratulacje!" << endl << "Otrzymujesz " << 2 * temp->poziom << " punktow doswiadczenia i " << 50 * temp->dmg << " zlota." << endl;
				jakis.exp += 2 * temp->poziom;
				jakis.hajs += 50 * temp->dmg;
			}
			break;

		case 2:
			if (cios == false)
			{
				atak = jakis.dmg + rand() % 2;
				cout << "Atakujesz potwora z mocą " << atak << "! To byl piekny atak." << endl;
				temp->hp -= atak;
				cout << "Potwor ma teraz " << temp->hp << " punktow zycia" << endl;
				cios = true;

				if (temp->hp <= 0)
				{
					wygrana = true;
					cout << "Skopal";
					if (jakis.plec == "kobieta")
						cout << "a";
					else
						cout << "e";
					cout << "s mu tylek. Gratulacje!" << endl << "Otrzymujesz " << 2 * temp->poziom << " punktow doswiadczenia i " << 50 * temp->dmg << " zlota." << endl;
					jakis.exp += 2 * temp->poziom;
					jakis.hajs += 50 * temp->dmg;
				}
			}
			else
				cout << "Ktos tu cos kreci. Cios krytyczny dziala tylko raz na walke. Tracisz szansę na atak." << endl;
			break;

		case 3:
			if (jakis.zaklecia >= 1)
			{
				jakis.zaklecia--;
				temp->dmg = 0.5 * temp->dmg;
				cout << "teraz twój wróg zadaje mniejsze obrażenia o 50% !";

			}
			else
			{
				cout << "Nie masz zaklęć, tracisz kolejkę.";
			}
			break;
		case 4:
			cout << "której apteczki chcesz użyć?" << endl << "Masz " << jakis.maleapteczki << "małych apteczek" << endl << "Masz " << jakis.srednieapteczki << " średnich apteczek" << endl << "Masz " << jakis.duzeapteczki << " dużych apteczek" << endl;
			Sleep(1000);
			cout << "Aby użyć małej apteczki wciśnij 1, średniej - 2, a dużej - 3";
			int decyzja;
			cin >> decyzja;
			cin.clear();
			cin.ignore(1000, '\n');
			switch (decyzja)
			{
			case 1:
			{
				if (jakis.maleapteczki == 0)
					cout << "Nie masz małych apteczek, tracisz ruch";
				else
				{
					jakis.maleapteczki--;
					if (zdrowie < 0.7 * jakis.hp)
						zdrowie += 0.3 * jakis.hp;
					else zdrowie = jakis.hp;
				}
			}
			break;
			case 2:
			{
				if (jakis.srednieapteczki == 0)
					cout << "Nie masz średnich apteczek, tracisz ruch";
				else
				{
					jakis.srednieapteczki--;
					if (zdrowie < 0.5 * jakis.hp)
						zdrowie += 0.5 * jakis.hp;
					else zdrowie = jakis.hp;
				}
			}
			break;
			case 3:
			{
				if (jakis.duzeapteczki == 0)
					cout << "Nie masz małych apteczek, tracisz ruch";
				else
				{
					jakis.duzeapteczki--;
					if (zdrowie < 0.3 * jakis.hp)
						zdrowie += 0.7 * jakis.hp;
					else zdrowie = jakis.hp;
				}
			}
			break;
			default:
			{
				cout << "Nie ma takiej opcji, tracisz ruch";
			}
			break;
			}
		}

		if (temp->hp > 0)
		{
			wybor = 1 + rand() % 9;
			cout << wybor << " ";
			switch (wybor)
			{
			case 1: case 2: case 3: case 4: case 5:
				atak = temp->poziom + rand() % (temp->dmg - temp->poziom + 1);
				cout << "Potwor atakuje cie z mocą " << atak << "!" << endl;
				zdrowie -= atak;
				cout << "Masz teraz " << zdrowie << " punktow zycia" << endl;

				if (zdrowie <= 0)
				{
					pokonany = true;
					cout << "Jestes ciezko pobit";
					if (jakis.plec == "kobieta")
						cout << "a";
					else
						cout << "e";
					cout << ", ale przezyjesz. Gratulacje!" << endl;
					jakis.exp -= 0, 5 * temp->poziom;

				}
				break;
			case 6: case 7:
				if (ciosp == false)
				{
					atak = temp->dmg + rand() % 2;
					cout << "Potwor uderzyl cie z moca " << atak << "! Natarcie prawie przewrocilo cie na kolana." << endl;
					zdrowie -= atak;
					cout << "Masz teraz " << zdrowie << " punktow zycia" << endl;
					ciosp = true;

					if (zdrowie <= 0)
					{
						pokonany = true;
						cout << "Jestes ciezko pobit";
						if (jakis.plec == "kobieta")
							cout << "a";
						else
							cout << "e";
						cout << ", ale przezyjesz. Gratulacje!" << endl;
						jakis.exp -= 0, 5 * temp->poziom;

					}
				}
				else
					cout << "Potwor nie trafil. " << endl;
				break;
			case 8:
				if (temp->status == "nieumarly" && licznikp < temp->poziom)
				{
					licznik++;
					atak = 7 + 3 * temp->poziom;
					cout << "Potwor jest nieumarłym i rzuca na ciebie klatwe o mocy " << atak << "!" << endl;
					zdrowie -= atak;
					cout << "Masz teraz " << zdrowie << " punktow zycia" << endl;

					if (zdrowie <= 0)
					{
						pokonany = true;
						cout << "Jestes ciezko pobit";
						if (jakis.plec == "kobieta")
							cout << "a";
						else
							cout << "e";
						cout << ", ale przezyjesz. Gratulacje!" << endl;
						jakis.exp -= 0, 5 * temp->poziom;
					}
				}
				else if (licznikp < temp->poziom)
				{
					cout << "Potwor ma kryzys tozsamosci" << endl;
				}
				else
				{
					cout << "Potwor potknal sie" << endl;
				}
				break;
			case 9:
				cout << "Potwor przykleil sobie plaster i wypil ciepla herbatke z sokiem malinowym" << endl;
				temp->hp += 10;
				cout << "Ma teraz " << temp->hp << " punktow zycia" << endl;
			}
		}

		Sleep(8000);



		system("cls");

	}
}


void sklep_drugi(bohater& jakis)
{
	system("cls");
	int kontynuacja = 1;
	do
	{

		cout << "Witaj, możesz tu kupić przedmioty co pozwolą ci przetrwać walkę. Oto one: " << endl;
		int apteczkam = 30, apteczkas = 100, apteczkad = 300, klatwasily = 100, numer;

		cout << "1. mała apteczka ---> cena: " << apteczkam << " dodaje 30% hp" << endl;
		cout << "2. średnia apteczka ---> cena: " << apteczkas << " dodaje 50% hp" << endl;
		cout << "3. duża apteczka ---> cena: " << apteczkad << " dodaje 70% hp" << endl;
		cout << "4. klątwa---> cena: " << klatwasily << " obniża siłę przeciwnika o 50%" << endl << endl;

		cout << "wybierz numer przedmiotu który chcesz zakupić ( 5 oznacza nic) " << endl;
		cin >> numer;
		cin.clear();
		cin.ignore(1000, '\n');
		switch (numer)
		{
		case 1:
		{
			if (jakis.hajs < 50)
			{
				cout << "nie stać cię na to" << endl;
			}
			else
			{
				jakis.hajs -= 50;
				jakis.maleapteczki++;

				cout << "posiadasz teraz " << jakis.maleapteczki << " małych apteczek" << endl;
			}
			break;
		}


		case 2:
		{
			if (jakis.hajs < 100)
			{
				cout << "nie stać cię na to" << endl;
			}
			else
			{
				jakis.hajs -= 100;
				jakis.srednieapteczki++;

				cout << "posiadasz teraz " << jakis.srednieapteczki << " średnich apteczek" << endl;
			}
			break;
		}


		case 3:
		{
			if (jakis.hajs < 300)
			{
				cout << "nie stać cię na to" << endl;
			}
			else
			{
				jakis.hajs -= 50;
				jakis.duzeapteczki++;

				cout << "posiadasz teraz " << jakis.duzeapteczki << " dużych apteczek" << endl;
			}
			break;
		}


		case 4:
		{
			if (jakis.hajs < 100)
			{
				cout << "nie stać cię na to" << endl;
			}
			else
			{
				jakis.hajs -= 100;
				jakis.zaklecia++;

				cout << "posiadasz teraz " << jakis.zaklecia << " zaklęć" << endl;
			}
			break;
		}


		case 5:
		{
			break;
		}
		}

		cout << "czy chcesz kontynuować zakupy? Wciśnij   1   jeśli tak, lub dowolny inny numer jeśli nie" << endl;
		kontynuacja = 1;
		cin >> kontynuacja;
		cin.clear();
		cin.ignore(1000, '\n');
		system("cls");
	} while (kontynuacja == 1);

}
void poruszanie(bohater& jakis)
{

	system("cls");
	PunktNaMapie aktualnapozycja = { 20,5 };
	PunktNaMapie początek = { 0,0 };
	rysujmape();

	Kursor(aktualnapozycja);
	cout << "x";

	do
	{
		if (_kbhit())
		{

			Kursor(początek);
			rysujmape();

			char kierunek = _getch();

			switch (kierunek)
			{

			case 'w':

				if (aktualnapozycja.Y > 2)
				{
					aktualnapozycja.Y -= 1;
				}

				Kursor(aktualnapozycja);
				cout << "x"; // Nadpisanie
				break;

			case 's':

				if (aktualnapozycja.Y < 10)
				{
					aktualnapozycja.Y += 1;
				}

				Kursor(aktualnapozycja);
				cout << "x";
				break;

			case 'a': //Strzalka w lewo

				if (aktualnapozycja.X > 1)
				{
					aktualnapozycja.X -= 1;
				}

				Kursor(aktualnapozycja);
				cout << "x";
				break;

			case 'd':
				if (aktualnapozycja.X < 39)
				{
					aktualnapozycja.X += 1;
				}

				Kursor(aktualnapozycja);
				cout << "x";
				break;

			default:
				break;

			}


			//ARENA
			if (aktualnapozycja.X > 13 && aktualnapozycja.X < 19 && aktualnapozycja.Y == 2)
			{
				system("cls");
				arena(jakis);
				aktualnapozycja.Y += 1;
				cout << "wciśnij dowolny klawisz (inny niż w)" << endl;
			}
			//ZBROJMISTRZ
			else if (aktualnapozycja.X > 22 && aktualnapozycja.X < 33 && aktualnapozycja.Y == 3)
			{
				system("cls");
				sklep_zbroj(jakis);
				aktualnapozycja.Y += 1;
				cout << "wciśnij dowolny klawisz (inny niż w)" << endl;
			}
			//gildia
			else if (aktualnapozycja.X > 9 && aktualnapozycja.X < 25 && aktualnapozycja.Y == 9)
			{
				system("cls");
				kartapostaci(jakis);
				aktualnapozycja.Y += 1;
				cout << "wciśnij dowolny klawisz (inny niż w)" << endl;
			}

			//MAG
			else if (aktualnapozycja.X > 35 && aktualnapozycja.X < 39 && aktualnapozycja.Y == 10)
			{
				system("cls");
				sklep_drugi(jakis);
				aktualnapozycja.Y += 1;
				cout << "wciśnij dowolny klawisz (inny niż w)" << endl;
			}

		}
		else
		{
			Kursor(aktualnapozycja);
		}

	} while (wygrana == false);
}

char mapa[WYSOKOSC][DLUGOSC] =
{
	{'=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '\n'},
	{'|','*','*','*','|','R','|','*','*','*','*','*','*','[','A','R','E','N','A',']','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|','\n'},
	{'|','*','*','*','|','Z','|','*','[',']','[',']','[',']','[',']',' ','|','|', ' ', ' ', ' ', '[','Z','B','R','O','J','M','I','S','T','R','Z',']','*','*','*','*','*','|','\n'},
	{'|','*','*','*','|','E','|','*','[',']','[',']','[',']','[',']','-','|','|','-','-','-','|','|','-','[',']','[',']','[',']','[',']','[',']','*','*','*','*','*','|','\n'},
	{'|', '*', '*', '*', '\\', 'K', '\\', '*', '[', ']', '[', ']', '[', ']', '[', ']', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '[', ']', '[', ']', '[', ']', '[', ']', '[', ']', '*', '*',  '*', '*', '*', '|', '\n'},
	{'|','*','*','*','*','\\','A','\\','[',']','[',']','[',']','[',']','|',' ', 'R','Y','N','E','K',' ','|','_','_','_','[',']','[',']','[',']',' ','*','*','*','*','*','|','\n'},
	{'|','*','*','*','*','*','|','=','|','=','=','=','=','=','=','=','|','_','_',' ', ' ', '_','_','_','_','_',' ', ' ',  '|', '[',']','[',']','[',']','*','*','*','*','*','|','\n'},
	{'|','*','*','*','*','*','|','W','|',' ','[',']','[',']','[',']','-','-','-','|','|','-','-','-','-','-','|',' ', '|','[',']','[',']','[',']','*','*','*','*','*','|','\n'},
	{'|', '*','*','*','*','*','|','I','|','[','S','I','E','D','Z','I','B','A',' ','G','I','L','D','I','I',']','|',' ','|','_','_','_','_','_','_','*','*','*','*','*','|','\n'},
	{'|', '*','*','*','*','*','\\','T','\\','[',']','[',']','[',']','[',']','[',']','[',']','[',']', '*', '*','*','|', '_','_','_','_','_','_','_','_','[','M','A','G',']','|','\n'},
	{'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','='}
};


void rysujmape()
{
	cout << endl;

	for (int j = 0; j < WYSOKOSC; j++)
	{
		for (int i = 0; i < DLUGOSC; i++)
		{
			if (mapa[j][i] == '*')
			{
				kolorZielen();
				cout << mapa[j][i];
			}

			else if (mapa[j][i] == '[')
			{
				kolorCzerwien();
				cout << mapa[j][i];
			}

			else if (mapa[j][i] == ']')
			{
				kolorCzerwien();
				cout << mapa[j][i];
			}

			else if (mapa[j][i] == '+')
			{
				kolorNiebieski();
				cout << mapa[j][i];
			}
			else
			{
				cout << mapa[j][i];
			}
			kolorNeutral();
		}



	}
	cout << endl;
}

void kolorZielen()
{
	SetConsoleTextAttribute
	(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void kolorNeutral()
{
	SetConsoleTextAttribute
	(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void kolorCzerwien()
{
	SetConsoleTextAttribute
	(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void kolorNiebieski()
{
	SetConsoleTextAttribute
	(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}