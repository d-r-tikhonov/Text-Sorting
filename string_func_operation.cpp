#include <stdlib.h>
#include <stdio.h>

#include "string_func_operation.h"



size_t getlineFile(char** string, FILE* stream)
{
	char incomingSymbol = 0;
	unsigned counterMass = 0;

	if (stream == nullptr || string == nullptr)
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
	int nlines = 0;
	int len = 0;
	char** string = (char**) calloc(1, sizeof(char));

	while (len = getlineFile(string, stream) > 0)
	{
			(*(p + nlines)).lineptr   = *string;
			(*(p + nlines)).countSymb = len;
			nlines++;
	}

	return nlines;
}


int cmpFromBegin (struct paramStr *p, int adressFirstStr, int adressSecondStr)
{
	const char* firstLinePtr  = (*(p + adressFirstStr )).lineptr; 
	const char* secondLinePtr = (*(p + adressSecondStr)).lineptr;

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

int cmpFromEnd (struct paramStr *p, int adressFirstStr, int adressSecondStr)
{
	const char* firstLinePtr  = (*(p + adressFirstStr )).lineptr; 
	const char* secondLinePtr = (*(p + adressSecondStr)).lineptr;

	int i = (*(p + adressFirstStr )).countSymb;
	int j = (*(p + adressSecondStr)).countSymb;

	for (; i >= 0; i--)
	{
		for (; j >= 0; j--)
		{
			if (firstLinePtr[i] != secondLinePtr[j] || firstLinePtr[i] == '\n')
			{
				break;
			}
		}
	}

	return firstLinePtr[i] - secondLinePtr[j];
}


void swap (struct paramStr *p, int adressFirstString, int adressSecondString)
{
	char* temp = (*(p + adressSecondString)).lineptr;

	(*(p + adressSecondString)).lineptr  = (*(p + adressFirstString)).lineptr;
	(*(p + adressFirstString)). lineptr  = temp;
}


void qsort (struct paramStr *p, int nlines, int (*cmpFunc) (struct paramStr *p, int, int))
{
	for (int i = 0; i < nlines - 1; i++)
	{
		for (int j = 0; j < nlines - 1; j++)
		{
			if ((*cmpFunc) (p, j, j+1) > 0)
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