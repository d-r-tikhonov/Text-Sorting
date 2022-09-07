#ifndef __STRING_FUNC_OPERATION__
#define __STRING_FUNC_OPERATION__


size_t getlineFile(char **string, FILE *stream);
int isEqString(char* firstLinePtr, char* secondLinePtr);
void swap(char* lineptr[], int adressFirstString, int adressSecondString);
void qsort(char* lineptr[], int nlines);


#endif