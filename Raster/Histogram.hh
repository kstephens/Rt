#ifndef	__Histogram_hh
#define	__Histogram_hh

#include "portable.h"
#include "Buffer.hh"

class Histogram : Buffer {
  size_t	_size;
public:
  Histogram() : _size(0), Buffer() {}
  Histogram(size_t size)
  : _size(size), Buffer(size * sizeof(U32))
  {
    clear();
  }

  void size(size_t size) {
    _size = size;
    Buffer::size(size * sizeof(U32));
  }

  U32& operator [] (int i) {
    return ((U32*) Buffer::buffer())[i];
  }
  void clear ();
  void take(int i) {
    (*this)[i] ++;
  }

  U32 area(int l, int r);

  int median(int l, int r);
  int min(int l, int r);
  int max(int l, int r);
};

#endif
