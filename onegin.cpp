#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct fileLines
{
    char* lineStart;
    size_t lineLen;
};

struct Text
{
    char* buffer;
    size_t nChar;
    size_t nLines;

    fileLines* lines;
};

int textCtor (Text*, FILE* const);
int readFile (Text*, FILE* const);
long fileSize (FILE*);
int matchLines (Text*);
int countLines (char*, char, size_t*);
int TextDtor (Text*);
int printText (FILE*, fileLines*, size_t, int (*comparator) (const void*, const void*));
int comparator (const void*, const void*);
int bubbleSort (void*, size_t, size_t, int (*comparator) (const void*, const void*));
const char* skipLeftSymbols (const char*);

int main (int argc, const char* argv[])
{
    assert (argc == 3);

    FILE* source    = fopen (argv[1], "r");
    FILE* processed = fopen (argv[2], "w+");

    assert (source != nullptr && processed != nullptr);

    Text text = {};

    textCtor (&text, source);

    printText (processed, text.lines, text.nLines, comparator);

    TextDtor (&text);

    fclose (source);
    fclose (processed);

    return 0;
}

int textCtor (Text* text, FILE* const sourceFile)
{
    assert (text != nullptr && sourceFile != nullptr);

    readFile (text, sourceFile);

    matchLines (text);

    return 0;
}

int readFile (Text* text, FILE* const sourceFile)
{
    assert (text != nullptr && sourceFile != nullptr);

    text->nChar  = fileSize (sourceFile);
    text->buffer = (char*) calloc (text->nChar + 1, sizeof (char));

    fread (text->buffer, sizeof (char), text->nChar, sourceFile);

    return 0;
}

long fileSize (FILE* stream)
{
    assert (stream != nullptr);

    long currentPos = ftell (stream);
    assert (currentPos != -1);

    fseek (stream, 0L, SEEK_END);

    long size = ftell (stream);
    assert (size != -1);

    fseek (stream, currentPos, SEEK_SET);

    return size;
}

int matchLines (Text* text)
{
    size_t line      = 0;
    size_t lineStart = 0;

    countLines (text->buffer, '\n', &(text->nLines));

    text->lines = (fileLines*) calloc (text->nLines, sizeof (fileLines));

    for (size_t index = 0; index < text->nChar; ++index)
    {
        if (*(text->buffer + index) == '\n')
        {
            *(text->buffer + index) = '\0';

            (text->lines + line)->lineStart = text->buffer + lineStart;
            (text->lines + line)->lineLen   = index - lineStart;

            lineStart = index + 1;
            line++;
        }
    }

    return 0;
}

int countLines (char* buffer, char separator, size_t* count)
{
    size_t index = 0;

    while (*(buffer + index))
    {
        if (*(buffer + index) == separator)
        {
            (*count)++;
        }

        index++;
    }

    return 0;
}

int TextDtor (Text* text)
{
    assert (text != nullptr);

    free (text->buffer);
    free (text->lines);

    return 0;
}

int printText (FILE* processed, fileLines* data, size_t nLines, int (*comparator) (const void*, const void*))
{
    bubbleSort (data, nLines, sizeof (fileLines), comparator);

    for (size_t index = 0; index < nLines; ++index)
    {
        if (*(data[index].lineStart) != '\0')
        {
            fputs (data[index].lineStart, processed);
            fputs ("\n", processed);
        }
    }

    return 0;
} 

int bubbleSort (void *ptr, size_t count, size_t size, int (*comparator) (const void*, const void*)) 
{
    size_t index = 0;
    bool isSorted = 1;

    void* prev = nullptr;
    void* cur  = nullptr;
    void* temp = calloc (size, sizeof (char));
  
    do 
    {
        isSorted = 1;
        index = 1;
        prev = (char*) ptr;
        cur  = (char*) prev + size;

        while (index < count) 
        {
            if (comparator (prev, cur) > 0) 
            {
                memcpy (temp, prev, size);
                memcpy (prev, cur, size);
                memcpy (cur, temp, size);

                isSorted = 0;
            }

            index++;

            prev = (char*) prev + size;
            cur  = (char*) cur  + size;
        }
    } while (!isSorted);

    free (temp);

    return 0;
}

int comparator (const void* ptr1, const void* ptr2)
{
    assert (ptr1 != nullptr && ptr2 != nullptr);
    assert (ptr1 != ptr2);

    const char* str1 = ((const fileLines*) ptr1)->lineStart;
    const char* str2 = ((const fileLines*) ptr2)->lineStart;

    assert (str1 != nullptr && str2 != nullptr);

    while (*str1 && *str2)
    {
        str1 = skipLeftSymbols (str1);
        str2 = skipLeftSymbols (str2);

        if (*str1 && *str2 && toupper (*str1) != toupper (*str2))
        {
            return (toupper (*str1) - toupper (*str2));
        }
        else
        {
            str1++;
            str2++;
        }
    }

    return *str1 - *str2;
}

const char* skipLeftSymbols (const char* str)
{
    assert (str != nullptr);

    while (*str && !isalpha (*str) && isspace (*str))
    {
        str++;
    }

    return str;
}