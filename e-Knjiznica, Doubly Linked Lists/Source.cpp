#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <ctype.h>
#include <algorithm>


#define DULJINA (50)
#define OK (0)
#define imeDatoteke ("eKnjiznica.txt")
#define posudeneDat ("posudene.txt")

using namespace std;

typedef struct eKnjiznica* Pozicija;
struct eKnjiznica {
	char knjiga[DULJINA];
	char autor[DULJINA];
	int godina;
	int brojKnjiga;

	Pozicija prev, next;
}eKNJIZNICA;

Pozicija AlokacijaNoveKnjige();
void UnosInfoUKnjigu(Pozicija novaKnjiga, char knjige[], char autor[], int godina, int brojPrimjeraka);
void Izbornik();
void Ispis(Pozicija P);
void DodajKnjiguNaKraj(Pozicija P);
void DodajKnjiguNaPocetak(Pozicija P);
void IzbrisiKnjigu(Pozicija P);
int IzbrojiKnjige(Pozicija P);
int PosudiKnjigu(Pozicija P);
void IspisiPosudeneKnjige();
int UpdateajFile(Pozicija P);
void DealociranjeMemorije(Pozicija head, char* lista);
void ToUpper(char naziv[]);
int ReturnRandom();
Pozicija Trazi(char knjiga[], Pozicija P);

void Izbornik()
{
	cout << "Odaberite jednu od opcija: " << endl;
	cout << "1. Ispis knjiga" << endl;
	cout << "2. Dodaj knjigu na pocetak" << endl;
	cout << "3. Dodaj knjigu na kraj" << endl;
	cout << "4. Izbrisi knjigu" << endl;
	cout << "5. Ukupan broj knjiga" << endl;
	cout << "6. Posudi knjigu po nazivu" << endl;
	cout << "7. Ispis proslih posudenih knjiga" << endl;
	cout << "8. Izlaz" << endl;
}

int main()
{
	struct eKnjiznica lista;
	lista.next = NULL;

	int choice = -1;
	int x = 0;
	bool valid = false;

	while (choice != 10)
	{
		do {
			Izbornik();
			cin >> choice;
			if (cin.good())
			{
				//everything went well, we'll get out of the loop and return the value
				valid = true;
			}
			else
			{
				//something went wrong, we reset the buffer's state to good
				cin.clear();
				//and empty it
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Krivi unos, pokusajte ponovo." << endl;
			}
			switch (choice)
			{
			case 1: Ispis(lista.next);
				break;
			case 2:
				DodajKnjiguNaPocetak(&lista);
				UpdateajFile(lista.next);
				break;
			case 3:
				DodajKnjiguNaKraj(&lista);
				UpdateajFile(lista.next);
				break;
			case 4:
				IzbrisiKnjigu(&lista);
				UpdateajFile(lista.next);
				break;
			case 5:
				IzbrojiKnjige(&lista);
				break;
			case 6:
				PosudiKnjigu(lista.next);
				break;
			case 7:
				IspisiPosudeneKnjige();
				break;
			case 8:
				break;
			default: cout << "Krivi izbor!" << endl;
			}
		} while (!valid);
	}

	DealociranjeMemorije(lista.next, (char*)"pocetne liste.\r\n");
	return 0;
}

Pozicija AlokacijaNoveKnjige()
{
	Pozicija novaKnjiga = (Pozicija)malloc(sizeof(eKNJIZNICA));
	if (novaKnjiga == NULL)
	{
		cout << "Memorija je puna, ne moze se dodati nova knjiga!" << endl;
		return NULL;
	}
	novaKnjiga->next = NULL;

	return novaKnjiga;
}

void UnosInfoUKnjigu(Pozicija novaKnjiga, char knjige[], char autor[], int godina, int brojPrimjeraka)
{
	strcpy(novaKnjiga->knjiga, knjige);
	strcpy(novaKnjiga->autor, autor);
	novaKnjiga->godina = godina;
	novaKnjiga->brojKnjiga = brojPrimjeraka;
}

void Ispis(Pozicija P)
{
	cout << "---------- ISPIS ---------- " << endl;
	if (P == NULL)
	{
		cout << "Knjiznica je prazna!" << endl;
		return;
	}
	while (P != NULL)
	{
		printf("%s %s (%d)\r\n", P->knjiga, P->autor, P->godina);
		P = P->next;
	}
}

void DodajKnjiguNaKraj(Pozicija P)
{
	char knjige[DULJINA];
	char autor[DULJINA];
	int godina = -1;
	int brojPrimjeraka = 0;
	Pozicija novaKnjiga = AlokacijaNoveKnjige();
	bool valid = false;
	do
	{
		cout << "Unesite ime knjige koju zelite dodati, autora, godinu u formatu IME_KNJIGE AUTOR GODINA: ";
		cin >> knjige >> autor >> godina;
		brojPrimjeraka = ReturnRandom();
		ToUpper(knjige); ToUpper(autor);
		if (cin.good())
		{
			//everything went well, we'll get out of the loop and return the value
			valid = true;
		}
		else
		{
			//something went wrong, we reset the buffer's state to good
			cin.clear();
			//and empty it
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Krivi unos, pokusajte ponovo." << endl;
		}
	} while (!valid);


	UnosInfoUKnjigu(novaKnjiga, knjige, autor, godina, brojPrimjeraka);
	while (P->next != NULL)
		P = P->next;
	novaKnjiga->next = P->next; //NULL
	P->next = novaKnjiga;
	novaKnjiga->prev = P;
}

