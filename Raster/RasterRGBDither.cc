//
// RasterRGBDither.cc
// KAS 91/06/23
//
#include "Raster/RasterRGBDither.hh"
#include <math.h>

RasterType
RasterRGBDither::type() const { return "RasterRGBDither"; }

int
RasterRGBDither::isATypeOf(RasterType t) const {
	return t == type() || Raster::isATypeOf(t);
}

void
RasterRGBDither::init() {
	RasterLUT&	lut = *(r->LUT());
	RasterValue	lutsize = lut.size();
	cubesize = 1;

	//
	// Find an appropriate color cube size.
	//
	while ( cubesize * cubesize * cubesize < lutsize )
		cubesize ++;
	cubesize --;

	RasterValue	squarearea = cubesize * cubesize;
	RasterValue	cubelen = squarearea * cubesize;
	double		factor = 1.0 / (double) cubesize;

	
	for ( int i = 0; i < cubelen; i ++ ) {
		double	r = i % cubesize;
		double	g = (i % squarearea) / cubesize;
		double	b = i / squarearea;

		lut.color( i,
			RasterColor( r * factor,
				g * factor,
				b * factor ) );
	}
}

//
// The dither matrix for SpatialDither
//
static
/* scale: 1 */
unsigned char	D8x8[8][8] =
{
	{   0,  32,   8,  40,   2,  34,  10,  42 },
	{  48,  16,  56,  24,  50,  18,  58,  26 },
	{  12,  44,   4,  36,  14,  46,   6,  38 },
	{  60,  28,  52,  20,  62,  30,  54,  22 },
	{   3,  35,  11,  43,   1,  33,   9,  41 },
	{  51,  19,  59,  27,  49,  17,  57,  25 },
	{  15,  47,   7,  39,  13,  45,   5,  37 },
	{  63,  31,  55,  23,  61,  29,  53,  21 }
};

//
// Compute the dither for a fraction
//
inline
int	SpatialDither (float fraction, int x, int y ) {

	return ((unsigned char) (fraction * 64.0) > D8x8[y & 7][x & 7]) ?
		1 :
		0;
}
inline double fraction ( const double& x ) {
	return x - floor ( x );
}

//
// Compute a LUT value for a Color
//
RasterValue
RasterRGBDither::value( const RasterColor& c, const RasterPosition& p ) const {
	float	factor	= (float) cubesize - 0.0001;

	float	ri = c.red() * factor;
	float	gi = c.green() * factor;
	float	bi = c.blue() * factor;

	float	rf = fraction ( ri );
	float	gf = fraction ( gi );
	float	bf = fraction ( bi );

	return int (ri) + SpatialDither( rf, p.x, p.y) +
	cubesize * (int (gi) + SpatialDither( gf, p.x + 1, p.y) +
	cubesize * (int (bi) + SpatialDither( bf, p.x, p.y + 1)));
}

void
RasterRGBDither::LUT(RasterLUT* lut ) {
	r->LUT(lut);
	init();
}

