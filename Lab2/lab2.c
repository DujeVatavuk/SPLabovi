//dodaj zadatak ode u komentar

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
} Person;

int AppendList(Position head);
int AddToEndOfList(Position head);
int PrintList(Position first);
int FindPerson(Position head);
int DeletePerson(Position head);
Position CreatePerson();
Position FindLast(Position head);
int PrintPerson(Position person);
int Menu(Position head);
char* WishedSurname();

int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0},
				.surname = {0}, .birthYear = 0 };
	Menu(&Head);


	return EXIT_SUCCESS;
}

Position CreatePerson()
{
	Position newPerson = NULL;
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int birthYear = 0;

	newPerson = (Position)malloc(sizeof(Person));
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


	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	return newPerson;
}

int AppendList(Position head)
{
	Position newPerson = NULL;

	newPerson = CreatePerson();

	if (newPerson)
	{
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	while (head->next != NULL)
	{
		head = head->next;
	}

	return head;
}

int AddToEndOfList(Position head)
{
	Position newPerson = NULL;

	newPerson = CreatePerson();

	if (newPerson)
	{
		head = FindLast(head);
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	if (!first)
	{
		perror("Empty list!\n");
	}
	for (; first != NULL; first = first->next)
	{
		printf("Name: %s\t Surname: %s\t Birth year: %d\t\n", first->name, first->surname, first->birthYear);
	}

	return EXIT_SUCCESS;
}

int FindPerson(Position head)
{
	if (head->next)
	{
		while (head->next && strcmp(head->next->surname, WishedSurname()) != 0)
		{
			head = head->next;
		}
		if (head->next)
		{
			PrintPerson(head->next);
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
int DeletePerson(Position head)
{
	if (head->next)
	{
		Position previous = NULL;

		while (head->next && strcmp(head->surname, WishedSurname()) != 0)
		{
			previous = head;
			head = head->next;
		}
		if (previous->next && strcmp(head->surname, WishedSurname()) == 0)
		{
			PrintPerson(head);
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

int PrintPerson(Position person)
{
	printf("Name: %s, surname: %s, birth year: %d, adress: %p\n",
		person->name, person->surname, person->birthYear, person);

	return EXIT_SUCCESS;
}

int Menu(Position Head)
{
	char choice = '\0';
	while (1) {
		printf("Enter A(Append list), E(Put at the end of list), P(Print list), S(Search), D(Delete), X(Exit)\n");
		scanf(" %c", &choice);
		if (tolower(choice) == 'a')
			AppendList(Head);
		else if (tolower(choice) == 'e')
			AddToEndOfList(Head);
		else if (tolower(choice) == 'p')
			PrintList(Head->next);
		else if (tolower(choice) == 's')
		{
			while (FindPerson(Head) == -1)
			{
				FindPerson(Head);
			}
		}
		else if (tolower(choice) == 'd')
		{
			while (DeletePerson(Head) == -1)
			{
				DeletePerson(Head);
			}
		}
		else if (tolower(choice) == 'x')
			break;
		else
			perror("Wrong letter!\n");
	}
	return EXIT_SUCCESS;
}

char* WishedSurname()
{
	char surname[MAX_LENGTH] = { 0 };
	printf("Enter surname of the wanted person:\n");
	scanf(" %s", surname);

	return surname;
}
