#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
#define MAX_SIZE 128
#define MAX_POINTS 15
#define FILE_NOT_OPEN -1

typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
} Student;

int brojRedovaUdadoteci() {
	int brojac = 0;
	FILE* file_pointer = NULL;
	char buffer[MAX_SIZE] = { 0 };
	file_pointer = fopen("dat.txt", "r");
	if (!file_pointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return FILE_NOT_OPEN;
	}
	while (!feof(file_pointer))
	{
		fgets(buffer, MAX_SIZE, file_pointer);
		brojac++;
	}
	fclose(file_pointer);
	return brojac;
}

Student* alocirajMemorijuIprocitajStudente(int brojStudenata)
{
	int brojac = 0;
	FILE* filePointer = NULL;
	Student* studenti = NULL;
	studenti = (Student*)malloc(brojStudenata * sizeof(Student));
	if (!studenti)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return NULL;
	}
	filePointer = fopen("dat.txt", "r");
	if (!filePointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return FILE_NOT_OPEN;
	}
	while (!feof(filePointer))
	{
		fscanf(filePointer, "%s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}
	fclose(filePointer);
	return studenti;
}
int ispis(int brojStudenata, Student* studenti)
{
	for (int i = 0; i < brojStudenata; i++)
	{
		printf("%s %s - %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
	}
	return 0;
}

int main() {
	int red = 0;
	Student* studenti = NULL;
	red = brojRedovaUdadoteci();
	if (red > 0)
	{
		studenti = alocirajMemorijuIprocitajStudente(red);
		ispis(red, studenti);
		free(studenti);
	}

	return EXIT_SUCCESS;
}
