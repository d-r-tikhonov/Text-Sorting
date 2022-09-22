#ifndef __TEXT_PROCESSING__
#define __TEXT_PROCESSING__

struct lines
{
    char* start = 0;
    char* end   = 0;
};

char* cpyFileToBuffer (FILE* stream);

size_t nLinesFile (char* buffer, char separator);

struct lines* readLines (FILE* stream);

int cmpFromBegin (const struct lines* firstString, const struct lines* secondString);

int cmpFromEnd (const struct lines* firstString, const lines* secondString);

void swap (void* ptr, size_t firstAdress, size_t secondAdress);

void bubbleSort (void* ptr, size_t nLines, size_t size, int (*cmpFunc)(const void*, const void*));

void writeLines (const struct lines* string, size_t nLines, FILE* stream);

void freeLines (struct lines* string);

void clearBuffer (char* buffer);

void memClr(struct lines *string, size_t nLines, char* buffer);

#endif