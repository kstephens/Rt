#include "Raster/RasterLUT.hh"
#include <unistd.h> /* read(), write() */

void
RasterLUT::copy(const RasterLUT& l ) {
	RasterValue	min = size() < l.size() ? size() : l.size();
	for ( RasterValue i = 0; i < min; i ++ )
		color(i, l.color(i));

}

void
RasterLUT::size(const RasterValue& v ) {
}

RasterValue
RasterLUT::value(const RasterColor& c ) const {
	double	min = (c - color(0)).abs().sum();
	RasterValue	v = 0;

	for ( RasterValue i = 1; i < size(); i ++ ) {
		double	d = (c - color(i)).abs().sum();

		if ( d < min ) {
			min = d;
			v = i;
		}
	}
	return v;
}

void
RasterLUT::write(int fd ) const {
	RasterValue	s = size();
	::write(fd, (void*) &s, sizeof(s));
	for ( RasterValue i = 0; i < s; i ++ ) {
		RasterColor	c = color(i);
		::write(fd, (void*) &c, sizeof(c));
	}
}

void
RasterLUT::read(int fd ) {
	RasterValue	s;
	::read(fd, (void*) &s, sizeof(s));
	size(s);
	for ( RasterValue i = 0; i < s; i ++ ) {
		RasterColor	c;
		::read(fd, (void*) &c, sizeof(c));
		color(i, c);
	}
}
