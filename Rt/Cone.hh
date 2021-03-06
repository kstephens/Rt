//
// Cone.hh
// KAS 91/06/29
//
#ifndef	__Cone_hh
#define	__Cone_hh

#include "Quadric.hh"

class Cone : public Quadric {
  scalar	height, height2; // height * height
  scalar	radius, radius2;	// radius * radius

	int	isOn(const Point& p) const;

	Point	random() const;
public:
	Cone( scalar HEIGHT, scalar RADIUS, scalar THETAMAX );

	Point	P(const Param& p);
	Param	p(const Point& p);

#if 0
	Point	Ngp(const Param& p);
	Point	NgP(const Point& p);
	Point	Ng(RPI* p);
#endif

	vector	dPdup(const Param& p);
	vector	dPdvp(const Param& p);

  int quadradic(const Ray &r, scalar *t);

	Point	randomIn();
	Point	randomOn();

};

#endif
