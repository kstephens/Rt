//
// Raster.cc - class Raster
// KAS 91/06/12
//
#include "Raster.hh"
#include "error.h"

#ifndef	NULL
#define	NULL	((Raster*) 0L)
#endif

Raster* 	Raster::read(const char* filename ) { NOT_IMPLEMENTED; return NULL; }
int		Raster::write(const char* filename, const char* type ) { NOT_IMPLEMENTED; return 0; }

Raster::~Raster() {}

RasterType	Raster::type() const {
	return "Raster";
}
int		Raster::isATypeOf( RasterType t ) const {
	return t == Raster::type();
}

int	Raster::bitsPerPixel() const { NOT_IMPLEMENTED; return 0; }

Raster*	Raster::parent() const { return NULL; }
void	Raster::parent( Raster* p) { NOT_IMPLEMENTED }

Raster*	Raster::parentRoot() const {
	Raster*	p = parent();

	while ( p != NULL )
		p = p->parent();

	return p;
}

void	Raster::parentRoot( Raster* p ) { NOT_IMPLEMENTED }

RasterPosition	Raster::offset() const { return RasterPosition(0,0); }
void		Raster::offset( const RasterPosition& p ) { NOT_IMPLEMENTED }

RasterPosition	Raster::offsetRoot() const {
	Raster* p = parent();
	RasterPosition	pos = offset();

	while ( p != NULL ) {
		pos += p->offset();
		p = p->parent();
	}

	return pos;
}
void		Raster::offsetRoot( const RasterPosition& p ) { NOT_IMPLEMENTED }

RasterSize	Raster::size() const { NOT_IMPLEMENTED; return RasterSize(0,0); }
void		Raster::size( const RasterSize& s ) { NOT_IMPLEMENTED }

void		Raster::resize( const RasterSize& s) { size(s); }

float		Raster::pixelAspectRatioXY() const { return 1.0; }

RasterValue	Raster::value( const RasterPosition& p ) const { NOT_IMPLEMENTED; return 0.0; }
void		Raster::value( const RasterPosition& p, const RasterValue& v ) { NOT_IMPLEMENTED }

RasterColor	Raster::color( const RasterPosition& p ) const { NOT_IMPLEMENTED; return 0.0; }
void		Raster::color( const RasterPosition& p, const RasterColor& v ) { NOT_IMPLEMENTED }

RasterLUT*	Raster::LUT() const { return (RasterLUT*) NULL; }
void		Raster::LUT(RasterLUT* LUT) { NOT_IMPLEMENTED }

void		Raster::horizontal ( const RasterPosition& P, int l, const RasterValue& v ) {
	RasterPosition	p = P;
	if ( l > 0 )
		while ( l -- ) {
			value(p, v);
			p.x ++;
		}
	else
		while ( l ++ ) {
			value(p, v);
			p.x --;
		}
}

void		Raster::horizontal ( const RasterPosition& P, int l, const RasterColor& v ) {
	RasterPosition p = P;
	if ( l > 0 )
		while ( l -- ) {
			color(p, v);
			p.x ++;
		}
	else
		while ( l ++ ) {
			color(p, v);
			p.x --;
		}
}


void		Raster::vertical ( const RasterPosition& P, int l, const RasterValue& v ) {
	RasterPosition p = P;
	if ( l > 0 )
		while ( l -- ) {
			value(p, v);
			p.y ++;
		}
	else
		while ( l ++ ) {
			value(p, v);
			p.y --;
		}
}

void		Raster::vertical ( const RasterPosition& P, int l, const RasterColor& v ) {
	RasterPosition p = P;
	if ( l > 0 )
		while ( l -- ) {
			color(p, v);
			p.y ++;
		}
	else
		while ( l ++ ) {
			color(p, v);
			p.y --;
		}
}


void  lineDDA ( RasterPosition p0, RasterPosition p1, lineDDAFunc func, void* data ) {
	RasterPosition	delta = p1 - p0;
	RasterPosition	signdelta = delta.sign();
	RasterPosition 	absdelta = delta.abs();
	int	majoraxis, minoraxis;

	if ( absdelta.x > absdelta.y ) {
		majoraxis = 0;
		minoraxis = 1;
	} else {
		majoraxis = 1;
		minoraxis = 0;
	}

	if ( p0[majoraxis] > p1[majoraxis] ) {
		RasterPosition temp = p0;
		p0 = p1;
		p1 = temp;
		delta.negate();
	}
	register	int	count = absdelta[majoraxis];

	(*func)(p0, data);
	if ( absdelta[minoraxis] == 0 ) {
		do {
			p0[majoraxis] += signdelta[majoraxis];

			(*func)(p0, data);
		} while ( -- count ) ;
	} else {
		register	int 	signdeltaminoraxis = signdelta[minoraxis];
		if ( absdelta[minoraxis] == absdelta[majoraxis] ) {
			do {
				p0[minoraxis] += signdeltaminoraxis;
				p0[majoraxis] ++;

				(*func)(p0, data);
			} while ( -- count );
		} else {
                  int	error = (absdelta[minoraxis] << 1) - absdelta[majoraxis];
			int	minorerrordelta = absdelta[minoraxis] << 1;
			int	majorerrordelta = (absdelta[minoraxis] - absdelta[majoraxis]) << 1;

			do {
				if ( error < 0 ) {
					error += minorerrordelta;
					p0[minoraxis] += signdeltaminoraxis;
				}
				error += majorerrordelta;
				p0[majoraxis] ++;

				(*func)(p0, data);
			} while ( -- count );
		}
	}
}

struct	vectorValueData {
	Raster* p;
	const RasterValue& v;
	vectorValueData(Raster* P, const RasterValue& V) : p(P), v(V) {}
};

static
void		vectorValue ( const RasterPosition& pos, void *DATA) {
	vectorValueData&	data = * (vectorValueData*) DATA;

	data.p->value(pos, data.v);
}

void		Raster::vector ( const RasterPosition& p0, const RasterPosition& p1, const RasterValue& v) {
	vectorValueData	data ( this, v );

	lineDDA( p0, p1, vectorValue, (void*) &data);
}

struct	vectorColorData {
	Raster* p;
	const RasterColor& c;
	vectorColorData(Raster* P, const RasterColor& C) : p(P), c(C) {}
};

static
void		vectorColor ( const RasterPosition& pos, void* DATA) {
	vectorColorData&	data = * (vectorColorData*) DATA;

	data.p->color(pos, data.c);
}

void		Raster::vector ( const RasterPosition& p0, const RasterPosition& p1, const RasterColor& c ) {
	vectorColorData		data (this, c);

	lineDDA( p0, p1, vectorColor, (void*) &data);
}
