#define NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "text_processing.h"

static long fileSize (FILE* stream);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static long fileSize (FILE* stream) 
{
	assert (stream != nullptr);

	long curPos = ftell(stream);

	fseek (stream, 0L, SEEK_END);
	long size = ftell (stream);
	if (size == -1)
		return -1;

	fseek(stream, curPos, SEEK_SET);

	return size;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char* cpyFileToBuffer (FILE* stream) 
{
	assert (stream != nullptr);

	size_t size = fileSize (stream);

	char* buffer = (char*) calloc (size + 1, sizeof(char));
	assert (buffer != nullptr);

	long readSuccess = fread (buffer, sizeof(char), size, stream);		
	buffer[readSuccess] = '\0';

	assert (feof (stream));

	return buffer;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t nLinesFile (char* buffer)
{
	assert (buffer != 0);

	size_t nLines = 0;
	char* ptrN = buffer;

	while ((ptrN = strchr (ptrN, '\n')) != nullptr)
	{
		nLines++;
		ptrN++;
	}

	return nLines;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

size_t readLines (char* buffer, struct lines* string)
{
	char* ptrStart = buffer;
	char* ptrEnd   = buffer;

	size_t nLines = 0;
	while ((ptrEnd = strchr (ptrStart, '\n')) != nullptr)
	{
		string[nLines].start = ptrStart;
		string[nLines].end 	 = ptrEnd;
		
		ptrStart = ptrEnd + 1;
		nLines++;
	}

	return nLines;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int cmpFromBegin (const struct lines* firstString, const struct lines* secondString) 
{
	assert(firstString != secondString);

	const char* firstStr  =  firstString->start;
    const char* secondStr = secondString->start;

    while (*firstStr == *secondStr) 
    {
        if (*firstStr == *(firstString->end) || *secondStr == *(secondString->end))
            break;

         firstStr++;
        secondStr++;
    }

    return *firstStr - *secondStr;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int cmpFromEnd (const struct lines* firstString, const struct lines* secondString) 
{
	assert(firstString != secondString);

    const char* firstStr  =  firstString->end;
    const char* secondStr = secondString->end;

    while (*firstStr == *secondStr) 
    {
      	if (*firstStr == *(firstString->start))
        	break;

         firstStr--;
        secondStr--;
    }

    return *firstStr - *secondStr;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void swap (void* ptr, size_t firstAdress, size_t secondAdress)///void* void* size
{
	assert(firstAdress != secondAdress);

	struct lines* string = (struct lines* ) ptr;

	struct lines temp = string[firstAdress];
	string[firstAdress] = string[secondAdress];
	string[secondAdress] = temp;

	assert(firstAdress != secondAdress);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void bubbleSort (void *ptr, size_t nLines, size_t size, int (*cmpFunc)(const void *, const void *))
{
	char *data = (char* ) ptr;
	assert(data == (char * ) ptr);

	for (size_t i = 0; i < nLines; i++)
	{		
		for (size_t j = 0; j < nLines - 1; j++)
		{
			if ((*cmpFunc) (data + size * j, data + size * (j + 1)) > 0)
			{
				swap (data, j, j + 1);
			}
		}
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void writeLines (const struct lines* string, size_t nLines, FILE* stream)
{	
	// fwrite("Sorted rows\n", sizeof(char), sizeof("Sorted rows\n")/sizeof(char), stream);

	for (size_t i = 0; i < nLines; i++)
	{
		fwrite (string[i].start, sizeof(char), (string[i].end - string[i].start)/sizeof(char) + 1, stream);
	}

	// fwrite("~~\n", sizeof(char), sizeof("~~\n")/sizeof(char), stream);
}	
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void freeLines (struct lines* string, size_t nLines)
{				
	for (size_t i = 0; i < nLines; i++)
	{
		free (string);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void clearBuffer (char* buffer)
{
	if (buffer != nullptr)
		free (buffer);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void memClr (struct lines* string, size_t nLines, char* buffer)
{
	clearBuffer (buffer);
	freeLines (string, nLines);
}