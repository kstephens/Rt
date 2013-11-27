//
// Cone.cc - class Cone
// KAS 91/06/25
//
#include "Cone.hh"
#include "EPSINF.hh"
#include "ri/RiRand.h"

Cone::Cone ( RtFloat HEIGHT, RtFloat RADIUS, RtFloat THETAMAX ) :
	height(HEIGHT), radius(RADIUS), radius2(RADIUS * RADIUS), Quadric(THETAMAX) {
}

int	Cone::isOn(const Point&P) const {
	return P.z >= 0.0 && P.z <= height && Quadric::isOn(P);
}

Point	Cone::P(const Param& p) {
	angle	theta = utheta(p[0]);
	scalar	rxy = radius * (1.0 - p[1]);

	return Point(
		rxy * thetax(theta),
		rxy * thetay(theta),
		p[1] * height);
}

Param	Cone::p(const Point& p) {
  return	Param(thetau(xytheta(p.x, p.y)), p.z / height);
}


Point	Cone::Ngp(const Param& p) {
	angle	theta = utheta(p[0]);
	return Point(
		radius * thetax(theta),
		radius * thetay(theta),
		height);
}


Point	Cone::NgP(const Point& p) {
	Point P = p;
	((Point2&) P).normalize() * radius;
	P.z = height;
	return	P;
}

Point	Cone::Ng(RPI* p) {
	return NgP(p->P());
}


Point	Cone::dPdup(const Param& p) {
	angle	theta = utheta(p.u);
	RtFloat rxy = radius * thetamax.radians();

	return Point(
		rxy * dxdtheta(theta),
		rxy * dydtheta(theta),
		0.0 );
}

Point	Cone::dPdvp(const Param& p) {
	angle	theta = utheta(p.u);
	scalar	rxy = - radius;
	return	Point (
		rxy * thetax(theta),
		rxy * thetay(theta),
		height );
}

RPIList
Cone::intersect( const Ray& r ) {
	Point	d = r.origin; d.negate();
	scalar	d2 = d % d;
	scalar	rdnorm = ~ r.direction;
	//
	// assure that r.direction is unit
	// (it may not be when I implement object transformations)
	//
	scalar	h = (r.direction / rdnorm) % d;
	scalar	i2 = d2 - h * h;

	if ( i2 < radius2 ) {
		scalar j = sqrt(radius2 - i2);
		RPIList	list;
		list.append( check( new RPI(r, this, (h - j) * rdnorm)));
		list.append( check( new RPI(r, this, (h + j) * rdnorm)));
		return list;
	} else {
		return RPIList();
	}
}


inline
Point
Cone::random() const {
	scalar	sr = 2.0 * radius;
	Point	P;

	do {
		P = Point (
			(RiRand() - 0.5) * sr,
			(RiRand() - 0.5) * sr,
			RiRand());
	} while ( ((Point2&)P) % ((Point2&) P) > radius2 * P.z);

	P.z = (1.0 - P.z) * height;
	return P;
}

Point
Cone::randomIn() {
	return random();
}

Point
Cone::randomOn() {
	Point	P;

	do {
		P = random();
		((Point2&) P).normalize() * radius * (1.0 - (P.z / height));
	} while ( ! isOn(P) );

	return P;
}



