#include <iostream> 
#include <time.h>
#include <windows.h>//sleep
#include <cstdlib>
#include <string>
#include <conio.h>

using namespace std;

bool smierc = false;

void menu();
void gra(bool s);
int* kartapostaci(int tablica[], int w);//jakies umiejetnosci w zaleznosci od rasy? (int bo chce, zeby zwracalo tablice)
void ekwipunek(int tablica[]);//bron, zbroja, hajs itd
void lokacja();//w ktorym miejscu sie jest, odpowiednie wspolrzedne, odpowiednia lokacja
void arena(int &exp);//wybor przecinika, moze trening
void walka();//jak wyglada walka z potworem
int* sklep_zbroj(int tablica[]);
int zdobywanie_poziomu(int poziom, int exp);
int trening(int &exp);
void intro();

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
void snake(int &exp);
//do gry w treningu

int main()
{
	setlocale(LC_ALL, "");
	//UINT oldcp = ::GetConsoleOutputCP();
	//::SetConsoleOutputCP(CP_UTF8);
	srand(time(NULL));
	menu();

	//::SetConsoleOutputCP(oldcp);
	return 0;
}
void menu()
{
	int w;
	cout << "Wciśnij 1, aby zacząć przygodę" << endl;
	cout << "Wciśnij 2, aby wyłączyć grę" << endl;
	cin >> w;

	if (w == 1)
	{
		gra(smierc);
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
	int wybor = 0;
	int bohater[10];
	bohater[0] = 7;
	int exp = 0;
	kartapostaci(bohater, wybor);
	do
	{
		kartapostaci(bohater, wybor);
	    Sleep(5000);
		cout << "Witaj wojowniku!" << endl << "Loading...";
	    Sleep(8000);
		intro();
		sklep_zbroj(bohater);

		break;

	} while (s == false);
}
int* kartapostaci(int tablica[], int w)
{
	string klasa[4] = { "wojownik ", "   mag   ", "złodziej ", " kapłan  " };
	string rasa[4] = { "człowiek ", "krasnolud", "   elf   ", "   ork   " };
	string plec[2] = { " kobieta ", "mężczyzna" };
	if (tablica[0] == 7)
	{
		tablica[0] = rand() % 4;
		//tablica[0] rasa

		//tablica[1]
		cout << "Jeśli chcesz być kobietą, wciśnij 1" << endl;
		cout << "Jeśli chcesz być mezczyzną, wciśnij 2" << endl;
		cin >> w;

		if (w == 1 || w == 2)
		{
			tablica[1] = w - 1;
		}
		else
		{
			cout << "Wybrałeś inną opcję." << endl;
			Sleep(2000);
			system("cls");
			tablica[0] = 7;
			kartapostaci(tablica, w);
		}

		//tablica[2]

		cout << "Jeśli chcesz być wojownikiem, wciśnij 1" << endl;
		cout << "Jeśli chcesz być magiem, wciśnij 2" << endl;
		cout << "Jeśli chcesz być złodziejem, wciśnij 3" << endl;
		cout << "Jeśli chcesz być kapłanem, wciśnij 4" << endl;
		cin >> w;
		tablica[2] = w - 1;

		switch (w)// hp tablica[3], dmg (zadany podczas walki) tablica[4]
		{
		case 1:
		{
			tablica[3] = 10;
			tablica[4] = 10;
			break;
		}
		case 2:
		{
			tablica[3] = 7;
			tablica[4] = 13;
			break;
		}
		case 3:
		{
			tablica[3] = 12;
			tablica[4] = 8;
			break;
		}
		case 4:
		{
			tablica[3] = 16;
			tablica[4] = 4;
			break;
		}
		default:
		{
			cout << "Nie ma takiej klasy." << endl;
			Sleep(2000);
			system("cls");
			tablica[0] = 7;
			kartapostaci(tablica, w);
		}
		}

		//tablica[5]
		int wiek = rand() % 60 + 15;
		tablica[5] = wiek;

		system("cls");
		cout << "Masz " << wiek << " lat." << endl;
		if (wiek >= 60)
		{
			cout << "Jesteś dość star";
			if (plec[tablica[1]] == "kobieta")
				cout << "a" << endl;
			else
				cout << "y" << endl;

			tablica[4] -= 3;
		}

		//tablica[6] - poziom
		tablica[6] = 1;

		//tablica[7] - exp
		tablica[7] = 0;

		//tablica[8] - gold
		tablica[8] = 300;
	}
	else
	{
		cout << "*********************************" << endl;
		cout << "*                               *" << endl;
		cout << "*          " << rasa[tablica[0]] << "            *" << endl;
		cout << "*          " << klasa[tablica[2]] << "            *" << endl;
		cout << "*          " << plec[tablica[1]] << "            *" << endl;
		cout << "*  hp:  " << tablica[3];
		if (tablica[3] < 10)
			cout << " ";
		cout << "                      *" << endl;
		cout << "*  dmg: " << tablica[4];
		if (tablica[4] < 10)
			cout << " ";
		cout << "                      *" << endl;
		cout << "*  lvl: " << tablica[6];
		if (tablica[6] < 10)
			cout << " ";
		cout << "                      *" << endl;
		cout << "*  exp: " << tablica[6];
		if (tablica[7] < 10)
			cout << " ";
		cout << "                      *" << endl;
		cout << "*  monety: "<< tablica[8];
		if (tablica[8] < 10)
			cout << " ";
		cout << "                  *" << endl;
		
		cout << "*                               *" << endl;
		cout << "*********************************" << endl;
	}

	return tablica;




}
void ekwipunek(int tablica[])
{

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

// wstępny zamysł <= troche tu zmienilam
int zdobywanie_poziomu(int poziom, int exp)
{
	//poziom = 1, exp=0;
	if (exp >= 5 * poziom + 5)
	{
		while (poziom <= 10)
		{
			poziom++;
			cout << "Świetnie! Jesteś od teraz na " << poziom << " poziomie!" << endl;
			break;
		}

	}

	if (poziom == 10)//koniec gry?
	{

	}

	/*for (poziom ; ; (poziom++) && (exp = 0))
	{

		for (exp; exp<=5*poziom+5; exp++)
		{
			cout << poziom << "    " << exp << endl;
		}


		if (poziom == 10) break;
	}*/

	return poziom;
}

int* sklep_zbroj(int tablica[])
{
	system("cls");
	string text1 = "Witaj podróżniku, w mieście roi się od plotek na twój temat. Podobno masz zamiar stać się najpotężniejszym wojownikiem w całej krainie! Mam tu co uczyni cię bardziej odpornym na ataki";
	string text2 = "Wybierz przedmioty, które chcesz zobaczyć: ";
	string text3 = "1: hełmy";
	string text4 = "2: kirysy";
	string text5 = "3: trzewiki";
	int decyzja;
	int kontynuacja = 1;
	//wpisywanie powitalnego tekstu
	int dlug1 = text1.length();
	for (int i = 0; i < dlug1; i++)
	{
		cout << text1[i];
		Sleep(30);
	}
	Sleep(2000);
	cout << endl;

	int dlug2 = text2.length();
	for (int i = 0; i < dlug2; i++)
	{
		cout << text2[i];
		Sleep(30);
	}
	Sleep(2000);

	//----------------------------------------
	//wybór zakupu


	int helm[10];		helm[0] = 100;			helm[1] = 200;
	int kirys[10];		kirys[0] = 250;			kirys[1] = 400;
	int trzewiki[10];	trzewiki[0] = 80;		trzewiki[1] = 150;

	do
	{
		cout << endl;
		int dlug3 = text3.length();
		for (int i = 0; i < dlug3; i++)
		{
			cout << text3[i];
			Sleep(30);
		}
		cout << endl;

		int dlug4 = text4.length();
		for (int i = 0; i < dlug4; i++)
		{
			cout << text4[i];
			Sleep(30);
		}
		cout << endl;

		int dlug5 = text5.length();
		for (int i = 0; i < dlug5; i++)
		{
			cout << text5[i];
			Sleep(30);
		}
		cout << endl;


		cin >> decyzja;
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
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << helm[i] << endl;

				else
				{
					helm[i] = helm[i - 1] + helm[i - 2];
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << helm[i] << endl;
				}
			}
			cout << endl << endl << "czy chcesz coś kupić? Kliknij   1   jeśli tak";
			int odp = 0;
			cin >> odp;
			if (odp == 1)
			{
				cout << "Wybierz numer przedmiotu, który chcesz zakupić: " << endl;
				int numer = 0;
				cin >> numer;
				if ((numer > tablica[6]) || (helm[numer] > tablica[8])) //6 to poziom, 7 to exp, 8 to gold
					cout << "Nie osiągnąłeś wystarczającego poziomu, lub jesteś zbyt biedny by zakupić ten przedmiot! " << endl;
				else
				{
					cout << "Gratulacje, udało ci się zakupić hełm " << numer << " poziomu! " << endl;
					tablica[8] -= helm[numer - 1];
					cout << "stan twojego konta wynosi teraz: "<< tablica[8] << endl;
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
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << kirys[i] << endl;

				else
				{
					kirys[i] = kirys[i - 1] + kirys[i - 2];
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << kirys[i] << endl;
				}
			}
			cout << endl << endl << "czy chcesz coś kupić? Kliknij   1   jeśli tak";
			int odp = 0;
			cin >> odp;
			if (odp == 1)
			{
				cout << "Wybierz numer przedmiotu, który chcesz zakupić: " << endl;
				int numer = 0;
				cin >> numer;
				if ((numer > tablica[6]) || (kirys[numer] > tablica[8]))
					cout << "Nie osiągnąłeś wystarczającego poziomu, lub jesteś zbyt biedny by zakupić ten przedmiot! " << endl;
				else
				{
					cout << "Gratulacje, udało ci się zakupić hełm " << numer << " poiomu! " << endl;
					tablica[8] -= kirys[numer - 1];
					cout << "stan twojego konta wynosi teraz: "<< tablica[8] << endl;
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
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << trzewiki[i] << endl;

				else
				{
					trzewiki[i] = trzewiki[i - 1] + trzewiki[i - 2];
					cout << i + 1 << ")" << " Wymagany poziom do zakupu: " << i + 1 << "     Cena: " << trzewiki[i] << endl;
				}
			}
			cout << endl << endl << "czy chcesz coś kupić? Kliknij   1   jeśli tak";
			int odp = 0;
			cin >> odp;
			if (odp == 1)
			{
				cout << "Wybierz numer przedmiotu, który chcesz zakupić: " << endl;
				int numer = 0;
				cin >> numer;
				if ((numer > tablica[6]) || (trzewiki[numer] > tablica[8]))
					cout << "Nie osiągnąłeś wystarczającego poziomu, lub jesteś zbyt biedny by zakupić ten przedmiot! " << endl;
				else
				{
					cout << "Gratulacje, udało ci się zakupić hełm " << numer << " poiomu! " << endl;
					tablica[8] -= trzewiki[numer - 1];
					cout << "stan twojego konta wynosi teraz: "<< tablica[8] << endl;
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
	}
	while (kontynuacja == 1);

	return tablica;
}
void arena(int &exp)
{
	int w = 0;
	cout << "Chcesz walczyć z potworem? Wpisz 1" << endl;
	cout << "Chcesz potrenować? Wpisz 2" << endl;
	cin >> w;
	Sleep(1500);
	system("cls");
	if (w == 1)
	{
		walka();
	}
	else if (w == 2)
	{
		trening(exp);
	}
	else
	{
		cout << "Nie masz zbyt dużego wyboru. Zostaniesz zapytany ponownie." << endl;
		Sleep(1500);
		arena(exp);
	}
}
void walka()
{

}
int trening(int &exp)
{
    cout << "Zaczynamy trening!" << endl;
    snake(exp);
	return 0;
}


void snake(int &exp)
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

        exp = 0.5 * Wynik;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        cout << "\n\t\tZdobyto ";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << Wynik;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        cout << " punktow czyli ";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << exp;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        cout << " exp! Super!";

        Sleep(3000);
        _getch();
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
