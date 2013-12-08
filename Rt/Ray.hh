//
// Ray.hh - class Ray
// KAS 91/06/13
//
#ifndef	__Ray_hh
#define	__Ray_hh

#include "Point.hh"
#include "vector.hh"

class Ray {
public:
	Point	origin;
	vector	direction;

	Ray () {}
	Ray ( const Point& O, const vector& D ) : origin (O), direction(D) {}

	Ray	operator + ( scalar t ) const {
		return Ray ( origin + direction * t, direction ); }
	Ray&	operator += ( scalar t ) {
		origin += direction * t; return *this; }
	Point	operator [] ( scalar t ) const {
		return origin + direction * t; }

  Ray &normalize() {
    direction.normalize();
    return *this;
  }

  // Distance of p as projected on to this ray.
  scalar distance_to(const point &p) const {
    vector V = p - origin;
    scalar Vl = 1.0 / ~V;
    scalar Dl = 1.0 / ~direction;
    return ((V * Vl) % (direction * Dl)) * Dl;
  }

  // Move the ray away from origin along N.
  Ray& fix(const vector &N)
  {
    // vector n = unit(N);
    origin += N * (N % direction > 0 ? 0.00001 : -0.00001);
    return *this;
  }
};

inline std::ostream & operator << (std::ostream & os, const Ray &r)
{
  return os << "Ray(" << r.origin << ", " << r.direction << ")";
}

#endif

