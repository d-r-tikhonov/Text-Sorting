#include <stdio.h>

#include "read_and_write_func.h"
#include "string_func_operation.h"

const unsigned MaxLines = 5000;

///////////////////////////////////////////////////////////////
/// @param nlines Количество прочитанных строк
///////////////////////////////////////////////////////////////
int main()
{
	char *lineptr[MaxLines];
	int nlines = 0;

	FILE * ptrFile = fopen ("inputFile.txt", "r");

	if (ptrFile == NULL) 
  		printf("Error opening files!\n");
   	else
   	{
   		nlines = readlines(lineptr, ptrFile);

		qsort(lineptr, nlines - 1);

		writelines(lineptr, nlines - 1);

		fclose(ptrFile);

		return 0;
	}
}