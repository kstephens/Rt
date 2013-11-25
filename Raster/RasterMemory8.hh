#ifndef	__Raster_RasterMemory8_hh
#define	__Raster_RasterMemory8_hh

#include "Raster/RasterMemory.hh"

class RasterMemory8 : public RasterMemory {
public:
	RasterMemory8(const RasterSize& s) : RasterMemory(s, 8) {}

  RasterValue	value(const RasterPosition& p) const;
  void		value(const RasterPosition& p, const RasterValue& v);
};

#endif

