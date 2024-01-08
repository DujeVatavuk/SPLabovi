#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define MAX_LINE (1024)
#define FILE_NOT_OPEN (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)

struct _town;
typedef struct _town* TownPosition;
typedef struct _town
{
	char name[MAX_LENGTH];
	int population;
	TownPosition next;
	TownPosition left;
	TownPosition right;
} Town;

struct _country;
typedef struct _country* CountryPosition;
typedef struct _country
{
	char name[MAX_LENGTH];
	CountryPosition next;
	CountryPosition left;
	CountryPosition right;
	TownPosition townTreeRoot;
	Town townListHead;
} Country;

CountryPosition readAndFillCountries(CountryPosition countryHeadList, CountryPosition countryHeadTree);
int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries);
CountryPosition createNewCountry(char* countryName);
TownPosition createNewTown(char* townName, int townPopulation);
int insertSortedNewTownList(TownPosition townHead, TownPosition newTown);
int insertTownAfter(TownPosition townCurrent, TownPosition newTown);
TownPosition insertNewTownTree(TownPosition root, TownPosition newTownTree);
int insertSortedNewCountryList(CountryPosition townHead, CountryPosition newCountry);
int insertCountryAfter(CountryPosition countryCurrent, CountryPosition newCountry);
CountryPosition insertNewCountryTree(CountryPosition root, CountryPosition newCountry);
int printCountryList(CountryPosition countryHeadList);
int printCountryTree(CountryPosition countryHeadTree);
int printTownList(TownPosition townHeadList);
int printTownTree(TownPosition townHeadTree);

int main() {
	Country countryHeadList = {
		.name = { 0 },
		.next = NULL,
		.left = NULL,
		.right = NULL,
		.townTreeRoot = NULL,
		.townListHead = {
			.name = { 0 },
			.population = 0,
			.next = NULL,
			.left = NULL,
			.right = NULL,
		}
	};

	CountryPosition countryHeadTree = NULL;

	countryHeadTree = readAndFillCountries(&countryHeadList, countryHeadTree);
	printCountryList(&countryHeadList);
	printf("\n\n\n\n");
	printCountryTree(countryHeadTree);

	//articleInBetweenDates("Jabuka", "2023-11-10", "2023-11-17", receiptHead.next);

	return EXIT_SUCCESS;
}

CountryPosition readAndFillCountries(CountryPosition countryHeadList, CountryPosition countryHeadTree) {
	FILE* filePointer = NULL;
	char countryName[MAX_LINE] = { 0 };
	char countryFile[MAX_LINE] = { 0 };
	char nullString[MAX_LINE] = { 0 };
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	CountryPosition countries[] = { NULL, NULL };

	filePointer = fopen("drzave.txt", "r");
	if (!filePointer) {
		printf("\033[31mCan't open file!\033[0m\n");
		return FILE_NOT_OPEN;
	}

	while (!feof(filePointer)) {
		fscanf(filePointer, " %s %s", countryName, countryFile);
		createNewCountryFromBuffer(countryName, countryFile, countries);
		newCountryList = countries[0];
		newCountryTree = countries[1];
		insertSortedNewCountryList(countryHeadList, newCountryList);
		countryHeadTree = insertNewCountryTree(countryHeadTree, newCountryTree);
		strcpy(countryName, nullString);// provjeri treba li
		strcpy(countryFile, nullString);// provjeri treba li
	}

	fclose(filePointer);

	return countryHeadTree;
}

int createNewCountryFromBuffer(char* countryName, char* countryFile, CountryPosition* countries) {
	char countryLocation[MAX_LENGTH] = { 0 };
	FILE* countryFilePointer = NULL;
	CountryPosition newCountryList = NULL;
	CountryPosition newCountryTree = NULL;
	TownPosition newTownList = NULL;
	TownPosition newTownTree = NULL;
	char townName[MAX_LENGTH] = { 0 };
	int townPopulation = 0;

	strcpy(countryLocation, countryFile);

	countryFilePointer = fopen(countryLocation, "r");
	if (!countryFilePointer) {
		printf("\033[31mCan't open file!\033[0m\n");
		return FILE_NOT_OPEN;
	}

	newCountryList = createNewCountry(countryName);
	newCountryTree = createNewCountry(countryName);

	while (!feof(countryFilePointer)) {
		fscanf(countryFilePointer, " %s %d", townName, &townPopulation);
		newTownList = createNewTown(townName, townPopulation);
		newTownTree = createNewTown(townName, townPopulation);
		insertSortedNewTownList(&newCountryTree->townListHead, newTownList);
		newCountryList->townTreeRoot = insertNewTownTree(newCountryList->townTreeRoot, newTownTree);
		newTownList = NULL;// provjeri treba li
	}
	countries[0] = newCountryList;
	countries[1] = newCountryTree;

	fclose(countryFilePointer);

	return EXIT_SUCCESS;
}

