//
// RGBDither.hh - class RasterRGBDither
// KAS 91/06/23
//
#ifndef	__Raster_RasterRGBDither_hh
#define	__Raster_RasterRGBDither_hh

#include "Raster/Raster.hh"

class RasterRGBDither : public Raster {
  Raster*	r;
  RasterValue	cubesize;
  void	init();
public:
  RasterRGBDither ( Raster* R ) : r(R) { init(); }

  RasterType	type() const;
  int		isATypeOf(RasterType t) const;

  Raster*	parent() const { return r; }

  int		bitsPerPixel() const { return r->bitsPerPixel(); }

  RasterSize	size() const { return r->size(); }
  void		size(const RasterSize& s ) { r->size(s); }

  RasterValue	value ( const RasterPosition& p ) const {
          return r->value(p);
  }
  void		value ( const RasterPosition& p, const RasterValue& v ) {
          r->value(p,v);
  }

  //
  // The dithering function
  //
  RasterValue	value ( const RasterColor& c, const RasterPosition& p ) const;
  RasterColor	color ( const RasterPosition& p ) const {
          return r->LUT()->color(r->value(p));
  }
  void		color ( const RasterPosition& p, const RasterColor& c ) {
          r->value(p, value(c,p));
  }

  RasterLUT*	LUT() const { return r->LUT(); }
  void		LUT(RasterLUT* lut);
};

#endif
