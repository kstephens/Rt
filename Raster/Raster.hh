//
// Raster.hh - class Raster
// KAS 91/06/11
//
#ifndef	__Raster_Raster_hh
#define	__Raster_Raster_hh

#include "Raster/RasterPosition.hh"
#include "Raster/RasterSize.hh"
#include "Raster/RasterValue.hh"
#include "Raster/RasterColor.hh"
#include "Raster/RasterType.hh"
#include "Raster/RasterLUT.hh"

class Raster {
public:
virtual	~Raster();

//
// Read/Write a raster (in a specified format)
//
static	Raster*	read( const char* filename);
	int	write( const char* filename, const char* format = "Raster" );

//
// Query the about the Raster's type
//
virtual	RasterType	type() const;
virtual	int		isATypeOf(RasterType) const;

//
// How many bits per pixel?
//
virtual	int		bitsPerPixel() const;
  virtual int             channelsPerPixel() const;
  virtual int hasAlpha() const;

//
// Get/Set the immediate parent.
//
virtual	Raster*	parent() const;
virtual	void	parent( Raster* );

//
// Get/Set the ultimate parent. (Adam/Eve ;^)
//
virtual	Raster*	parentRoot() const;
virtual	void	parentRoot( Raster* );


//
// Get/Set the offset relative to immediate parent.
//
virtual	RasterPosition	offset() const;
virtual	void		offset( const RasterPosition& );

//
// Get/set the offset relative to ultimate parent.
//
virtual	RasterPosition	offsetRoot() const;
virtual	void		offsetRoot( const RasterPosition& );

virtual	RasterSize	size() const;
virtual	void		size( const RasterSize& );
virtual	void		resize( const RasterSize& ); // preserve contents

//
// give the ratio of X/Y dimentions for a pixel.
//  for RasterCore this is always 1.
//  for RasterFile or RasterDevice it may be different.
//
virtual	float		pixelAspectRatioXY() const;

//
// Get/Set pixels by value or color
//
virtual	RasterValue	value( const RasterPosition& ) const;
virtual	void		value( const RasterPosition&, const RasterValue& );

virtual	RasterColor	color( const RasterPosition& ) const;
virtual	void		color( const RasterPosition&, const RasterColor& );

//
// The Raster's RasterColor LookUp Table.
//
virtual	RasterLUT*	LUT() const;
virtual	void		LUT(RasterLUT*);

//
// Do a median cut conversion.
//
	void		medianCut(Raster* output, RasterValue lutsize = 0);

//
// Line routines
//
virtual	void		horizontal ( const RasterPosition&, int, const RasterValue& );
virtual	void		horizontal ( const RasterPosition&, int, const RasterColor& );

virtual	void		vertical ( const RasterPosition&, int, const RasterValue& );
virtual	void		vertical ( const RasterPosition&, int, const RasterColor& );

virtual	void		vector ( const RasterPosition&, const RasterPosition&, const RasterValue& );
virtual	void		vector ( const RasterPosition&, const RasterPosition&, const RasterColor& );
};

typedef 	void	(*lineDDAFunc)(const RasterPosition& pos, void* data);
void lineDDA(RasterPosition p1, RasterPosition p2, lineDDAFunc, void* );

#endif

