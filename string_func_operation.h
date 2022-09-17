#ifndef __STRING_FUNC_OPERATION__
#define __STRING_FUNC_OPERATION__

struct paramStr
{
    char* lineptr;
    int   countSymb;
};

///////////////////////////////////////////////////////////////
/// @brief 				Reads characters from the input stream, allocates space for them
/// @param[in] string	Pointer to a string pointer		
/// @param[in] nlines 	The stream from where the characters are read
/// @return 			Number of characters read
///////////////////////////////////////////////////////////////
size_t getlineFile (char **string, FILE *stream);


///////////////////////////////////////////////////////////////
/// @brief 						Compares strings like strcmp()
/// @param[in] firstLinePtr		The first line to be compared
/// @param[in] secondLinePtr 	The second line to be compared
/// @return 					NULL, in case of equality
/// @return 					positive value if the first row is higher in order than the second; negative value otherwise
///////////////////////////////////////////////////////////////
int cmpFromBegin (struct paramStr *p, int adressFirstStr, int adressSecondStr);
int cmpFromEnd	 (struct paramStr *p, int adressFirstStr, int adressSecondStr);


///////////////////////////////////////////////////////////////
/// @brief 							Changes pointers to strings between each other
/// @param[in] lineptr				Array of pointers to strings	
/// @param[in] adressFirstString 	Address of the first line
/// @param[in] adressSecondString	Address of the second line
///////////////////////////////////////////////////////////////
void swap (struct paramStr *p, int adressFirstString, int adressSecondString);


///////////////////////////////////////////////////////////////
/// @brief 							Sorts strings in alphabetical order
/// @param[in] lineptr				Array of pointers to strings	
/// @param[in] adressFirstString 	Number of rows
///////////////////////////////////////////////////////////////
void qsort (struct paramStr *p, int nlines, int (*cmpFunc) (struct paramStr *p, int adressFirstString, int adressSecondString));


///////////////////////////////////////////////////////////////
/// @brief 				Reading lines from the input stream
/// @param[in] lineptr	Array of pointers		
/// @param[in] nlines 	Number of lines read
/// @return 			Number of lines read
///////////////////////////////////////////////////////////////
int readlines (struct paramStr *p, FILE *stream);


///////////////////////////////////////////////////////////////
/// @brief 				Output of ordered strings
/// @param[in] lineptr	Array of pointers		
/// @param[in] nlines 	Number of lines read
///////////////////////////////////////////////////////////////
void writelines (struct paramStr *p, int nlines);


///////////////////////////////////////////////////////////////
/// @brief 				To clear the buffer
/// @param[in] lineptr	Array of pointers		
/// @param[in] nlines 	Number of lines read
///////////////////////////////////////////////////////////////
void clearBuffer(struct paramStr *p, int nlines);


#endif