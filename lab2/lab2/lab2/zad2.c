/*
2. Definirati strukturu osoba (ime, prezime, godina rodenja) i napisati program koji:
A. dinamicki dodaje novi element na pocetak liste,
B. ispisuje listu,
C. dinamicki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. brise odredeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];      //Position tip podataka koji predstavlja pokazivac na strukturu _Person 
	int birthYear;					//u funkcijama koje rade s vezanim listama
	Position next;
} Person;

int addOnHead(Position head);
int addToEnd(Position head);
int print(Position first);
int findPerson(Position head);
int deletePerson(Position head);
Position createPerson();
Position findLast(Position head);
int printPerson(Position person);
int menu(Position head);
char* wishedSurname();



Position createPerson()			//stvaranje nove osobe
{
	Position newPerson = NULL;
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;

	newPerson = (Position)malloc(sizeof(Person));		//alociranje memorije
	if (!newPerson)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	printf("Enter name:\n");
	scanf(" %s", name);
	printf("Enter surname:\n");
	scanf(" %s", surname);
	printf("Enter birth year:\n");
	scanf(" %d", &birthYear);


	strcpy(newPerson->name, name);			//kopiranje niz znakova (ime, prez, datum rod. u odgovarajuca polja u strukturi
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	return newPerson;
}

int addOnHead(Position head)			//dodavanje nove osobe na pocetak liste
{
	Position newPerson = NULL;

	newPerson = createPerson();		//funkcija poziva funkciju createPerson() koja "pravi" novu osobu 

	if (newPerson)					//ako je stvaranje nove osobe uspjelo, funkcija dodaje novu osobu na pocetak liste
	{
		newPerson->next = head->next;		//pokazivac next nove osobe postavi na pokazivac na prvu osobu u listi
		head->next = newPerson;				//pokazivaz next glave liste postavi na pokazivac na novu osobu
	}

	return EXIT_SUCCESS;
}

Position findLast(Position head)		//pronalazenje posljednje osobe
{
	while (head->next != NULL)			//while petlja prolazi kroz cijelu listu da pronade posljednju osobu
	{
		head = head->next;
	}

	return head;
}

int addToEnd(Position head)			//dodavanje nove osobe na kraj liste
{
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		head = findLast(head);
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int print(Position first)			//ispis i funkcija prima pokazivac na prvu osobu u listi
{
	if (!first)
	{
		perror("Empty list!\n");		//perror() je funkcija za "gresku"
	}
	for (; first != NULL; first = first->next)
	{
		printf("Name: %s\t Surname: %s\t Birth year: %d\t\n", first->name, first->surname, first->birthYear);
	}

	return EXIT_SUCCESS;
}

char* wishedSurname()		//trazi osobu po prezimenu
{
	char surname[MAX_SIZE] = { 0 };
	printf("Enter surname to serch for the wanted person:\n");
	scanf(" %s", surname);

	return surname;
}

int findPerson(Position head)		//funkcija nadi osobu koja poziva funkciju wishedSurname()
{
	if (head->next)
	{
		while (head->next && strcmp(head->next->surname, wishedSurname()) != 0)
		{
			head = head->next;
		}
		if (head->next)
		{
			printPerson(head->next);			//ako je nadeno prezime osobe u listi ispisat ce se podatci te osobe
		}
		else
		{
			perror("Can't find person with that surname!\n");
			return -1;
		}
	}
	else
	{
		perror("Empty list!\n");
	}

	return EXIT_SUCCESS;
}
int deletePerson(Position head)
{												//brisanje osobe po prezimenu
	if (head->next)
	{
		Position previous = NULL;

		while (head->next && strcmp(head->surname, wishedSurname()) != 0)
		{
			previous = head;
			head = head->next;
		}
		if (previous->next && strcmp(head->surname, wishedSurname()) == 0)
		{
			printPerson(head);
			previous->next = head->next;
			free(head);
			printf("Deleted!\n");
		}
		else
		{
			perror("Can't find person with that surname!\n");
			return -1;
		}
	}
	else
	{
		perror("Empty list!\n");
	}

	return EXIT_SUCCESS;
}

int printPerson(Position person)
{
	printf("Name: %s, surname: %s, birth year: %d, adress: %p\n",
		person->name, person->surname, person->birthYear, person);

	return EXIT_SUCCESS;
}

int menu(Position Head)		//opcije za funkcije da se izvrse
{
	char choice = '\0';
	while (1) {
		printf("Enter A(Add on head), E(Add to the end of list), P(Print), S(Search), D(Delete), X(Exit)\n");
		scanf(" %c", &choice);
		if (tolower(choice) == 'a')
			addOnHead(Head);				//tolower() za A i a
		else if (tolower(choice) == 'e')
			addToEnd(Head);
		else if (tolower(choice) == 'p')
			print(Head->next);
		else if (tolower(choice) == 's')
		{
			while (findPerson(Head) == -1)
			{
				findPerson(Head);
			}
		}
		else if (tolower(choice) == 'd')
		{
			while (deletePerson(Head) == -1)
			{
				deletePerson(Head);
			}
		}
		else if (tolower(choice) == 'x')
			break;
		else
			perror("Wrong insert!\n");
	}
	return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0},
				.surname = {0}, .birthYear = 0 };
	menu(&Head);


	return EXIT_SUCCESS;
}
