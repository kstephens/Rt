//
// RasterLUTFile.cc - class RasterLUTFile
// KAS 91/06/22
//
#include "Raster/RasterLUTFile.hh"
#include <fcntl.h>
#include <unistd.h>


RasterValue
RasterLUTFile::size() const { return _size; }

inline
void
RasterLUTFile::seek(const RasterValue& v ) const
{
  lseek(fd, loc + v * sizeof(RasterColor), SEEK_SET);
}

RasterColor
RasterLUTFile::color ( const RasterValue& v ) const
{
  RasterColor	c;

  seek(v);
  ::read(fd, (void*) &c, sizeof(c));

  return c;
}

void
RasterLUTFile::color ( const RasterValue& v, const RasterColor& c ) {
	seek(v);
	::write(fd, (void*) &c, sizeof(RasterColor));
}

void
RasterLUTFile::read(int _fd) {
	fd = _fd;
	::read(fd, &_size, sizeof(_size));
	loc = lseek(_fd, SEEK_CUR, 0); // tell(_fd);
}

