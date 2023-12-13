/* Napisati program koji čita datoteku racuni.txt u kojoj su zapisani nazivi svih datoteka koji
predstavljaju pojedini račun. Na početku svake datoteke je zapisan datum u kojem vremenu je
račun izdat u formatu YYYY-MM-DD. Svaki sljedeći red u datoteci predstavlja artikl u formatu
naziv, količina, cijena. Potrebno je formirati vezanu listu računa sortiranu po datumu. Svaki čvor
vezane liste sadržava vezanu listu artikala sortiranu po nazivu artikla. Nakon toga potrebno je
omogućiti upit kojim će korisnik saznati koliko je novaca sveukupno potrošeno na specifični
artikl u određenom vremenskom razdoblju i u kojoj je količini isti kupljen. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGHT (50)
#define MAX_DATE_LENGHT (111)
#define MAX_LINE (1024)
#define FILE_NOT_OPEN (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)

typedef struct _article* articlePosition;
typedef struct _article {
	char name[MAX_LENGHT];
	int quanity;
	int price;
	articlePosition next;
}article;

typedef struct _receipt* receiptPosition;
typedef struct _receipt {
	char receiptDate[MAX_DATE_LENGHT];
	article articleHead;
	receiptPosition next;
}receipt;
