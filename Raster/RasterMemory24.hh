#ifndef	__RasterMemory24_hh
#define	__RasterMemory24_hh

#include "Raster/RasterMemory.hh"

class RasterMemory24 : public RasterMemory {
public:
	RasterMemory24(const RasterSize& s) : RasterMemory(s, 24) {}

	RasterValue	value(const RasterPosition& p) const;
	void		value(const RasterPosition& p, const RasterValue& v);
  RasterColor	color( const RasterPosition& p ) const;
  void		color( const RasterPosition& p, const RasterColor& v );

};
#endif

