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
* 	\version 		1.4
* 	\date 			September, 2022
* 	\bug 			not found yet.
* 	\warning 		There are no such.
* 	\copyright 		Copyright © 2022 Dmitry Tikhonov. All rights reserved.
* 	\todo 			TODO LIST.
* 
*/

#include <stdio.h>

#include "string_func_operation.h"

///////////////////////////////////////////////////////////////
/// @param nlines 	Number of lines read
/// @param lineptr	Pointer to a string
///////////////////////////////////////////////////////////////
int main()
{
    struct paramStr string[5000] = {};
    struct paramStr *ptrStr = string;

	int nlines = 0;

	FILE * ptrFile = fopen ("inputFile.txt", "r");

	if (ptrFile == NULL) 
    {
  		printf ("Error opening files!\n");
        return 1;
    }

    nlines = readlines (ptrStr, ptrFile);

    fclose (ptrFile);

    qsort        (ptrStr, nlines - 1, &cmpFromBegin);
    writelines   (ptrStr, nlines - 1);

    clearBuffer  (ptrStr, nlines);

	return 0;
}