#include "Raster/RasterLUTCore.hh"
#include <unistd.h>

void
RasterLUTCore::read(int fd)
{
  size_t size;
  ::read(fd, (void*) &size, sizeof(size));
  for ( int i = 0; i < size; i ++ ) {
  }
}
