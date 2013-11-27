/*
** RiRand.c
** KAS 91/06/29
*/

#include "ri/RiRand.h"

#define randtable RiRand_randtable

RtFloat randtable[] = {
#include "randtable.h"
};
#define RANDTABLELEN (sizeof(randtable) / sizeof(randtable[0]))
size_t RiRand_randtable_len = RANDTABLELEN;

static RtFloat* curr = randtable;
#define	RANDTABEND	(randtable + RANDTABLELEN)
#define	RAND()	(*((++ curr == RANDTABEND) ? curr = randtable : curr))

RtFloat	Rifloat_random()
{
  return RAND();
}

void Ricolor_random(RtColor* c)
{
  (*c)[0] = RAND(); (*c)[1] = RAND(); (*c)[2] = RAND();
}

void Ripoint_random(RtPoint* p)
{
  (*p)[0] = RAND(); (*p)[1] = RAND(); (*p)[2] = RAND();
}

