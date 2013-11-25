#include "Raster/RasterFileRGB.hh"
#include "Raster/RGB.hh"
#include "Raster/error.h"

RasterFileRGB::RasterFileRGB(const char* filename, const RasterSize& size ) :
	RasterFile( filename, size, 24, 0 ) {
}

RasterFileRGB::RasterFileRGB(const char* filename ) :
	RasterFile(filename) {
	if ( header.bitsperpixel != 24 ) FATAL
}

RasterColor
RasterFileRGB::color ( const RasterPosition& p ) const {
	RGB	rgb;
	read(p, (char*) &rgb, sizeof(rgb));
	return RasterColor(rgb.r, rgb.g, rgb.b);
}

void
RasterFileRGB::color ( const RasterPosition& p, const RasterColor& c ) {
	RGB	rgb ( c.red(), c.green(), c.blue() );
	write(p, &rgb, sizeof(rgb));
}

RasterLUT*
RasterFileRGB::LUT() const { return (RasterLUT*) 0L; }

