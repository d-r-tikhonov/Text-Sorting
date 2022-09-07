#include <stdio.h>
#include <string.h>

#include "read_and_write_func.h"
#include "string_func_operation.h"


int readlines(char* lineptr[], FILE *stream)
{
	int len = 0;
	int nlines = 0;
	char** string;

	while ((len = getlineFile(string, stream)) > 0)
	{
		if (*string == NULL)
		{
			printf("Error! Adress of string in readlines(); not found!");
			return -1;
		}
		else
		{
			(*string)[len - 1] = '\0';   ///len-1?

			lineptr[nlines++] = *string;
		}
	}

	return nlines;
}


void writelines(char* lineptr[], int nlines)
{
	for(int i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

