/*
** RiRand.h
** KAS 91/06/29
*/
#ifndef	__RiRand_h
#define	__RiRand_h

#include "ri/ri.h"
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

extern RtFloat RiRand_randtable[];
extern size_t RiRand_randtable_len;

extern	RtFloat	Rifloat_random();
extern	void	Ricolor_random(RtColor* color);
extern 	void	Ripoint_random(RtPoint* point);

#define RiRand() Rifloat_random()

#ifdef	__cplusplus
}
#endif

#endif
