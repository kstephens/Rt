//
// Point.hh - class Point
// KAS 91/06/29
//
#ifndef	__Point_hh
#define	__Point_hh

#include "point_def.hh"
#include "vector_imp.hh"
#include "point_undef.hh"
typedef point Point;
typedef point2 Point2;

inline
Point	floor ( const Point& p ) {
	return Point ( floor(p.x), floor(p.y), floor(p.z)); }

inline
Point	fraction ( const Point& p ) { return p - floor(p); }

inline
Point	normalize( const Point& p ) { return p.unit(); }

inline
Point	faceforward ( const Point& N, const Point& I ) {
	return (N % I > 0.0) ? - N : N; }

inline
Point	reflect ( const Point& I, const Point& N ) {
	return I - (2.0 * (I % N) * N);
}

inline
Point	refract ( const Point& I, const Point& N, float eta ) {
	scalar	IdotN = I % N;
	scalar	k = 1.0 - eta * eta * (1.0 - IdotN * IdotN);
	return k < 0 ? Point(0) : eta * I + (eta * IdotN - sqrt(k)) * N;
}

#endif

