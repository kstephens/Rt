//
// ConvexPolygon.cc - class ConvexPolygon
// KAS 91/06/30
//
#include "ConvexPolygon.hh"

ConvexPolygon::ConvexPolygon ( RtInt NVERTS, Point* POINTS ) : PolygonBase ( NVERTS, POINTS ) {
	invec = new Point[nverts];
	for ( RtInt i = 0; i < nverts; i ++ ) {
		RtInt	j = (i + 1) % nverts;
		invec[i] = N ^ (point[j] - point[i]);
		invec[i].normalize();
	}
}

int	ConvexPolygon::isIn(const Point& P ) {
	for ( RtInt i = 0; i < nverts; i ++ ) {
		if ( (P - point[i]) % invec[i] < 0.0 )
			return 0;
	}
	return 1;
}

RPIList	ConvexPolygon::intersect(const Ray& ray ) {
	RPIList	l = PolygonBase::intersect(ray);
	if ( ! l.isEmpty() ) {
		Point	P = l.begin()->P();

		if ( ! isIn(P) )
                  return RPIList();
	}
	return l;
}
