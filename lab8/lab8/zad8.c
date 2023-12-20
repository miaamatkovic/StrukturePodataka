/* 8. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIRECTORY_NAME (256)

#define ERROR_ALLOCATION (-1)

struct _tree;
typedef struct _tree* TreeP;
typedef struct _tree {
	int num;
	TreeP left;
	TreeP right;
}Tree;

struct _array;
typedef struct _array* ArrayP;
typedef struct _array {
	TreeP data;
	ArrayP next;
}Array;

int Menu() {
	printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
		"\t\t\MENU\n\n"
		"\ta) insert element\n"
		"\tb) print inorder\n"
		"\tc) print preorder\n"
		"\td) print postorder\n"
		"\te) print level order\n"
		"\tf) delete element\n"
		"\tg) find element\n"
		"\tx) exit\n\n"
		"Your choice: ");

	return 0;
}

ArrayP AllocateMemmoryForArray(TreeP);
int Push(ArrayP, TreeP);
TreeP Pop(ArrayP);

TreeP AllocateMemmoryForTree(int);
TreeP Insert(TreeP, TreeP);

int InOrder(TreeP);
int PreOrder(TreeP);
int PostOrder(TreeP);

int LevelOrder(TreeP);

TreeP Delete(TreeP, int);

TreeP Find(TreeP);
TreeP FindMax(TreeP);

int main(int agrc, char** argv) {
	TreeP root = NULL;
	TreeP temp = NULL;
	char choice;
	int element;

	while (1) {
		Menu();
		scanf(" %c", &choice);


		switch (tolower(choice))
		{
		case 'a':
			printf("What element would you like to insert: ");
			scanf(" %d", &element);
			root = Insert(root, element);
			break;
		case 'b':
			InOrder(root);
			break;
		case 'c':
			PreOrder(root);
			break;
		case 'd':
			PostOrder(root);
			break;
		case 'e':
			LevelOrder(root);
			break;
		case 'f':
			printf("What element would you like to delete: ");
			scanf(" %d", &element);
			root = Delete(root, element);
			break;
		case 'g':
			printf("What element would you like to find: ");
			scanf(" %d", &element);
			temp = Find(root, element);
			if (temp != NULL) {
				printf("Wanted element %d is placed on adress %d\n", temp->num, temp);
			}
			break;
		case 'x':
			printf("Bye!");
			return 0;
			break;
		default:
			printf("Invalid input!");
			break;
		}
	}

	return 0;
}

ArrayP AllocateMemmoryForArray(TreeP p) {
	ArrayP new = (ArrayP)malloc(sizeof(Array));

	if (new == NULL)
		return ERROR_ALLOCATION;

	new->data = p;
	new->next = NULL;
}

int Push(TreeP p, ArrayP head) {
	ArrayP new = AllocateMemmoryForArray(p);

	new->next = head->next;
	head->next = new;
	new->data = p;
}

TreeP Pop(ArrayP head) {
	if (head->next == NULL) {
		return 0;
	}
	else {
		while (head->next->next != NULL) {
			head = head->next;
		}
	}

	ArrayP temp = head->next;
	ArrayP position = temp->data;
	head->next = NULL;
	free(temp);

	return position;
}

TreeP AllocateMemmoryForTree(int number) {
	TreeP new = (TreeP)malloc(sizeof(Tree));

	if (new == NULL)
		return ERROR_ALLOCATION;

	new->num = number;
	new->left = NULL;
	new->right = NULL;
}

TreeP Insert(TreeP p, int number) {
	TreeP new = AllocateMemmoryForTree(number);

	if (p == NULL) {
		return new;
	}

	if (p->num < new->num) {
		p->right = Insert(p->right, new->num);
	}
	else if (p->num > new->num) {
		p->left = Insert(p->left, new->num);
	}
	else {
		free(new);
	}

	return p;
}

int InOrder(TreeP p) {
	if (p == NULL) {
		return NULL;
	}

	InOrder(p->left);
	printf("%d\n", p->num);
	InOrder(p->right);

	return 0;
}

int PreOrder(TreeP p) {
	if (p == NULL) {
		return NULL;
	}

	printf("%d\n", p->num);
	PreOrder(p->left);
	PreOrder(p->right);

	return 0;
}

int PostOrder(TreeP p) {
	if (p == NULL) {
		return NULL;
	}

	PostOrder(p->left);
	PostOrder(p->right);
	printf("%d\n", p->num);

	return 0;
}

int LevelOrder(TreeP p) {
	ArrayP head = AllocateMemmoryForArray(p);

	while (p != NULL) {
		printf("%d ", p->num);
		if (p->left != NULL) {
			Push(p->left, head);
		}
		if (p->right != NULL) {
			Push(p->right, head);
		}
		p = Pop(head);
	}
	free(head);

	return 0;
}

TreeP Delete(TreeP p, int number) {
	if (p == NULL) {
		return NULL;
	}

	if (p->num < number) {
		p->right = Delete(p->right, number);
	}
	else if (p->num > number) {
		p->left = Delete(p->left, number);
	}
	else {
		if (p->left != NULL) {
			TreeP temp = FindMax(p->left);
			p->num = temp->num;
			p->left = Delete(p->left, temp->num);
		}
		else if (p->right != NULL) {
			TreeP temp = FindMax(p->right);
			p->num = temp->num;
			p->right = Delete(p->right, temp->num);
		}
		else {
			free(p);
			return NULL;
		}
	}

	return p;
}

TreeP Find(TreeP p, int number) {
	if (p == NULL) {
		return NULL;
	}

	if (p->num < number) {
		return Find(p->right, number);
	}
	else if (p->num > number) {
		return Find(p->left, number);
	}
	else {
		return p;
	}
}

TreeP FindMax(TreeP p) {
	while (p->right != NULL) {
		p = p->right;
	}

	return p;
}