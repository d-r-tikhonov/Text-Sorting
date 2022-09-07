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

	while( (incomingSymbol = getc(stream)) != '\n' && incomingSymbol != EOF )
	{
		(*string)[counterMass] = incomingSymbol; 

		counterMass++;

		*string = (char*) realloc(*string, (counterMass + 1)* sizeof(char));
	}

	(*string)[counterMass] = '\0';

	return counterMass;
}

int isEqString(char* firstLinePtr, char* secondLinePtr)
{
	int i = 0;

	for (i = 0; firstLinePtr[i] == secondLinePtr[i]; i++)
	{
		if (firstLinePtr[i] == '\n')
		{
			return 0;
		}
	}

	return firstLinePtr[i] - secondLinePtr[i];
}

void swap(char* lineptr[], int adressFirstString, int adressSecondString)
{
	char* temp = lineptr[adressSecondString];

	lineptr[adressSecondString] = lineptr[adressFirstString];
	lineptr[adressFirstString] = temp;
}

void qsort(char* lineptr[], int nlines)
{
	for (int i = 0; i < nlines - 1; i++)
	{
		for (int j = 0; j < nlines - 1; j++)
		{
			if (isEqString(lineptr[j], lineptr[j + 1]) > 0)
			{
				swap(lineptr, j + 1, j);
			}
		}
	}
}