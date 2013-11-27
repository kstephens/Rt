#include <stdlib.h>
#include <stdio.h>

static
double drand()
{
  return (double) rand() / (((double) RAND_MAX) + 1);
}

int main(int argc, char **argv)
{
  size_t size = 4096;
  int i;

  if ( argc > 1 )
    size = atoi(argv[1]);

  for ( i = 0; i < size; ) {
    printf("%.22g, ", drand());
    if ( ++ i % 8 == 0 ) {
      printf("\n");
    }
  }
  return 0;
}
