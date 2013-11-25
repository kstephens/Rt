#include "Raster/Histogram.hh"

void
Histogram::clear ()
{
  for ( int i = 0; i < _size; i ++ )
    (*this)[i] = 0;
}

U32
Histogram::area(int l, int r)
{
  U32 sum = 0;

  for ( int i = l; i < r; i ++ )
    sum += (*this)[i];
  
  return sum;
}

int
Histogram::median(int l, int r)
{
  U32	halfarea = area(l,r) / 2;
  U32	sum = 0;
  int i;
  for ( i = l; i < r; i ++ ) {
    sum += (*this)[i];
    if ( sum >= halfarea )
      break;
  }
  return i;
}

int
Histogram::min(int l, int r)
{
  int i;
  for ( i = l; i < r; i ++ )
    if ( (*this)[i] > 0 )
      break;
  return i;
}

int
Histogram::max(int l, int r)
{
  int i;
  for ( i = r - 1; i >= l; i -- )
    if ( (*this)[i] > 0 )
      break;
  return i;
}
