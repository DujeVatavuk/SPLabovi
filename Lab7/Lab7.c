/*
* Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct _directory;
typedef struct _directory* Position;
typedef struct _directory {
    char name[MAX_NAME_LENGTH];
    Position subDirectories;
    Position next;
} Directory;

Position createDirectory(char name[MAX_NAME_LENGTH]);
Position createSubdirectory(char name[MAX_NAME_LENGTH], Position currentDirectory);
Position changeDirectory(char name[MAX_NAME_LENGTH], Position currentDirectory);
Position goUpOneLevel(Position currentDirectory, Position rootDirectory);
void listDirectoryContents(Position currentDirectory);

int main() {
    Directory head = {
        .name = {0},
        .subDirectories = NULL,
        .next = NULL
    };
    Position firstDirectory = createDirectory("C:");
    head.next = firstDirectory;

    Position currentDirectory = firstDirectory;

    while (1) {
        printf("\nMenu:\n");
        printf("1 - md (Create Directory)\n");
        printf("2 - cd dir (Change Directory)\n");
        printf("3 - cd.. (Go Up)\n");
        printf("4 - dir (List Contents)\n");
        printf("5 - exit\n");

        char choice[10];
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            char directoryName[MAX_NAME_LENGTH];
            printf("Enter directory name: ");
            scanf("%s", directoryName);
            createSubdirectory(directoryName, currentDirectory);
        }
        else if (strcmp(choice, "2") == 0) {
            char directoryName[MAX_NAME_LENGTH];
            printf("Enter directory name: ");
            scanf("%s", directoryName);
            currentDirectory = changeDirectory(directoryName, currentDirectory);
        } else if (strcmp(choice, "3") == 0) {
            currentDirectory = goUpOneLevel(currentDirectory, firstDirectory);
        } else if (strcmp(choice, "4") == 0) {
            listDirectoryContents(currentDirectory);
        } else if (strcmp(choice, "5") == 0) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    // Free allocated memory
    free(firstDirectory);

    return 0;
}

Position createDirectory(char name[MAX_NAME_LENGTH]) {
    Position newDirectory = NULL;
    newDirectory = (Position)malloc(sizeof(Directory));
    if (!newDirectory) {
        printf("Can't allocate memory!\n");
        return NULL;
    }
    strcpy(newDirectory->name, name);
    newDirectory->subDirectories = NULL;
    newDirectory->next = NULL;
    return newDirectory;
}

Position createSubdirectory(char name[MAX_NAME_LENGTH], Position currentDirectory) {
    Position newDirectory = NULL;
    newDirectory = createDirectory(name);
    newDirectory->next = currentDirectory->subDirectories;
    currentDirectory->subDirectories = newDirectory;
    return newDirectory;
}

Position changeDirectory(char name[MAX_NAME_LENGTH], Position currentDirectory) {
    Position subdirectory = currentDirectory->subDirectories;
    while (subdirectory != NULL) {
        if (strcmp(subdirectory->name, name) == 0) {
            return subdirectory;
        }
        subdirectory = subdirectory->next;
    }
    printf("Directory '%s' not found.\n", name);
    return currentDirectory;
}

Position goUpOneLevel(Position currentDirectory, Position rootDirectory) {
    if (currentDirectory != rootDirectory) {
        Position parent = rootDirectory;
        while (parent != NULL) {
            if (parent->subDirectories == currentDirectory) {
                return parent;
            }
            parent = parent->next;
        }
        printf("Error: Parent directory not found.\n");
        return currentDirectory;
    }
    else {
        printf("Already in the root directory.\n");
        return currentDirectory;
    }
}

void listDirectoryContents(Position currentDirectory) {
    printf("Contents of directory '%s':\n", currentDirectory->name);
    Position subdirectory = currentDirectory->subDirectories;
    while (subdirectory != NULL) {
        printf(" - %s\n", subdirectory->name);
        subdirectory = subdirectory->next;
    }
    if (currentDirectory->subDirectories == NULL) {
        printf("   (empty)\n");
    }
}
