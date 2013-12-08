#ifndef	__RasterMemory32_hh
#define	__RasterMemory32_hh

#include "Raster/RasterMemory.hh"

class RasterMemory32 : public RasterMemory {
public:
	RasterMemory32(const RasterSize& s) : RasterMemory(s, 32) {}

	RasterValue	value(const RasterPosition& p) const;
	void		value(const RasterPosition& p, const RasterValue& v);
  RasterColor	color( const RasterPosition& p ) const;
  void		color( const RasterPosition& p, const RasterColor& v );

};
#endif

