/*
** assign.h
** KAS 91/06/29
*/
#ifndef	__assign_h
#define	__assign_h

#include <string.h> /* memcpy() */

#define	ASSIGN(a,b)	memcpy((void*) &(a), (void*) &(b), sizeof(a));

#endif

