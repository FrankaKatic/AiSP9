/* 9. Napisati program koji iz datoteke studenti.txt èita popis studenata na nekom predmetu i njihov ID,
a zatim m izgenerirati sluèajnu ocjenu u ospegu od  1 do 5.
Izgraditi vezanu listu na naèin da su studenti sortirani prema ocjenama, a zatim po prezimenima. ispisati vezanu listu.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct _student;
typedef struct _student student;
typedef student* position;

struct _student {
    char maticnibroj[20];
    char prezime[20];
    char ime[20];
    int ocjena;
    position next;
};

int IspisListe(position head);
int CitajDat(position head);
int SpremanjeUListu(position head, char prezime[20], char ime[20], char maticnibroj[20], int ocjena);
int GenerirajBroj();

int main()
{
	srand((unsigned int)(time));

	student head;
	head.next = NULL;
	int result;

	result = CitajDat(&head);

	result = IspisListe(&head);


	return 0;
}





int CitajDat(position head)
{
	char buffer[1024] = "\0";
	char ime[20] = "\0";
	char prezime[20] = "\0";
	char maticnibroj[20] = "\0";
	int ocjena;
	int result = 0;

	FILE* file;
	file = fopen("studenti.txt", "r");
	if (file == NULL)
	{
		printf("nije se otovrila");
		return -1;

	}
	while (!feof(file))
	{
		strcpy(buffer, "\0");
		strcpy(ime, "\0");
		strcpy(prezime, "\0");
		strcpy(maticnibroj, "\0");
		ocjena = 0;

		fgets(buffer, 1024 - 1, file);
		if (strlen(buffer) > 1)
		{
			sscanf(buffer, "%s %s %s", maticnibroj, prezime, ime);
			ocjena = GenerirajBroj();
		}
		result = SpremanjeUListu(head, prezime, ime, maticnibroj, ocjena);
		if (result == -1)
		{
			fclose(file);
			return -1;
		}
	}
	fclose(file);
	return 0;
}

int SpremanjeUListu(position head, char prezime[20], char ime[20], char maticnibroj[20], int ocjena)
{
	position temp;
	temp = (position)malloc(sizeof(student));
	int f = 0;
	if (temp == NULL)
	{
		printf("nije se alociralo");
		return -1;
	}
	strcpy(temp->prezime, prezime);
	strcpy(temp->ime, ime);
	strcpy(temp->maticnibroj, maticnibroj);
	temp->ocjena = ocjena;

	while (head->next != NULL && f == 0)
	{
		if (head->next->ocjena > temp->ocjena)
		{
			f = 1;
		}
		else if (head->next->ocjena == temp->ocjena)
		{
			if (strcmp(head->next->prezime, temp->prezime) > 0)
			{
				f = 1;
			}
			else
			{
				head = head->next;
			}
		}
		else
		{
			head = head->next;
		}
	}

	temp->next = head->next;
	head->next = temp;
	return 0;
}


int GenerirajBroj()
{
	int x;
	x = rand() % (5 - 1 + 1) + 1;
	return x;
}
int IspisListe(position head)
{
	head = head->next;
	while (head != NULL)
	{
		printf("%s %s %s \t%d \n", head->maticnibroj, head->prezime, head->ime, head->ocjena);
		head = head->next;
	}
	return 0;
}