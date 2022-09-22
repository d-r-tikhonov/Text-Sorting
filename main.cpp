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

#define NDEBUG

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

int main(int argc, const char* argv[])
{
    FILE* inputFile = fopen ("inputFile.txt", "r");
    if (inputFile == nullptr) 
    {
        printf ("Error opening file! Name of file: inputFile.txt\n");
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
            printf("Error! In switch(cmdArgsStatus)! funcPtr = %d", funcPtr);
            break;
    }

    if (fclose (inputFile) != 0)
        printf("Error opening file! Name of file: inputFile.txt\n");

    struct lines* string = readLines(inputFile);

    // bubbleSort (string, nLines, sizeof(lines), (int (*) (const void*, const void*)) funcPtr);

    // FILE* outputFile = fopen ("outputFile.txt", "w");
    // if (outputFile == nullptr) 
    // {
    //     printf ("Error opening file! Name of file: outputFile.txt\n");
    //     return errno;
    // }
    // writeLines (string, nLines, outputFile);

    // if (fclose (outputFile) != 0)
    //     printf("File closing error! Name of file: outputFile.txt");

	return 1;
}