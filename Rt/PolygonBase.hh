//
// PolygonBase.hh - class PolygonBase
// KAS 91/06/29
//
#ifndef	__PolygonBase_hh
#define	__PolygonBase_hh

#include "Bound.hh"
#include "Prim.hh"
#include "ri/ri.h" /* RtInt */

class PolygonBase : public Prim {
protected:
	RtInt	nverts;
	Point	N;	// the polygon's plane normal
	Point*	point;	// point list
	Bound	bound;	// the bounds of the polygon
	scalar	D;
	int	X, Y, Z;	// virtual coordinate tags 

virtual	int	isIn(const Point& P) = 0;

	PolygonBase ( RtInt NVERTS, Point* POINTS );
public:
	Point	P(const Param& p);
	Param	p(const Point& p);

	Point	Ng(RPI* p);
	Point	dPdu(RPI* p);
	Point	dPdv(RPI* p);

	RPIList	intersect(const Ray& ray);

	Point	pointOn();
};

#endif
