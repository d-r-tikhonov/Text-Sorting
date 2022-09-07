#ifndef __STRING_FUNC_OPERATION__
#define __STRING_FUNC_OPERATION__


///////////////////////////////////////////////////////////////
/// @brief 				Reads characters from the input stream, allocates space for them
/// @param[in] string	Pointer to a string pointer		
/// @param[in] nlines 	The stream from where the characters are read
/// @return 			Number of characters read
///////////////////////////////////////////////////////////////
size_t getlineFile(char **string, FILE *stream);


///////////////////////////////////////////////////////////////
/// @brief 						Compares strings like strcmp()
/// @param[in] firstLinePtr		The first line to be compared
/// @param[in] secondLinePtr 	The second line to be compared
/// @return 					NULL, in case of equality
/// @return 					positive value if the first row is higher in order than the second; negative value otherwise
///////////////////////////////////////////////////////////////
int isEqString(char* firstLinePtr, char* secondLinePtr);


///////////////////////////////////////////////////////////////
/// @brief 							Changes pointers to strings between each other
/// @param[in] lineptr				Array of pointers to strings	
/// @param[in] adressFirstString 	Address of the first line
/// @param[in] adressSecondString	Address of the second line
///////////////////////////////////////////////////////////////
void swap(char* lineptr[], int adressFirstString, int adressSecondString);


///////////////////////////////////////////////////////////////
/// @brief 							Sorts strings in alphabetical order
/// @param[in] lineptr				Array of pointers to strings	
/// @param[in] adressFirstString 	Number of rows
///////////////////////////////////////////////////////////////
void qsort(char* lineptr[], int nlines);


#endif