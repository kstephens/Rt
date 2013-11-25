//
// Plane.cc - class Plane
// KAS 91/06/29
//
#include "Plane.hh"
#include "EPSINF.hh"
#include "ri/rirand.h"

Point
Plane::P( const Param& p ) {
	Point	P;
	P[axis] = lo()[axis];
	P[u] = lo()[u] + size[u] * p.u;
	P[v] = lo()[v] + size[v] * p.v;
	return P;
}

Param
Plane::p( const Point& p ) {
	return Param (
		(p[u] - lo()[u]) / size[u],
		(p[v] - lo()[v]) / size[v]);
}

Point
Plane::NgP( const Point& p ) {
	Point N(0);
	N[axis] = 1.0;
	return N;
}
Point
Plane::Ngp( const Param& p ) {
	Point N(0);
	N[axis] = 1.0;
	return N;
}

Point
Plane::dPduP( const Point& p ) {
	Point N(0);
	N[u] = 1.0;
	return N;
}

Point
Plane::dPdup( const Param& p ) {
	Point N(0);
	N[u] = 1.0;
	return N;
}


Point
Plane::dPdvP( const Point& p ) {
	Point N(0);
	N[v] = 1.0;
	return N;
}
Point
Plane::dPdvp( const Param& p ) {
	Point N(0);
	N[v] = 1.0;
	return N;
}

RPIList
Plane::intersect ( const Ray& ray ) {
	RPIList	L;

	scalar	d = ray.direction[axis];
	if ( d != rt_EPSILON ) {
		scalar	l = lo()[axis];
		scalar t = (l - ray.origin[axis]) / d;
		Point P = ray[t];
		P[axis] = l;
		if ( isIn(P) ) {
			RPI*	i = new RPI ( ray, this, t );
			i->P(P);
			L.append(i);

			return L;
		}
	}

	return L;
}


Point
Plane::randomIn() {
	Point	p;

	p[axis] = 0.0;
	p[u] = lo()[u] + size[u] * RiRand();
	p[v] = lo()[v] + size[v] * RiRand();

	return p;
}
Point
Plane::randomOn() {
	return randomIn();
///
// IMPLEMENT !!!
//
/*
	scalar	r = RiRand();
	if ( r < 0.25 ) {
		return (lo()
	} else if ( r < 0.5 ) {
	} else if ( r < 0.75 ) {
	} else {
	}
*/

}
