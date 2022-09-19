/*! \mainpage 			A program for sorting strings
 *
 * - \ref 				This program sorts strings alphabetically
 * - \ref 				You can insert the text you want to sort in the file inputFile.txt
 * 
 * - \subpage guide 	"How to use the program?"
 * - \subpage authors 	"Authors of the program"
 *
 */ 

/*! \page guide 				How to use the program?
 *
 * - \ref    					This is a page about how to use this program.
 * - \ref 						In development
 * 
 */

/*! \page authors 	Authors of the program
 * 
*   \authors 		Tikhonov D.R.
* 	\version 		1.5
* 	\date 			September, 2022
* 	\bug 			
* 	\warning 		There are no such.
* 	\copyright 		Copyright © 2022 Dmitry Tikhonov. All rights reserved.
* 	\todo 			
* 
*/

// #define NDEBUG

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#include "text_processing.h"

enum cmdArgs
{
    CMP_BEGIN = 0,  
    CMP_END   = 1,
};

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen ("inputFile.txt", "r");
    if (inputFile == nullptr) 
    {
        printf ("Error opening files!\n");
        return errno;
    }

    int cmdArgsStatus = CMP_BEGIN;
    if (argc > 1 && strcmp (argv[1], "-r") == 0)
        cmdArgsStatus = CMP_END;

    int (*funcPtr) (const struct lines*, const struct lines*) = nullptr;
    switch (cmdArgsStatus)
    {
        case CMP_BEGIN:
            funcPtr = cmpFromBegin;
            break;
        case CMP_END:
            funcPtr = cmpFromEnd;
            break;
        default:
            printf("Error! In switch(cmdArgsStatus)!");
            break;
    }

    char* buffer = cpyFileToBuffer (inputFile);
    assert (buffer != nullptr);

    const size_t nLines = nLinesFile (buffer);
    struct lines* string = (lines* ) calloc (nLines, sizeof(lines));

    if (fclose (inputFile) != 0)
        printf("File closing error!");

    size_t readLinesReturn = readLines (buffer, string);
    assert (nLines == readLinesReturn);

    bubbleSort (string, nLines, sizeof(lines), (int (*) (const void*, const void*)) funcPtr);

    FILE* outputFile = fopen ("outputFile.txt", "w");
    if (outputFile == nullptr) 
    {
        printf ("Error opening files!\n");
        return 1;
    }
    writeLines (string, nLines, stdout);

    if (fclose (outputFile) != 0)
        printf("File closing error!");

    memClr(string, nLines, buffer);

    assert(string == nullptr);
    assert(buffer == nullptr);

	return 0;
}