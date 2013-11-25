#include "Raster/RasterFile.hh"
#include <fcntl.h>
#include <unistd.h> /* read(), write() */

RasterFileHeader::RasterFileHeader()
{
  magic = *((U32*) "RAST");
}

int
RasterFileHeader::read(int fd)
{
  return ::read(fd, (void*) this, sizeof(*this));
}

int
RasterFileHeader::write(int fd)
{
  return ::write(fd, (void*) this, sizeof(*this));
}

inline
long
RasterFile::imagelen(const RasterPosition& p ) const
{
  return (long) xbytes * (long) p.y + (((long) p.x * header.bitsperpixel) >> 3);
}

inline
void
RasterFile::image( const RasterPosition& p ) const
{
  lseek( fd, imageaddress + imagelen(p), SEEK_SET);
}

void
RasterFile::read( const RasterPosition& p, void* b, int len ) const
{
  image(p);
  ::read(fd, b, len);
}

void
RasterFile::write( const RasterPosition& p, void* b, int len ) const
{
  image(p);
  ::write(fd, b, len);
}


RasterFile::RasterFile(const char*filename, const RasterSize& size, int bitsperpixel, RasterValue lutsize )
{
#ifndef O_BINARY
#define O_BINARY 0
#endif
  fd = open( filename, O_RDWR | O_BINARY | O_CREAT );
  header.size = size;
  header.bitsperpixel = bitsperpixel;
  header.write(fd);
  
  lut.size((lutsize != 0xffffffffL) ? lutsize : 1 << bitsperpixel);
  lut.write(fd);

  imageaddress = lseek(fd, SEEK_CUR, 0); // tell(fd);

  xbytes = ((header.size.x + 7) * header.bitsperpixel) >> 3;

  //
  // Fill the rest
  //
  {
#define	BS	512
    char 	buf[BS];
    long	len = imagelen(size);
    while ( len > BS ) {
      write( fd, buf, BS);
      len -= BS;
    }
    write( fd, buf, len);
#undef	BS
  }
}

RasterFile::RasterFile(const char *filename )
{
  fd = open( filename, O_RDWR | O_BINARY );
  lseek(fd, 0L, SEEK_SET);
  header.read(fd);
  lut.read(fd);
  imageaddress = lseek(fd, SEEK_CUR, 0); // tell(fd);
  
  xbytes = ((header.size.x * header.bitsperpixel) >> 3) + 1;
}


RasterFile::~RasterFile() {
  close(fd);
}

RasterSize
RasterFile::size() const
{
  return header.size;
}

RasterValue
RasterFile::value( const RasterPosition& p ) const
{
  RasterValue	v = 0;
  read(p, (void*) &v, header.bitsperpixel >> 3);
  return v;
}

void
RasterFile::value(const RasterPosition& p, const RasterValue& v )
{
  write(p, (void*) &v, header.bitsperpixel >> 3);
}

RasterColor
RasterFile::color( const RasterPosition& p ) const
{
  return LUT()->color(value(p));
}

void
RasterFile::color( const RasterPosition& p, const RasterColor& c )
{
  value(p, LUT()->value(c));
}

RasterLUT*
RasterFile::LUT() const
{
  return (RasterLUT*) &lut;
}

