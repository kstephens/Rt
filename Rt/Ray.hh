//
// Ray.hh - class Ray
// KAS 91/06/13
//
#ifndef	__Ray_hh
#define	__Ray_hh

#include "Point.hh"

class Ray {
public:
	Point	origin;
	Point	direction;

	Ray () {}
	Ray ( const Point& O, const Point& D ) : origin (O), direction(D) {}

	Ray	operator + ( scalar t ) const {
		return Ray ( origin + direction * t, direction ); }
	Ray&	operator += ( scalar t ) {
		origin += direction * t; return *this; }
	Point	operator [] ( scalar t ) const {
		return origin + direction * t; }
	//
	// Fix the ray to remove "acne"
	//
	Ray&	fix ( const Point& Ng ) {
		origin += Ng * ((direction % Ng > 0.0) ? 0.0001 : -0.0001);
		return *this; }
};

inline std::ostream & operator << (std::ostream & os, const Ray &r)
{
  return os << "Ray(" << r.origin << ", " << r.direction << ")";
}

#endif

