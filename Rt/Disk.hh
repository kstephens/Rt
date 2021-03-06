//
// Disk.hh - class Disk
// KAS 91/06/29
//
#ifndef	__Disk_hh
#define	__Disk_hh

#include "Quadric.hh"

class Disk : public Quadric {
	scalar radius;
	scalar	radius2; // radius * radius
	scalar	height;
  Point _Ng;

public:
  Disk ( scalar HEIGHT, scalar RADIUS, scalar THETAMAX );
	Point	P(const Param& p);
	Param	p(const Point& P);

	normal Ngp(const Param& p);
	normal NgP(const Point& P);
	normal Ng(RPI* p);

	vector dPdup(const Param& p);
	vector dPdvp(const Param& p);

	RPIList	intersect( const Ray& r );

	Point	randomIn();
	Point	randomOn();

};

#endif
