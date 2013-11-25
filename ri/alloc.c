/*
** alloc.c
** KAS 91/06/29
*/
#include <stdlib.h>
#include <stdio.h>

void*
alloc(int size, int len)
{
  void*	p;
  if ( (p = (void*) malloc(size * len)) == NULL ) {
    fprintf(stderr, "out of memory!\n");
    exit(1);
  }
  return p;
}
