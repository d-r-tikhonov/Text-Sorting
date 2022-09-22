#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEBUG

#ifdef DEBUG 
	FILE *const logFile = stderr;
	#define $$                                                                        \
	    fprintf(logFile, "[%s %s, %d]: I'm here" "\n", __TIME__, __FILE__, __LINE__); \
	    fflush(logFile);                                                              \
#endif
