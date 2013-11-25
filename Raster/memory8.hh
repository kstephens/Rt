//
// Core8.hh - class RasterCore8
//
//
#ifndef	__RasterCore8_hh
#define	__RasterCore8_hh

#include "Raster/Core.hh"

class RasterCore8 : public RasterCore {
public:
	RasterCore8(const RasterSize& s) : RasterCore(s,8) {}

	RasterValue	value(const RasterPosition& p) const;
	void		value(const RasterPosition& p, const RasterValue& v);
};
#endif