void DodajKnjiguNaPocetak(Pozicija P)
{
	char knjige[DULJINA];
	char autor[DULJINA];
	int godina = -1;
	int brojPrimjeraka = 0;
	Pozicija novaKnjiga = AlokacijaNoveKnjige();
	bool valid = false;
	do
	{
		cout << "Unesite ime knjige koju zelite dodati, autora, godinu formatu IME_KNJIGE AUTOR GODINA: ";
		cin >> knjige >> autor >> godina;
		brojPrimjeraka = ReturnRandom();
		ToUpper(knjige); ToUpper(autor);
		if (cin.good())
		{
			//everything went well, we'll get out of the loop and return the value
			valid = true;
		}
		else
		{
			//something went wrong, we reset the buffer's state to good
			cin.clear();
			//and empty it
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Krivi unos, pokusajte ponovo." << endl;
		}
	} while (!valid);


	UnosInfoUKnjigu(novaKnjiga, knjige, autor, godina, brojPrimjeraka);
	novaKnjiga->next = P->next; //NULL
	P->next = novaKnjiga;
	novaKnjiga->prev = P;

}

void IzbrisiKnjigu(Pozicija P)
{
	char knjiga[DULJINA];
	Pozicija temp = P;
	Pozicija prev = NULL;

	int godina = -1;
	Pozicija novaKnjiga = AlokacijaNoveKnjige();
	bool valid = false;
	cout << "Unesite ime knjige koju zelite izbrisati: ";
	cin >> knjiga;

	ToUpper(knjiga);

	//Ako head sadrzi key 
	if (temp != NULL && (strcmp(temp->knjiga, knjiga) == 0))
	{
		P = temp->next; // Promijeni head
		free(temp);     // Izbrisi stari head
		return;
	}

	// Trazi key i cuvaj prev 
	while (temp != NULL && (strcmp(temp->knjiga, knjiga) != 0))
	{
		prev = temp;
		temp = temp->next;
	}

	//Ako key ne postoji
	if (temp == NULL)
	{
		cout << "Knjiga ne postoji!" << endl;
		return;
	}

	//Odvezi knjigu iz liste
	prev->next = temp->next;
	free(temp); //Oslobodi memoriju 

}

int IzbrojiKnjige(Pozicija P)
{
	int br = 0;
	while (P->next != NULL)
	{
		P = P->next;
		br++;
	}
	br++;
	cout << "\r\nUkupan broj knjiga: " << br - 1 << endl;

	return br - 1;
}

int PosudiKnjigu(Pozicija P)
{
	char knjiga[DULJINA];
	FILE* f;

	if ((f = fopen(posudeneDat, "a")) == NULL)
	{
		cout << "Datoteka ne postoji!" << endl;
		return 0;
	}
	cout << "Unesite knjigu koju zelite posuditi: ";
	scanf(" %s", knjiga);
	ToUpper(knjiga);

	P = Trazi(knjiga, P);
	if (P == NULL)
	{
		cout << "Knjiga ne postoji!" << endl;
		return 0;
	}
	else if (P != NULL)
	{
		if (P->brojKnjiga < 1)
		{
			cout << "Nema rasolozivih knjiga!" << endl;
			return NULL;
		}
		else
		{
			cout << "Posudena " << knjiga << " knjiga." << endl;
			P->brojKnjiga--;
			fprintf(f, "%s %s (%d)\n", P->knjiga, P->autor, P->godina);
		}

	}
	return OK;
}


void IspisiPosudeneKnjige()
{
	FILE* f;
	char c;
	if ((f = fopen(posudeneDat, "r+")) == NULL)
	{
		cout << "Datoteka ne postoji!" << endl;
		return;  //smije nastaviti s radom jer samo čita
	}
	cout << "ISPIS PRETHODNO POSUDENIH" << endl;
	while ((c = fgetc(f)) != EOF) {
		cout << c;
	}
}

Pozicija Trazi(char knjiga[], Pozicija P)
{
	while (P != NULL && strcmp(P->knjiga, knjiga) != 0)
		P = P->next;

	return P;
}

int UpdateajFile(Pozicija P)
{
	FILE* fp = NULL;
	if ((fp = fopen(imeDatoteke, "w+")) == NULL)
	{
		cout << "Greska pri otvaranju datoteke!" << endl;
		free(fp);
		return 0;
	}

	while (P != NULL)
	{
		fprintf(fp, "%s %s %d \n", P->knjiga, P->autor, P->godina);
		P = P->next;
	}
}

void DealociranjeMemorije(Pozicija head, char* lista)
{
	Pozicija temp;
	int brojac = 0;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
		brojac++;
	}
	cout << "Dealocirano " << brojac << " elemenata iz " << lista << endl;
}


void ToUpper(char naziv[])
{
	char* p;

	for (p = naziv; *p != '\0'; ++p)
	{
		*p = toupper(*p);
	}
}

int ReturnRandom()
{
	return (rand() % (5 - 1 + 1) + 1);
}