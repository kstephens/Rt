//
// RasterDevice.hh - class RasterDevice
//
#ifndef	__Raster_RasterDevice_hh
#define	__Raster_RasterDevice_hh

#include "Raster/Raster.hh"

class RasterDevice : public Raster {
public:
virtual	~RasterDevice();
virtual	RasterType	type() const;
virtual	int		isATypeOf(RasterType) const;

virtual	int		bitsPerPixel() const = 0;

	Raster*		parent() const;

virtual	RasterSize	size() const = 0;

virtual	float		pixelAspectRatioXY() const;

virtual	RasterValue	value( const RasterPosition& ) const = 0;
virtual	void		value( const RasterPosition&, const RasterValue& ) = 0;

virtual	RasterColor	color( const RasterPosition& ) const = 0;
virtual	void		color( const RasterPosition&, const RasterColor& ) = 0;

virtual	RasterLUT*	LUT() const = 0;

};

#endif
