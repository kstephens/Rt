#ifndef	__Raster_RasterLUTCore_hh
#define	__Raster_RasterLUTCore_hh

#include "Raster/RasterLUT.hh"

class RasterLUTCore : public RasterLUT {
  RasterColor*	c;
  RasterValue	s; // number of entries
  void	alloc() { c = new RasterColor[s]; }
  void	free() { delete [] c; }
public:
  RasterLUTCore() : c(0), s(0) {}
  RasterLUTCore(const RasterValue& size) {
    c = new RasterColor[s = size];
  }
  RasterLUTCore(const RasterLUT &l): s(l.size()) { alloc(); copy(l); }
  RasterLUT&	operator = ( const RasterLUT& l ) {
    free();
    s = l.size();
    alloc();
    copy(l);
    return *this;
  }
  ~RasterLUTCore() { free(); c = 0; s = 0; }

  RasterValue	size() const { return s; }
  void		size(const RasterValue& v ) {
    free();
    s = v;
    alloc();
  }
  RasterColor value ( const RasterValue& v ) const {
    return c[v];
  }
  void color ( const RasterValue& v, const RasterColor& cv ) {
    c[v] = cv;
  }
  void	read ( int fd );
};

#endif
