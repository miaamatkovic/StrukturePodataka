#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)
#define FILE_NOT_OPEN (-1)
#define EMPTY_LIST (-2)
#define FAILED_MEMORY_ALLOCATION (NULL)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int coefficient;
	int exponent;
	Position next;
} Element;

int readPolyFromFile(Position headP1, Position headP2, char* file);
int printPoly(char* polynomialName, Position first);
int addPoly(Position resultHead, Position headP1, Position headP2);
int multiplyPoly(Position resultHead, Position headP1, Position headP2);
int freeMemory(Position head);
int parseStringIntoList(Position head, char* buffer);
Position createElement(int coefficient, int exponent);
int insertSorted(Position head, Position newElement);
int mergeAfter(Position current, Position newElement);
int insertAfter(Position current, Position newElement);
int deleteAfter(Position previous);
int createAndInsertAfter(int coefficient, int exponent, Position current);
int sortPoly(Position head);

int main()
{
	Element headP1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headP2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headPAdd = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headPMultiply = { .coefficient = 0, .exponent = 0, .next = NULL };
	char* fileName = "polynomes.txt";

	if (readPolyFromFile(&headP1, &headP2, fileName) == EXIT_SUCCESS)
	{
		printPoly("First polynomial: ", headP1.next);
		printPoly("Second polynomial: ", headP2.next);

		addPoly(&headPAdd, headP1.next, headP2.next);
		printPoly("Added polynomials: ", headPAdd.next);
		//printf("%d\n", headAdd.next->exponent);
		sortPoly(headPAdd.next);
		printPoly("Sorted added polynomials: ", headPAdd.next);
		multiplyPoly(&headPMultiply, headP1.next, headP2.next);

		printPoly("Multiplied polynomials: ", headPMultiply.next);

		freeMemory(&headP1);
		freeMemory(&headP2);
		freeMemory(&headPAdd);
		freeMemory(&headPMultiply);
	}
	return 0;
}

