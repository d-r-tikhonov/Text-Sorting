#ifndef __READ_AND_WRITE_FUNC__
#define __READ_AND_WRITE_FUNC__


///////////////////////////////////////////////////////////////
/// @brief 			Чтение строк
/// @param nlines 	Количество прочитанных строк
///////////////////////////////////////////////////////////////
int readlines(char* lineptr[], FILE *stream);



void writelines(char* lineptr[], int nlines);


#endif