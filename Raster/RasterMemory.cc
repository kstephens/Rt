#include "RasterMemory.hh"
#include <string.h>

void RasterMemory::alloc()
{
  memory = new unsigned char[buffersize()];
  memset(memory, sizeof(unsigned char) * buffersize(), 0);
}
void RasterMemory::dealloc()
{
  delete memory;
}

RasterMemory::~RasterMemory()
{
  dealloc();
}

void RasterMemory::size( const RasterSize& S )
{
  dealloc();
  s = S;
  alloc();
}

