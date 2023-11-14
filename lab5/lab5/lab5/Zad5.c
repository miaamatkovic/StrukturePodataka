//5. Napisati program koji iz datoteke cita postfiks izraz i zatim korištenjem stoga racuna
//rezultat.Stog je potrebno realizirati preko vezane liste.

#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 128
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct _stackElement;
typedef struct _stackElement* Position;
typedef struct _stackElement {
	double number;
	Position next;
} StackElement;


int calculatePostfixString(Position head, double* result);
int readFile(char* fileName, char* buffer);
int calculatingElements(Position head, char* buffer, double* result);
Position createNewStackEl(double number);
int performOperation(Position head, char op, double* result);
int push(Position head, Position newStackEl);
int pop(Position head, double* result);
int printStack(Position first);
int printResultAndEmptyStack(Position head, double* result);

int main() {

	StackElement head = { 0,NULL };
	double result = 0.0;

	calculatePostfixString(&head, &result);

	printf("Result: %0.1lf", result);

	return 0;
}

int calculatePostfixString(Position head, double* result)
{

	char buffer[MAX_SIZE] = { 0 };

	readFile("postfix.txt", buffer);

	calculatingElements(head, buffer, result);


	return 0;
}

int readFile(char* fileName, char* buffer) {

	FILE* file;
	file = fopen(fileName, "r");

	fgets(buffer, MAX_SIZE, file);

	printf("%s\n", buffer);

	fclose(file);

	return 0;
}

int calculatingElements(Position head, char* buffer, double* result) {

	char* currentBuffer = buffer;
	int readNums = 0;
	char op = 0;
	int numBytes = 0;
	double number = 0.0;
	Position newStackEl = NULL;

	while (strlen(currentBuffer) > 0) {
		readNums = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (readNums != 1) {
			sscanf(currentBuffer, " %c %n", &op, &numBytes);

			performOperation(head, op, result);

			number = *result;
		}

		newStackEl = createNewStackEl(number);

		if (!newStackEl) {
			printf("Element not created\n");
			return -1;
		}

		currentBuffer += numBytes;
		printf("%s <->", currentBuffer);
		push(head, newStackEl);
	}

	return printResultAndEmptyStack(head, result);

}

int performOperation(Position head, char op, double* result) {

	double oper1 = 0.0;
	double oper2 = 0.0;

	pop(head, &oper1);
	pop(head, &oper2);

	switch (op) {
	case '+':
		*result = oper2 + oper1;
		break;
	case '-':
		*result = oper2 - oper1;
		break;
	case '*':
		*result = oper2 * oper1;
		break;
	case '/':
		*result = oper2 / oper1;
		break;
	default:
		printf("Invalid operator\n");
		break;
	}

	return 0;
}

int printResultAndEmptyStack(Position head, double* result) {

	pop(head, result);

	return 0;
}

Position createNewStackEl(double number) {

	Position newStackEl = NULL;
	newStackEl = (Position)malloc(sizeof(StackElement));
	if (!newStackEl) {
		printf("Error at malloc\n");
		return NULL;
	}
	newStackEl->number = number;
	newStackEl->next = NULL;

	return newStackEl;
}

int push(Position head, Position newStackEl) {
	newStackEl->next = head->next;
	head->next = newStackEl;

	printStack(head->next);

	return 0;
}

int pop(Position head, double* result) {

	Position toDel = NULL;
	toDel = head->next;

	if (!toDel) {
		printf("Stack empty.\n");
		return -1;
	}

	head->next = toDel->next;

	*result = toDel->number;

	free(toDel);

	return 0;
}

int printStack(Position first) {

	Position current = first;

	while (current) {
		printf(" %0.1lf", current->number);
		current = current->next;
	}
	printf("\n");

	return 0;
}