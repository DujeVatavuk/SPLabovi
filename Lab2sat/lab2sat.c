#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define NO_PERSON_FOUND (NULL)
#define EMPTY_LIST (-1)
#define NO_PERSON_FOUND_FOR_DELETE (-2)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
} Person;

int menu(Position head);
Position createPerson();
Position findLast(Position head);
char* enterSurname();
int printPerson(Position person);
int addToFrontOfTheList(Position head);
int addToEndOfTheList(Position head);
int printList(Position firstElement);
Position findPerson(Position firstElement);
int deletePerson(Position head);

int main() {
	Person head = { .next = NULL, .name = {0},
				.surname = {0}, .birthYear = 0 };
	menu(&head);

	return EXIT_SUCCESS;
}

int menu(Position head) {
	char choice = '\0';
	Position person = NULL;
	while (1) {
		printf("Enter:  A(Add to the front of the list)\n\tE(Add to the end of list)\n\tP(Print list)\n\tS(Search)\n\tD(Delete)\n\tF(Add after item)\n\tB(Add before item)\n\tO(Sort)\n\tW(Write to file)\n\tR(Read from file)\n\tX(Exit)\n");
		scanf(" %c", &choice);
		switch (choice) {
			// add item to the front of the list
			case 'A':
			case 'a':
				addToFrontOfTheList(head);
				continue;
			// add item to the end of the list
			case 'E':
			case 'e':
				addToEndOfTheList(head);
				continue;
			// print list items
			case 'P':
			case 'p':
				printList(head->next);
				continue;
			// search item in list by surname
			case 'S':
			case 's':
				person = findPerson(head->next);
				person ? printPerson(person) : printf("Can't find person with that surname!\n");
				continue;
			// delete a item from list
			case 'D':
			case 'd':
				switch (deletePerson(head)) {
					case EXIT_SUCCESS:
						printf("Deleted!\n");
						break;
					case EMPTY_LIST:
						printf("List is empty!\n");
						break;
					case NO_PERSON_FOUND_FOR_DELETE:
						printf("Can't find person with that surname!\n");
						break;
					default:
						break;
				}
				continue;
			// add item to the list after some specified item
			case 'F':
			case 'f':
				/*person = findPerson(head->next);
				person ? printPerson(person) : printf("Can't find person with that surname!\n");*/
				continue;
			// add item to the list before some specified item
			case 'B':
			case 'b':
				/*person = findPerson(head->next);
				person ? printPerson(person) : printf("Can't find person with that surname!\n");*/
				continue;
			// sort items in list by surname
			case 'O':
			case 'o':
				/*person = findPerson(head->next);
				person ? printPerson(person) : printf("Can't find person with that surname!\n");*/
				continue;
			// write items in list to the file
			case 'W':
			case 'w':
			/*	person = findPerson(head->next);
				person ? printPerson(person) : printf("Can't find person with that surname!\n");*/
				continue;
			// read items in list from the file
			case 'R':
			case 'r':
			/*	person = findPerson(head->next);
				person ? printPerson(person) : printf("Can't find person with that surname!\n");*/
				continue;
			// exit program
			case 'X':
			case 'x':
				break;
			default:
				printf("Wrong letter!\n");
				continue;
		}
		break;
	}
	return EXIT_SUCCESS;
}

int addToFrontOfTheList(Position head) {
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson) {
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int addToEndOfTheList(Position head) {
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = createPerson();

	if (newPerson) {
		last = findLast(head);
		newPerson->next = last->next;
		last->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int printList(Position firstElement) {
	Position current = firstElement;
	if (!firstElement) {
		printf("Empty list!\n");
	}
	while (current) {
		printPerson(current);
		current = current->next;
	}

	return EXIT_SUCCESS;
}

Position findPerson(Position firstElement)
{
	Position current = firstElement;
	if (!firstElement) {
		printf("Empty list!\n");
		return NO_PERSON_FOUND;
	}
	char surname[MAX_LENGTH] = { 0 };
	strcpy(surname, enterSurname());
	do {
		if (strcmp(current->surname, surname) == 0) {
			return current;
		}
		else {
			current = current->next;
		}
	} while (current->next != NULL);

	return NO_PERSON_FOUND;
}

int deletePerson(Position head)
{
	Position current = head;
	char surname[MAX_LENGTH] = { 0 };
	strcpy(surname, enterSurname());
	if (head->next) {
		Position previous = NULL;

		while (current->next && strcmp(current->surname, surname) != 0) {
			previous = current;
			current = current->next;
		}
		//we have to have check for "previous" so intellisense doesn't show warning
		if (previous && previous->next && strcmp(current->surname, surname) == 0) {
			printPerson(current);
			previous->next = current->next;
			free(current);
		}
		else {
			return NO_PERSON_FOUND_FOR_DELETE;
		}
	}
	else {
		return EMPTY_LIST;
	}

	return EXIT_SUCCESS;
}

Position createPerson() {
	Position newPerson = NULL;
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int birthYear = 0;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Can't allocate memory!\n");
		return NULL;
	}

	printf("Enter name:\n");
	scanf(" %s", name);
	printf("Enter surname:\n");
	scanf(" %s", surname);
	printf("Enter birth year:\n");
	scanf(" %d", &birthYear);


	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	return newPerson;
}

Position findLast(Position head)
{
	Position current = head;

	while (current->next) {
		current = current->next;
	}

	return current;
}

char* enterSurname()
{
	char surname[MAX_LENGTH] = { 0 };
	printf("Enter surname of the wanted person:\n");
	scanf(" %s", surname);

	return surname;
}

int printPerson(Position person) {
	printf("Name: %s\t Surname: %s\t Birth year: %d\t\n", person->name, person->surname, person->birthYear);
	return EXIT_SUCCESS;
}