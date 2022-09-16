#include <stdlib.h>
#include <stdio.h>

#include "string_func_operation.h"



size_t getlineFile(char** string, FILE* stream)
{
	char incomingSymbol = 0;
	unsigned counterMass = 0;

	if (stream == nullptr)
	{
		printf("Error: file or incoming string not found!");

		return -1;
	}
	
	*string = (char*) calloc(1, sizeof(char));

	while ((incomingSymbol = getc(stream)) != '\n' && incomingSymbol != EOF)
	{

		(*string)[counterMass] = incomingSymbol; 

		counterMass++;

		*string = (char*) realloc(*string, (counterMass + 1) * sizeof(char));
	}

	if (incomingSymbol == '\n' && counterMass == 0)
		counterMass = 1;

	(*string)[counterMass] = '\0';

	return counterMass;
}


int readlines(struct paramStr *p, FILE *stream)
{
	int len = 0;
	int nlines = 0;
	char** string = (char**) calloc(1, sizeof(char));

	while ((len = getlineFile(string, stream)) > 0)
	{
			(*string)[len] = '\0';

			(*(p + nlines)).lineptr = *string;
			nlines++;
	}

	return nlines;
}


int cmpFromBegin (const char* firstLinePtr, const char* secondLinePtr)
{
	int i = 0;

	for (i = 0; firstLinePtr[i] == secondLinePtr[i]; i++)
	{
		if (firstLinePtr[i] == '\n')
		{
			break;
		}
	}

	return firstLinePtr[i] - secondLinePtr[i];
}


void swap (struct paramStr *p, int adressFirstString, int adressSecondString)
{
	char* temp = (*(p + adressSecondString)).lineptr;

	(*(p + adressSecondString)).lineptr = (*(p + adressFirstString)).lineptr;
	(*(p + adressFirstString)).lineptr = temp;
}


void qsort (struct paramStr *p, int nlines, int (*cmpFunc) (const char*, const char*))
{
	for (int i = 0; i < nlines - 1; i++)
	{
		for (int j = 0; j < nlines - 1; j++)
		{
			if ((*cmpFunc) ((*(p+j)).lineptr, (*(p+j+1)).lineptr) > 0)
			{
				swap(p, j + 1, j);
			}
		}
	}
}


void writelines(struct paramStr *p, int nlines)
{	
	for (int i = 0; i <= nlines; i++)
		printf("%s\n", (*(p+i)).lineptr);
}	
	

void clearBuffer(struct paramStr *p, int nlines)
{				
	for (int i = 0; i <= nlines; i++)
	{
		free((*(p + i)).lineptr);
	}
}