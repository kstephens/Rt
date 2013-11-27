//
// Xform.hh - class Xform
// KAS 91/06/29
//
#ifndef	__Xform_hh
#define	__Xform_hh

#include "Point.hh"
#include "Ray.hh"
#include "point_def.hh"
#include "matrix4_4.hh"

class Xform {
protected:
	matrix4_4	mat;
	matrix4_4	invmat;
	unsigned	know_invmat : 1;
public:
  Xform ()
  : know_invmat(1)
  {
    mat.identity();
    invmat.identity();
  }
	Xform ( const matrix4_4& m ) : mat(m), know_invmat(0) {}
	Xform&	operator = ( const matrix4_4& m ) {
		mat = m;
		know_invmat = 0;
		return *this;
	}
	Xform&	concat ( const matrix4_4& m ) {
		mat *= m;
		know_invmat = 0;
		return *this;
	}
	Point	transform( const Point& v ) const {
		return v * mat;
	}
	Point inverse_transform ( const Point& v ) {
		if ( ! know_invmat ) {
			invmat = ~ mat;
			know_invmat = 1;
		}
		return v * invmat;
	}
	Ray	transform ( const Ray& r ) const {
		Point p0t = transform(r.origin);
		Point p1 = r.origin + r.direction;
		return Ray ( p0t, transform(p1) - p0t );
	}
	Ray	inverse_transform ( const Ray& r ) {
		Point p0t = inverse_transform(r.origin);
		Point p1 = r.origin + r.direction;
		return Ray ( p0t, inverse_transform(p1) - p0t );
	}
  friend std::ostream& operator << (std::ostream &os, const Xform &x);
};

#include "point_undef.hh"

inline std::ostream& operator << (std::ostream &os, const Xform &x)
{
  return os << "Xform(" << x.mat << ")";
}

#endif

