//
// Plane.hh - class Plane
//
//
#ifndef	__Plane_hh
#define	__Plane_hh

#include "Prim.hh"
#include "Bound.hh"

class Plane : public Prim, public Bound  {
	char 	axis;
	char	u, v;
	Point	size;
public:
	Plane() : Prim(), Bound(), axis(0) {}
	Plane(const Point& p1, const Point& p2, char a ) :
		Prim(), Bound(p1,p2), axis(a) {
			size = h - l;
			u = (axis + 1) % 3;
			v = (axis + 2) % 3; }

	Point	P( const Param& p );
	Param	p( const Point& p );

	normal NgP( const Point& p );
	normal Ngp( const Param& p );
	normal Ng(RPI* _p) { return NgP(_p->P()); }

	Point	dPduP( const Point& p );
	Point	dPdup( const Param& p );
	Point	dPdu(RPI* _p) { return dPduP(_p->P()); }

	Point	dPdvP( const Point& p );
	Point	dPdvp( const Param& p );
	Point	dPdv(RPI* _p) { return dPdvP(_p->P()); }

	RPIList	intersect ( const Ray& r );

	Point	randomOn();
	Point	randomIn();

};

#endif
