#ifndef	__Bound_hh
#define	__Bound_hh

#include "Point.hh"
#include "EPSINF.hh"

#define	SWAP(a,b) { float t = (a); (a) = (b); (b) = t; }
//inline void SWAP( float& a, float& b ) { float t = a; a = b; b = t; }

class Bound	{
public:
	Point	l, h;
	Bound () {
		l.x = l.y = l.z = INFINITY;
		h.x = h.y = h.z = - INFINITY;
	}
	Bound ( const Point& p1, const Point& p2 ) : l(p1), h(p2) {
		if ( l.x > h.x )
			SWAP(l.x, h.x);
		if ( l.y > h.y )
			SWAP(l.y, h.y);
		if ( l.z > h.z )
			SWAP(l.z, h.z);
	}
	Bound&	add(const Point& p ) {
		if ( p.x < l.x )
			l.x = p.x;
		if ( p.x > h.x )
			h.x = p.x;
		if ( p.y < l.y )
			l.y = p.y;
		if ( p.y > h.y )
			h.y = p.y;
		if ( p.z < l.z )
			l.z = p.z;
		if ( p.z > h.z )
			h.z = p.z;

		return *this;
	}
	const Point&	operator[](int i) const { return (&l)[i]; }

	int	isIn( const Point& p) const {
		return p.x >= l.x && p.y >= l.y && p.z >= l.z &&
			p.x <= h.x && p.y <= h.y && p.z <= h.z;
	}
};

#undef	SWAP

#endif
