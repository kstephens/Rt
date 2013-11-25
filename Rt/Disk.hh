//
// Disk.hh - class Disk
// KAS 91/06/29
//
#ifndef	__Disk_hh
#define	__Disk_hh

#include "Quadric.hh"

class Disk : public Quadric {
	RtFloat radius;
	RtFloat	radius2; // radius * radius
	RtFloat	height;

	Point	random() const;
public:
  Disk ( RtFloat HEIGHT, RtFloat RADIUS, RtFloat THETAMAX );
	Point	P(const Param& p);
	Param	p(const Point& p);

	Point	Ngp(const Param& p);
	Point	NgP(const Point& p);
	Point	Ng(RPI* p);

	Point	dPdup(const Param& p);

	Point	dPdvp(const Param& p);

	RPIList	intersect( const Ray& r );

	Point	randomIn();
	Point	randomOn();

};

#endif
