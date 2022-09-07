#ifndef __READ_AND_WRITE_FUNC__
#define __READ_AND_WRITE_FUNC__


///////////////////////////////////////////////////////////////
/// @brief 				Reading lines from the input stream
/// @param[in] lineptr	Array of pointers		
/// @param[in] nlines 	Number of lines read
/// @return 			Number of lines read
///////////////////////////////////////////////////////////////
int readlines(char* lineptr[], FILE *stream);


///////////////////////////////////////////////////////////////
/// @brief 				Output of ordered strings
/// @param[in] lineptr	Array of pointers		
/// @param[in] nlines 	Number of lines read
///////////////////////////////////////////////////////////////
void writelines(char* lineptr[], int nlines);


#endif