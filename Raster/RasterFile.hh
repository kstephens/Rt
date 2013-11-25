#ifndef	__Raster_RasterFile_hh
#define	__Raster_RasterFile_hh

#include "Raster/Raster.hh"
#include "Raster/portable.h"
#include "Raster/RasterLUTFile.hh"

struct RasterFileHeader {
  U32	magic;
  RasterSize	size;
  U8	bitsperpixel;
  RasterFileHeader();
  
int read(int fd);
int write(int fd);
};

class RasterFile : public Raster {
protected:
  int	fd;
  long	imageaddress;
  RasterFileHeader	header;
  RasterLUTFile	lut;
  U16	xbytes;
  
  long	imagelen(const RasterPosition& p) const;
  void	image(const RasterPosition& p) const;
  void	read(const RasterPosition& p, void* b, int len ) const;
  void	write(const RasterPosition& p, void* b, int len) const;

  RasterFile(const char*filename, const RasterSize&, int bitsperpixel, RasterValue lutsize = 0xffffffffL);
  RasterFile(const char*filename );
public:
  virtual	~RasterFile();

  RasterSize	size() const;

  virtual	RasterLUT*	LUT() const;

  virtual	RasterValue	value( const RasterPosition& p ) const;
  virtual	void		value( const RasterPosition& p, const RasterValue& v);
  
  virtual	RasterColor	color( const RasterPosition& p ) const;
  virtual	void		color( const RasterPosition& p, const RasterColor& c) = 0;
};

#endif

