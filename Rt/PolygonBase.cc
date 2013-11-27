//
// PolygonBase.cc - class PolygonBase
// KAS 91/06/29
//
#include "PolygonBase.hh"
#include "ri/RiRand.h"

PolygonBase::PolygonBase ( RtInt NVERTS, Point* POINTS ) : nverts(NVERTS) {
	point = new Point[nverts];
	Point	p1p0 = POINTS[1] - POINTS[0];
	int	Nnotfound = 1;

	for ( RtInt i = 0; i < nverts; i ++ ) {
		bound.add( point[i] = POINTS[i] );
		//
		// find two non-colinear segments to compute normal
		//
		if ( i > 2 && Nnotfound ) {
			N = p1p0 ^ (point[i] - point[0]);
			if ( N.x != rt_EPSILON || N.y != rt_EPSILON || N.z != rt_EPSILON )
				Nnotfound = 0;
		}
	}

	//
	// Make sure the surface normal is not perpendicular to the "Z" axis!
	//
	if ( N.z != rt_EPSILON ) {
		X = 0;
		Y = 1;
		Z = 2;
	} else if ( N.x != rt_EPSILON ) {
		X = 1;
		Y = 2;
		Z = 0;
	} else /* if ( N.y != rt_EPSILON ) */ {
		X = 2;
		Y = 0;
		Z = 1;
	}

	//
	// A = N[X]
	// B = N[Y]
	// C = N[Z]
	// D = A * x1 + B * Y1 + C * z1
	//
	// Ax + By + Cz - D = 0
	//
	D = N % point[0];
}

Point	PolygonBase::P( const Param& p ) {
	Point	P;
	P[X] = p[0];
	P[Y] = p[1];
	P[Z] = (N[X] * p[0] + N[Y] * p[1] - D) / N[Z];
	return P;
}

Param	PolygonBase::p(const Point& p ) {
	return Param(p.x, p.y);
}

Point	PolygonBase::Ng(RPI* p) {
	return N;
}

//
// I think this is right...
//
Point	PolygonBase::dPdu(RPI* p) {
	Point	P;
	P[X] = N[Z];
	P[Y] = 0.0;
	P[Z] = - N[X];
	return P;
}

//
// I think this is right...
//
Point	PolygonBase::dPdv(RPI* p) {
	return Point( 0.0, - N.z, N.y );
	Point	P;
	P[X] = 0.0;
	P[Y] = - N[Z];
	P[Z] = N[Y];
	return P;
}

RPIList	PolygonBase::intersect(const Ray& ray) {
//
// Plane has a normal of N, and contains P0 and some point P.
//
//	N . (P - P0) = 0	for all planes
//
// Ray has an origin at Ro and a direction Rd.
//
//	P = Ro + Rd * t 	for all rays
//
// Therefore:
//
//	N . (P - P0) = 0
//
//      N . ((Ro + Rd * t) - P0) = 0
//
//	Nx * (Rox + Rdx * t - P0x) +
//	Ny * (Roy + Rdy * t - P0y) +
//	Nz * (Roz + Rdz * t - P0z) = 0
//
//	t * (N . Rd) = - (N . (Ro - P0))
//
//	     N . (P0 - Ro)
//	t = ---------------
//	        N . Rd
//
//	3 subtractions
//	4 additions
//	6 multiplies
//	1 divide
//
	float	N_dot_Rd = N % ray.direction;
	float	N_dot_P0_minus_Ro = N % (point[0] - ray.origin);

	//
	// Ray is parallel to plane
	//
	if ( N_dot_P0_minus_Ro == rt_EPSILON )
		return RPIList();

	float	t = N_dot_P0_minus_Ro / N_dot_Rd;

	return RPIList(1, ray, this, t);
}

Point	PolygonBase::pointOn() {
	Point	pnt;
	do {
		Param	p;
		p.u = bound.lo().x + (bound.hi().x - bound.lo().x) * RiRand();
		p.v = bound.hi().y + (bound.hi().y - bound.lo().y) * RiRand();
		pnt = P(p);
	} while ( ! isIn(pnt) );
	return pnt;
}
		
