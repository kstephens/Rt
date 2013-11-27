//
// Disk.cc - class Disk
// KAS 91/06/25
//
#include "Disk.hh"
#include "ri/RiRand.h"

Disk::Disk ( RtFloat RADIUS, RtFloat H, RtFloat THETAMAX ) :
  radius(RADIUS), radius2(RADIUS * RADIUS), height(H), Quadric(THETAMAX) {
}

Point	Disk::P(const Param& p) {
	angle	theta = utheta(p.u);
	float	rxy = radius * (1.0 - p.v);
	
	return Point(
		rxy * thetax(theta),
		rxy * thetay(theta),
		height);
}

Param	Disk::p(const Point& p) {
  scalar v = 1.0 - (~ ((Point2&) p) / radius);
	return	Param(thetau(xytheta(p.x, p.y)), v);
}


Point	Disk::Ngp(const Param& p) {
	return	Point(0.0, 0.0, 1.0);
}


Point	Disk::NgP(const Point& p) {
	return	Point(0.0, 0.0, 1.0);
}

Point	Disk::Ng(RPI* p) {
	return	Point(0.0, 0.0, 1.0);
}


Point	Disk::dPdup(const Param& p) {
	angle	theta = utheta(p.u);
	RtFloat rxy = radius * to_number(thetamax);

	return Point(
		rxy * dxdtheta(theta),
		rxy * dydtheta(theta),
		0.0 );
}

Point	Disk::dPdvp(const Param& p) {
  angle theta = utheta(p.u);
	scalar	rxy = - radius;
	return	Point (
		radius * thetax(theta),
		radius * thetay(theta),
		0.0);

}

RPIList
Disk::intersect( const Ray& r ) {
        if ( r.direction.z == rt_EPSILON )
		return RPIList();

	float	t = (height - r.origin.z) / r.direction.z;
	Point	p = r[t];
	p.z = height;
	if ( ((Point2&) p) % ((Point2&) p) <= radius2 && isOn(p) ) {
		RPIList	list;
		RPI*	rpi = new RPI(r, this, t);
		rpi->P(p);
		list.append( rpi);
		return list;
	} else {
		return RPIList();
	}
}

Point
Disk::random() const {
	scalar	sr = 2.0 * radius;
	Point	P;

	do {
		P = Point (
			(RiRand() - 0.5) * sr,
			(RiRand() - 0.5) * sr,
			height);
	} while ( ((Point2&) P) % ((Point2&) P) > radius2 );

	return P;
}

Point
Disk::randomIn() {
	return randomOn();
}

Point
Disk::randomOn() {
	Point	P;

	do {
		P = random();
	} while ( ! isOn(P) );

	return P;
}



