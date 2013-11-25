//
// ConvexPolygon.hh
// KAS 91/06/30
//
#ifndef	__ConvexPolygon_hh
#define	__ConvexPolygon_hh

#include "PolygonBase.hh"

class ConvexPolygon : public PolygonBase {
	Point*	invec;	// vector that point into the polygon's interior
	int	isIn(const Point& p );
public:
	ConvexPolygon ( RtInt NVERTS, Point* POINTS );

	RPIList	intersect(const Ray& ray);
};

#endif
