#include "ri/ri.h"
#include <stdio.h>

RtPoint	point = { 0.0, 1.0, 2.0 };
void foo(RtPoint p)
{
  RtPoint x = { -1.0, -1.0, -1.0 };
  
  if ( (void*) &p == (void*) &point )
    printf("pass by reference\n");
  else
    printf("pass by value\n");
  
  if ( x[0] == p[0] && x[1] == p[1] && x[2] == p[2] )
    printf("assignment by bitwise copy\n");
  else
    printf("bad assignment\n");
}

int main(int argc, char **argv)
{
  foo(point);
  return 0;
}
