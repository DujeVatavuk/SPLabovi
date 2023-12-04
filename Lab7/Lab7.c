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
    Position rootDirectory = createDirectory("C:");
    head.next = rootDirectory;

    Position currentDirectory = rootDirectory;

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
            printf("\033[0;32mEnter directory name: \033[0m");
            scanf("%s", directoryName);
            createSubdirectory(directoryName, currentDirectory);
        }
        else if (strcmp(choice, "2") == 0) {
            char directoryName[MAX_NAME_LENGTH];
            printf("\033[0;32mEnter directory name: \033[0m");
            scanf("%s", directoryName);
            currentDirectory = changeDirectory(directoryName, currentDirectory);
        } else if (strcmp(choice, "3") == 0) {
            currentDirectory = goUpOneLevel(currentDirectory, rootDirectory);
        } else if (strcmp(choice, "4") == 0) {
            listDirectoryContents(currentDirectory);
        } else if (strcmp(choice, "5") == 0) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("\033[0;31mInvalid choice. Please enter a valid option.\033[0m\n");
        }
    }

    // Free allocated memory
    free(rootDirectory);

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
    if (!newDirectory) {
        printf("New directory wasn't created!\n");
        return NULL;
    }
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
        Position current = parent->subDirectories;
        while (parent != NULL) {
            while (current != NULL) {
                
            }
        }
        /*while (parent != NULL) {
            if (parent->subDirectories == currentDirectory) {
                return parent;
            }
            parent = parent->next;
        }
        printf("Error: Parent directory not found.\n");
        return currentDirectory;*/
        /*
        * // Find the parent directory by checking the subdirectories
    Position parent = root;
    while (parent != NULL && parent->subDirectories != currentDirectory &&
           parent->subDirectories != NULL) {
        parent = parent->subDirectories->next;
    }

    return parent;
        */

    }
    else {
        printf("Already in the root directory.\n");
        return currentDirectory;
    }
}

void listDirectoryContents(Position currentDirectory) {
    printf("\033[0;32mContents of directory '%s':\033[0m\n", currentDirectory->name);
    Position subdirectory = currentDirectory->subDirectories;
    while (subdirectory != NULL) {
        printf("\033[0;32m - %s\033[0m\n", subdirectory->name);
        subdirectory = subdirectory->next;
    }
    if (currentDirectory->subDirectories == NULL) {
        printf("\033[0;32m   (empty)\033[0m\n");
    }
}
