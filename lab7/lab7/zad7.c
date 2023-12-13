//Napisati program koji pomoću vezanih listi(stabala) predstavlja strukturu direktorija.
//Omogućiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
//povratak u prethodni direktorij.Točnije program treba preko menija simulirati
//korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct _dir* PositionDir;
typedef struct _dir {
    char name[MAX_NAME_LENGTH];
    PositionDir nextDir;
    PositionDir subDir;
    PositionDir parentDir;
} Dir;

typedef struct _levelStack* PositionStack;
typedef struct _levelStack {
    PositionDir directoryLevel;
    PositionStack next;
} LevelStack;

int menu(PositionDir rootDir, PositionStack stackTop);
PositionDir createSubDir(PositionDir currentDir, char* dirName);
int printDirCont(PositionDir currentDir);
PositionDir changeDir(PositionDir currentDir, char* wantedDir);

int push(PositionStack HeadStack, PositionDir LevelDir);
PositionDir pop(PositionStack stackTop);

int main() {
    Dir HeadDir = { {0}, NULL, NULL };
    LevelStack HeadStack = { NULL, NULL };

    PositionDir rootDir = NULL;
    rootDir = createSubDir(&HeadDir, "C:");

    push(&HeadStack, rootDir);
    menu(rootDir, &HeadStack);

    free(rootDir);

    return EXIT_SUCCESS;
}
int menu(PositionDir rootDir, PositionStack stackTop) {
    char choice = '\0', dirName[MAX_NAME_LENGTH] = { 0 };
    PositionDir currentDir = rootDir, result = NULL;

    while (1) {

        printf("\nMenu:\n");
        printf("1 - md (Create Directory)\n");
        printf("2 - cd dir (Change Directory)\n");
        printf("3 - cd.. (Go Up)\n");
        printf("4 - dir (List Contents)\n");
        printf("5 - exit\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {

        case '1':
            printf("\nEnter new directory name: ");
            scanf("%s", dirName);

            result = createSubDir(currentDir, dirName);

            if (result != NULL)
                printf("\nSuccessfully created subdirectory %s\n", dirName);

            else
                printf("\nFailed creation of subdirectory!\n");

            continue;

        case '2':
            printf("\nEnter destination directory name: ");
            scanf(" %s", dirName);

            result = changeDir(currentDir, dirName);

            if (result != NULL) {
                printf("\nSuccessfully moved to directory %s\n", dirName);
                push(stackTop, result);
                currentDir = result;
            }
            else
                printf("\nDestination directory not found in current directory!\n");

            continue;

        case '3':
            if (currentDir != rootDir) {
                currentDir = pop(stackTop);
                printf("\nSuccessfully moved to directory %s\n", currentDir->name);
            }
            else {
                printf("\nAlready in root directory!\n");
                pop(stackTop);
                break;
            }

            continue;

        case '4':
            printDirCont(currentDir);

            continue;
        case '5':
            printf("\nExiting the program.\n");

            break;

        default:
            printf("\nInvalid input, please try again.\n");

            continue;
        }
        break;
    }
    return EXIT_SUCCESS;
}
PositionDir createSubDir(PositionDir currentDir, char* dirName) {
    PositionDir newDir = NULL;

    newDir = malloc(sizeof(Dir));

    if (!newDir) {
        printf("\nCan't allocate memory!\n");
        return NULL;
    }
    strcpy(newDir->name, dirName);
    newDir->subDir = NULL;

    newDir->nextDir = currentDir->subDir;
    currentDir->subDir = newDir;

    return newDir;
}
int printDirCont(PositionDir currentDir) {
    PositionDir currentSubDir = currentDir->subDir;

    printf("\nContents of directory %s:\n", currentDir->name);

    while (currentSubDir != NULL) {
        printf("%s\n", currentSubDir->name);
        currentSubDir = currentSubDir->nextDir;
    }

    if (currentDir->subDir == NULL)
        printf("(empty)\n");

    return EXIT_SUCCESS;
}
PositionDir changeDir(PositionDir currentDir, char* wantedDir) {
    if (!currentDir || !wantedDir) {
        printf("\nError!\n");
        return NULL;
    }
    if (strcmp(wantedDir, "..") == 0) {
        if (currentDir->parentDir)
            return currentDir->parentDir;
        else {
            printf("\nError: Already in root directory!\n");
            return NULL;
        }
    }
    PositionDir currentSubDir = currentDir->subDir;

    while (currentSubDir != NULL && strcmp(currentSubDir->name, wantedDir) != 0)
        currentSubDir = currentSubDir->nextDir;

    return currentSubDir;
}
int push(PositionStack stackTop, PositionDir LevelDir) {
    //PositionStack newStack = NULL;
    if (!stackTop) {
        printf("\nError!\n");
        return EXIT_FAILURE;
    }
    PositionStack newStack = malloc(sizeof(LevelStack));
    if (!newStack) {
        printf("\nMemory allocation failed!\n");
        return EXIT_FAILURE;
    }

    newStack->directoryLevel = LevelDir;

    newStack->next = stackTop->next;
    stackTop->next = newStack;

    return EXIT_SUCCESS;
}
PositionDir pop(PositionStack stackTop) {
    PositionDir LevelDir = NULL;
    PositionStack toDel = stackTop->next;

    stackTop->next = toDel->next;
    free(toDel);

    if (stackTop->next != NULL)
        LevelDir = stackTop->next->directoryLevel;

    return LevelDir;
}
