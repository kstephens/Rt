//
// Box.hh - class Box
// KAS 91/06/29
//
#ifndef	__Box_hh
#define	__Box_hh

#include "Prim.hh"
#include "Bound.hh"

class Box : public Prim, public Bound {
	Point	center;
	Point	size;

	Point2	select ( float u );
	float	inverse_select( const Point2& p );

public:
	Box ( const Point& p1, const Point& p2 ) : Bound(p1, p2) {
		center = (p1 + p2) * 0.5;
		size = hi() - lo(); }
	Point	P(const Param& p);
	Param	p(const Point& p);

	Point	Ngp(const Param& p);
	Point	NgP(const Point& p);
	Point	Ng(RPI* p) { return NgP(p->P()); }

	Point	dPdup(const Param& p);
	Point	dPduP(const Point& p);
	Point	dPdu(RPI* p) { return dPduP(p->P()); }

	Point	dPdvp(const Param& p);
	Point	dPdvP(const Point& p);
	Point	dPdv(RPI* p) { return dPdvP(p->P()); }

	RPIList	intersect( const Ray& r );
	int	intersects( const Ray& r );

	Point	randomIn();
	Point	randomOn();
};

#endif