CountryPosition createNewCountry(char* countryName) {
	CountryPosition country = NULL;
	country = (CountryPosition)malloc(sizeof(Country));
	if (!country) {
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}


	strcpy(country->name, countryName);
	country->next = NULL;
	country->left = NULL;
	country->right = NULL;
	country->townTreeRoot = NULL;
	//strcpy(country->townHead.name, NULL);
	country->townListHead.population = 0;
	country->townListHead.next = NULL;
	country->townListHead.left = NULL;
	country->townListHead.right = NULL;

	return country;
}

TownPosition createNewTown(char* townName, int townPopulation) {
	TownPosition town = NULL;
	town = (TownPosition)malloc(sizeof(Town));
	if (!town) {
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	strcpy(town->name, townName);
	town->population = townPopulation;
	town->next = NULL;
	town->left = NULL;
	town->right = NULL;

	return town;
}

int insertSortedNewTownList(TownPosition townHead, TownPosition newTown) {
	TownPosition townCurrent = townHead;
	while (townCurrent->next != NULL && townCurrent->next->population > newTown->population) {
		townCurrent = townCurrent->next;
	}

	insertTownAfter(townCurrent, newTown);

	return EXIT_SUCCESS;
}

int insertTownAfter(TownPosition townCurrent, TownPosition newTown) {
	newTown->next = townCurrent->next;
	townCurrent->next = newTown;

	return EXIT_SUCCESS;
}

TownPosition insertNewTownTree(TownPosition townTreeRoot, TownPosition newTownTree) {
	if (townTreeRoot == NULL)
		return newTownTree;

	if (newTownTree->population > townTreeRoot->population)//dodaj provjeru po imenima naknadno...
		townTreeRoot->left = insertNewTownTree(townTreeRoot->left, newTownTree);
	else if (newTownTree->population <= townTreeRoot->population)
		townTreeRoot->right = insertNewTownTree(townTreeRoot->right, newTownTree);

	return townTreeRoot;
}

int insertSortedNewCountryList(CountryPosition townHead, CountryPosition newCountry) {
	CountryPosition countryCurrent = townHead;
	while (countryCurrent->next != NULL && strcmp(countryCurrent->next->name, newCountry->name) < 0) {
		countryCurrent = countryCurrent->next;
	}

	insertCountryAfter(countryCurrent, newCountry);

	return EXIT_SUCCESS;
}

int insertCountryAfter(CountryPosition countryCurrent, CountryPosition newCountry) {
	newCountry->next = countryCurrent->next;
	countryCurrent->next = newCountry;

	return EXIT_SUCCESS;
}

CountryPosition insertNewCountryTree(CountryPosition countryTreeRoot, CountryPosition newCountry) {
	if (countryTreeRoot == NULL)
		return newCountry;

	if (strcmp(countryTreeRoot->name, newCountry->name) > 0)
		countryTreeRoot->left = insertNewCountryTree(countryTreeRoot->left, newCountry);
	else if (strcmp(countryTreeRoot->name, newCountry->name) <= 0)
		countryTreeRoot->right = insertNewCountryTree(countryTreeRoot->right, newCountry);

	return countryTreeRoot;
}

int printCountryList(CountryPosition countryHeadList) {
	CountryPosition currentCountry = countryHeadList->next;
	while (currentCountry != NULL) {
		printf("\n%s", currentCountry->name);
		printTownTree(currentCountry->townTreeRoot);
		currentCountry = currentCountry->next;
	}
}

int printCountryTree(CountryPosition countryHeadTree) {
	if (countryHeadTree) {
		printCountryTree(countryHeadTree->left);
		printf("\n%s", countryHeadTree->name);
		printTownList(&countryHeadTree->townListHead);
		printCountryTree(countryHeadTree->right);
	}
	return EXIT_SUCCESS;
}

int printTownList(TownPosition townHeadList) {
	TownPosition currentTown = townHeadList->next;
	while (currentTown != NULL) {
		printf("\n\t%s %d", currentTown->name, currentTown->population);
		currentTown = currentTown->next;
	}
}

int printTownTree(TownPosition townHeadTree) {
	if (townHeadTree) {
		printTownTree(townHeadTree->left);
		printf("\n\t%s %d", townHeadTree->name, townHeadTree->population);
		printTownTree(townHeadTree->right);
	}
	return EXIT_SUCCESS;
}