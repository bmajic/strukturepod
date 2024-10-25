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

	return 0;
}

