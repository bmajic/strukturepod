#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OPENING_FILE -1
#define BUFFER_SIZE 1024

typedef struct {
	char ime[50];
	char prezime[50];
	int bod;

}student;

int count_rows(char* filename);

int main()
{
	FILE*fp = NULL;
	fp = fopen("datoteka.txt", "r");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila");
		return ERROR_OPENING_FILE;
	}

	return 0;
}


int count_rows(char* filename)
{

	char buffer[BUFFER_SIZE];
	int count = 0;

	FILE*fp = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error in files opening");
		return ERROR_OPENING_FILE;
	}

	while (!feof(fp))
	{
		fgets(buffer, BUFFER_SIZE, fp);
		++count;
	}
	fclose(fp);
	return count;
}