
//
//
//
#ifndef	__RasterCore_hh
#define	__RasterCore_hh

#include "Raster.hh"
#include <assert.h>

class RasterMemory : public Raster {
protected:
  unsigned char*	memory;
  RasterSize	s;
  int	bitsperpixel;

  U32 xsize() const {
    return ((bitsperpixel * s.x) >> 3) + 1;
  }
  U32 buffersize() const {
    return xsize() * s.y;
  }
  unsigned char *address(int y) const {
    assert(y >= 0);
    assert(y < s.y);
    return memory + xsize() * y;
  }
  unsigned char *address(int x, int y) const {
    assert(x >= 0);
    assert(x < s.x);
    return address(y) + ((x * bitsperpixel) >> 3);
  }
  void	alloc();
  void	dealloc();
public:
  RasterMemory( const RasterSize& S, int bpp ) : s(S), bitsperpixel(bpp) {
    alloc();
  }
  virtual ~RasterMemory();

  int bitsPerPixel() const { return bitsperpixel; }
  RasterSize size() const { return s; }
  void size( const RasterSize& S );

  virtual RasterValue value(const RasterPosition& s ) const = 0;
  virtual void        value(const RasterPosition& s, const RasterValue& v ) = 0;

  virtual RasterColor color(const RasterPosition& s ) const = 0;
  virtual void        color(const RasterPosition& s, const RasterColor& c ) = 0;
};

#endif
