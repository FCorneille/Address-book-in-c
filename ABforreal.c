#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 16
#define MAX_AGE 3
#define MAX_NUM 12
#define MAX_PER 150

typedef struct {
	char name[MAX_LEN];
	char sirName[MAX_LEN];
	int age;
	char phoneNum[MAX_NUM];
} Contact;

typedef struct {
	Contact contacts[MAX_PER];
} Book;

int initialize(Book *book);
void showMenu();
void addContact(Book *book, int count);
void listContacts(Book *book, int count);
void writeBook(Book *book, int count);
void deleteContact(Book *book, int count);
void searchContact(Book *book, int count);

int main()
{
	int count;	
	Book *book = malloc(sizeof(Book));
	
	count = initialize(book);
	int i = 0;
	int ch = 0;

	printf("%d\n", count);

	while (ch != 'q')
	{
		showMenu();
		ch = getchar();
		getchar();
		switch (ch)
		{
			case '1':
				addContact(book, count);
				count++;
				break;
			case '2':
				deleteContact(book, count);
				count--;
				break;
			case '3':
				listContacts(book, count);
				break;
			case '4':
				searchContact(book, count);
				break;
			case 'q':
				break;
			default:
				printf("Pick a another option. \n");
				break;
		}
		printf("\n");
	}

	writeBook(book, count);
	free(book);
	
	return 0;
}

int initialize(Book* book)
{
	int c = 0;
	FILE *fp, *hm;
	fp = fopen("contacts.bin", "r");
	if (fp == NULL)
	{
		perror("File doesn't exist, but I've got a trick!\n");
		fp = fopen("contacts.bin", "w");
		fclose(fp);
		fp = fopen("contacts.bin", "r");
		if (fp == NULL)
			perror("Couldn't open file contacts.bin.\n");
	}
	hm = fopen("howmany.bin", "r");
	if (hm == NULL)
	{
		perror("File doesn't exist, but I've got another trick!\n");
		hm = fopen("howmany.bin", "w");
		fwrite(&c, sizeof(int), 1, hm);
		fclose(hm);
		hm = fopen("howmany.bin", "r");
		if (hm == NULL)
			perror("Couldn't open file howmany.bin\n");
	}
	fread(&c, sizeof(int), 1, hm);
	fread(book, sizeof(Book), 1, fp);

	fclose(fp);
	fclose(hm);

	return c;
}

void showMenu()
{
	printf("Menu options are: \n");
	printf("1. Add contact \n");
	printf("2. Delete contact \n");
	printf("3. List contacts \n");
	printf("4. Search contact \n");
	printf("q. Quit \n");
}

void addContact(Book *book, int count)
{
	char ageStr[MAX_AGE + 1];

	printf("Name: \n");
	fgets(book->contacts[count].name, MAX_LEN, stdin);
	printf("Sirname: \n");
	fgets(book->contacts[count].sirName, MAX_LEN, stdin);
	printf("Age: \n");
	fgets(ageStr, MAX_AGE + 1, stdin);
	book->contacts[count].age = atoi(ageStr);
	printf("Phone number: \n");
	getchar();
	fgets(book->contacts[count].phoneNum, MAX_NUM, stdin);
}

void listContacts(Book *book, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		printf("%s", book->contacts[i].name);
		printf("%s", book->contacts[i].sirName);
		printf("%d\n", book->contacts[i].age);
		printf("%s", book->contacts[i].phoneNum);
		printf("\n");
	}
}

void writeBook(Book *book, int count)
{
	FILE *fp, *hm;
	fp = fopen("contacts.bin", "w");
	hm = fopen("howmany.bin", "w");
	fwrite(book, sizeof(Book), 1, fp);
	fwrite(&count, sizeof(int), 1, hm);

	fclose(fp);
	fclose(hm);
}

void deleteContact(Book *book, int count)
{
	int i;
	int tmp;
	char buf[MAX_LEN];

	printf("Name: \n");
	fgets(buf, MAX_LEN, stdin);
	for (i = 0; i < count; i++) 
	{
		if (strcmp(book->contacts[i].name, buf) == 0 || strcmp(book->contacts[i].sirName, buf) == 0) 
		{
			for (tmp = i; tmp < count; tmp++) 
			{
				book->contacts[tmp] = book->contacts[tmp+1];
			}
		}
	}
}

void searchContact(Book *book, int count)
{
	int i;
	char buf[MAX_LEN];

	printf("Name \n");
	fgets(buf, MAX_LEN, stdin);
	for (i = 0; i < count; i++)
	{
		if (strcmp(buf, book->contacts[i].name) == 0 || strcmp(buf, book->contacts[i].sirName) == 0)
		{
			printf("%s \n", book->contacts[i].name);
			printf("%s \n", book->contacts[i].sirName);
			printf("%d \n", book->contacts[i].age);
			printf("%d \n", book->contacts[i].phoneNum);
			printf("\n");
		}
	}
}
