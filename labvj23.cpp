#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct Osobe* pozicija;
struct Osobe {

	char ime[50];
	char prezime[50];
	int god_rod;
	pozicija next;

};

pozicija kreiraj_osobu(const char* ime, const char* prezime, int god_rod)
{

	pozicija novaOsoba;
	novaOsoba = (pozicija)malloc(sizeof(struct Osobe));
	if (novaOsoba == NULL)
	{
		printf("Erorr in malloc");
		return NULL;
	}

	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);

	novaOsoba->god_rod = god_rod;
	novaOsoba->next = NULL;

	return novaOsoba;

}

void dodajPocetak(pozicija head, pozicija novaOsoba)
{
	novaOsoba->next = head->next;
	head->next = novaOsoba;
}


void ispis(pozicija head) {
	pozicija temp;
	temp = head->next;

	while (temp != NULL)
	{
		printf("%s %s %d\n", temp->ime, temp->prezime, temp->god_rod);
		temp = temp->next;
	}
}

void dodajKraj(pozicija head, pozicija novaOsoba)
{
	pozicija temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	temp->next = novaOsoba;
}

pozicija PronadiPrezime(pozicija head, const char* prezime)
{

	pozicija temp = head->next;

	while (temp != NULL)
	{
		if (strcmp(temp->prezime, prezime) == 0)
		{
			return temp;
		}

		temp = temp->next;
	}

	return NULL;

}

void brisi_po_prezimenu(pozicija head, const char* prezime)
{
	pozicija temp;
	temp = head;




	while (temp->next != NULL)
	{
		if (strcmp(temp->next->prezime, prezime) == 0)
		{
			pozicija prev = temp->next;
			temp->next = prev->next;
			free(prev);
			printf("Osoba s prezimenom '%s' je obrisana iz liste.\n", prezime);
			return;
		}

		temp = temp->next;
	}

	printf("Osoba s prezimenom '%s' nije pronađena.\n", prezime);

}

void dodajIza(pozicija head, const char* prezime, pozicija novaOsoba)
{
	pozicija temp = PronadiPrezime(head, prezime);
	if (temp != NULL)
	{
		novaOsoba->next = temp->next;
		temp->next = novaOsoba;
		printf("Dodana osoba iza prezimena '%s'.\n", prezime);
	}


	else {
		printf("Osoba s prezimenom '%s' nije pronađena.\n", prezime);
	}

}

void  dodajIspred(pozicija head, const char* prezime, pozicija novaOsoba)
{
	pozicija temp = head;
	while (temp->next != NULL && strcmp(temp->next->prezime, prezime) != 0) {
		temp = temp->next;
	}
	if (temp->next != NULL)
	{
		novaOsoba->next = temp->next;
		temp->next = novaOsoba;
		printf("Dodana osoba ispred prezimena '%s'.\n", prezime);
	}
	else {
		printf("Osoba s prezimenom '%s' nije pronađena.\n", prezime);
	}

}


void sortirajListu(pozicija head) {
	pozicija i, j, prev_i, temp;
	for (i = head->next; i != NULL; i = i->next) {
		for (j = head; j->next->next != NULL; j = j->next) {
			if (strcmp(j->next->prezime, j->next->next->prezime) > 0) {
				temp = j->next;
				j->next = temp->next;
				temp->next = j->next->next;
				j->next->next = temp;
			}
		}
	}
	printf("Lista sortirana po prezimenima.\n");
}


void UpisiUDatoteku(pozicija head, const char* ime_datoteke)
{
	FILE* fp = fopen(ime_datoteke, "w");
	if (fp == NULL)
	{
		printf("Erorr in file opening");
		return;
	}

	pozicija temp = head->next;
	while (temp != NULL)
	{
		fprintf(fp, "%s %s %d\n", temp->ime, temp->prezime, temp->god_rod);
		temp = temp->next;
	}
	printf("Lista upisana u datoteku '%s'.\n", ime_datoteke);
	fclose(fp);

}

void UcitajIzDatoteke(pozicija head, const char* ime_datoteke)
{
	FILE* fp = fopen(ime_datoteke, "w");
	if (fp == NULL)
	{
		printf("Erorr in file opening");
		return;
	}
	char ime[60], prezime[60];
	int god_rod=0;

	while (fscanf(fp, "%s %s %d", ime, prezime, &god_rod) == 3) {
		pozicija novaOsoba = kreiraj_osobu(ime, prezime, god_rod);
		dodajKraj(head, novaOsoba);
	
	}
	fclose(fp);
	printf("Lista učitana iz datoteke '%s'.\n", ime_datoteke);

}

int main()
{

	struct Osobe head;
	head.next = NULL;

	pozicija osoba1 = kreiraj_osobu("Ana", "Anic", 1990);
	dodajPocetak(&head, osoba1);


	pozicija osoba2 = kreiraj_osobu("Ive", "Ivic", 1997);
	dodajKraj(&head, osoba2);


	pozicija osoba3 = kreiraj_osobu("Luka", "Lukic", 1988);
	dodajKraj(&head, osoba3);

	printf("Lista osoba nakon dodavanja na početak i kraj:\n");
	ispis(&head);


	const char* prezime_za_pretragu = "Ivic";
	pozicija pronadena_osoba = PronadiPrezime(&head, prezime_za_pretragu);



	if (pronadena_osoba != NULL) {
		printf("\nOsoba pronađena s prezimenom '%s': %s %s, %d\n",
			prezime_za_pretragu, pronadena_osoba->ime, pronadena_osoba->prezime, pronadena_osoba->god_rod);
	}
	else {
		printf("\nOsoba s prezimenom '%s' nije pronađena.\n", prezime_za_pretragu);
	}

	const char* prezime_za_brisanje = "Anic";
	brisi_po_prezimenu(&head, prezime_za_brisanje);



	printf("\nLista osoba nakon brisanja:\n");
	ispis(&head);

	pozicija osoba4 = kreiraj_osobu("Ivan", "Ivanovic", 1988);
	dodajIza(&head, "Ivic", osoba4);

	pozicija osoba5 = kreiraj_osobu("Luka", "Topic", 1997);
	dodajIspred(&head, "Lukic", osoba5);

	printf("\nLista nakon dodavanja iza i ispred određenog prezimena:\n");
	ispis(&head);

	sortirajListu(&head);
	printf("\nSortirana lista:\n");
	ispis(&head);

	UpisiUDatoteku(&head, "osobe.txt");

	return 0;
}