int readPolyFromFile(Position headP1, Position headP2, char* fileName)
{
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;

	filePointer = fopen("polynomes.txt", "r");
	if (!filePointer)
	{
		printf("File not found!\n");
		return FILE_NOT_OPEN;
	}

	fgets(buffer, MAX_LINE, filePointer);
	status = parseStringIntoList(headP1, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, filePointer);
	status = parseStringIntoList(headP2, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int printPoly(char* polynomeName, Position first) {
	printf(" %s = ", polynomeName);
	if (first) {
		if (first->exponent < 0) {
			if (first->coefficient == 1) {
				printf("x^(%d)", first->exponent);
			}
			else {
				printf("%dx^(%d)", first->coefficient, first->exponent);
			}
		}
		else {
			if (first->coefficient == 1) {
				printf("x^%d", first->exponent);
			}
			else {
				printf("%dx^%d", first->coefficient, first->exponent);
			}
		}

		first = first->next;
	}

	for (; first != NULL; first = first->next) {
		if (first->coefficient < 0) {
			if (first->exponent < 0) {
				printf(" - %dx^(%d)", abs(first->coefficient), first->exponent);
			}
			else {
				printf(" - %dx^%d", abs(first->coefficient), first->exponent);
			}
		}
		else {
			if (first->exponent < 0) {
				if (first->coefficient == 1) {
					printf(" + x^(%d)", first->exponent);
				}
				else {
					printf(" + %dx^(%d)", first->coefficient, first->exponent);
				}
			}
			else {
				if (first->coefficient == 1) {
					printf(" + x^%d", first->exponent);
				}
				else {
					printf(" + %dx^%d", first->coefficient, first->exponent);
				}
			}
		}
	}

	printf("\n");
	return EXIT_SUCCESS;
}

int addPoly(Position resultHead, Position headP1, Position headP2)
{
	Position currentPoly1 = headP1;
	Position currentPoly2 = headP2;
	Position currentResult = resultHead;
	Position remainingPoly = NULL;

	while (currentPoly1 != NULL && currentPoly2 != NULL)
	{
		if (currentPoly1->exponent == currentPoly2->exponent)
		{
			createAndInsertAfter(currentPoly1->coefficient + currentPoly2->coefficient, currentPoly1->exponent, currentResult);
			currentPoly1 = currentPoly1->next;
			currentPoly2 = currentPoly2->next;
			currentResult = currentResult->next;
		}
		else if (currentPoly1->exponent < currentPoly2->exponent)
		{
			createAndInsertAfter(currentPoly1->coefficient, currentPoly1->exponent, currentResult);
			currentPoly1 = currentPoly1->next;
			currentResult = currentResult->next;
		}
		else
		{
			createAndInsertAfter(currentPoly2->coefficient, currentPoly2->exponent, currentResult);
			currentPoly2 = currentPoly2->next;
			currentResult = currentResult->next;
		}

	}
	if (currentPoly1 == NULL)
	{
		remainingPoly = currentPoly2;
	}
	else
	{
		remainingPoly = currentPoly1;
	}

	while (remainingPoly != NULL)
	{
		createAndInsertAfter(remainingPoly->coefficient, remainingPoly->exponent, currentResult);
		remainingPoly = remainingPoly->next;
		currentResult = currentResult->next;
	}

	return EXIT_SUCCESS;
}

int multiplyPoly(Position resultHead, Position headP1, Position headP2)
{
	if (headP1 != NULL || headP2 != NULL)
	{
		for (Position currentPoly1 = headP1; currentPoly1 != NULL; currentPoly1 = currentPoly1->next)
		{
			for (Position currentPoly2 = headP2; currentPoly2 != NULL; currentPoly2 = currentPoly2->next)
			{
				Position newElement = createElement(currentPoly1->coefficient * currentPoly2->coefficient, currentPoly1->exponent + currentPoly2->exponent);
				if (!newElement)
				{
					return EXIT_FAILURE;
				}

				insertSorted(resultHead, newElement);
			}
		}
		return EXIT_SUCCESS;
	}
	return EMPTY_LIST;
}

int freeMemory(Position head)
{
	Position current = head;

	while (current->next)
	{
		deleteAfter(current);
	}

	return EXIT_SUCCESS;
}

int parseStringIntoList(Position head, char* buffer)
{
	char* currentBuffer = buffer;
	int coefficient = 0;
	int exponent = 0;
	int numBytes = 0;
	int status = 0;
	Position newElement = NULL;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %dx^%d %n", &coefficient, &exponent, &numBytes);
		if (status != 2)
		{
			printf("This file is not good!\n");
			return EXIT_FAILURE;
		}

		newElement = createElement(coefficient, exponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		insertSorted(head, newElement);

		currentBuffer += numBytes;
	}

	return EXIT_SUCCESS;
}

Position createElement(int coefficient, int exponent)
{
	Position element = NULL;

	element = (Position)malloc(sizeof(Element));
	if (!element)
	{
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	element->coefficient = coefficient;
	element->exponent = exponent;
	element->next = NULL;

	return element;
}

int insertSorted(Position head, Position newElement)
{
	Position current = head;

	while (current->next != NULL && current->next->exponent > newElement->exponent)
	{
		current = current->next;
	}

	mergeAfter(current, newElement);

	return EXIT_SUCCESS;
}

int mergeAfter(Position current, Position newElement)
{
	if (current->next == NULL || current->next->exponent != newElement->exponent)
	{
		insertAfter(current, newElement);
	}
	else
	{
		int resultCoefficient = current->next->coefficient + newElement->coefficient;
		if (resultCoefficient == 0)
		{
			deleteAfter(current);
		}
		else
		{
			current->next->coefficient = resultCoefficient;
		}
		free(newElement);
	}

	return EXIT_SUCCESS;
}

int insertAfter(Position current, Position newElement)
{
	newElement->next = current->next;
	current->next = newElement;

	return EXIT_SUCCESS;
}

int deleteAfter(Position previous)
{
	Position toDelete = NULL;

	toDelete = previous->next;
	previous->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}

int createAndInsertAfter(int coefficient, int exponent, Position current)
{
	Position newElement = createElement(coefficient, exponent);
	if (!newElement)
	{
		return EXIT_FAILURE;
	}

	insertAfter(current, newElement);

	return EXIT_SUCCESS;
}

int sortPoly(Position first)
{
	Position temp;
	Position second = first->next;
	for (first; first->next != NULL; first = first->next)
	{
		for (second; second->next != NULL; second = second->next)
		{
			if (first->exponent < second->exponent)
			{
				temp = first;
				first = second;
				second = temp;
			}
		}
	}

	return EXIT_SUCCESS;
}