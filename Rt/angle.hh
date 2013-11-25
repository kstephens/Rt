//
// angle.hh - class angle, degrees, radians
// KAS 91/06/25
//
#ifndef	__angle_hh
#define	__angle_hh

#include "scalar.h"
#include <math.h>
#include <iostream>

class	angle {
//
// Implement as radian, because C math library trig functions
// expects them.
//
	scalar	r;
	angle ( scalar a ) { r = a; }
  static  angle _radians(scalar a) { return angle(a); }
  static  angle _degrees(scalar a) { return angle(M_PI / 180.0 * a); }

public:
	angle ( ) {}
	angle ( scalar y, scalar x ) { r = ::atan2((double) y, (double) x); }

  scalar number() const { return r; }
  scalar radians() const { return r; }
  scalar degrees() const { return 180.0 / M_PI * r; }

	void	asin ( scalar y ) { r = ::asin ( (double) y ); }
	void	acos ( scalar x ) { r = ::acos ( (double) x ); }
	void	atan ( scalar y, scalar x ) { r = ::atan2 ( (double) y, (double) x ); }
	void	atan ( scalar yx ) { r = ::atan( (double) yx ); }

	angle&	operator = ( const angle& l ) {
		r = l.r;
		return *this;
	}

	angle	operator -() const { return angle( - r ); }
	angle&	negate () { r = - r; return *this; }

#define	OP(op) \
friend	angle 	operator op ( const angle& L, const angle& R ) { \
		return angle ( L.r op R.r ); } \
	angle&	operator op##= ( const angle& R ) { \
		r op##= R.r; return *this; } 

	OP(+)
	OP(-)

#undef OP

#define	OP(op) \
friend	angle	operator op ( const angle& L, scalar s ) { \
		return angle ( L.r op s ); } \
friend	angle 	operator op ( scalar s, const angle& R ) { \
		return angle ( s op R.r ); } \
friend	angle 	operator op ( const angle& L, const angle& R ) { \
		return angle ( L.r op R.r ); } \
	angle&	operator op##= ( const angle& R ) { \
		r op##= R.r; return *this; } \
	angle&  operator op##= ( scalar s ) { \
		r op##= s; return *this; }

	OP(/)
	OP(*)

#undef OP

#define	OP(op) \
friend	int	operator op ( const angle& L, const angle& R ) { \
		return L.r op R.r; } 

	OP(==)
	OP(!=)
	OP(<)
	OP(<=)
	OP(>)
	OP(>=)

#undef	OP

        friend angle degrees(scalar a);
  friend angle degrees(scalar a);
  friend angle radians(scalar a);
  friend scalar to_radians(const angle &a);
  friend scalar to_degrees(const angle &a);
  friend scalar	sin (const angle &a );
  friend scalar	cos (const angle &a );
  friend scalar	tan (const angle &a );

};

inline angle degrees(scalar a) { return angle::_degrees(a); }
inline angle radians(scalar a) { return angle::_radians(a); }

inline scalar to_number(const angle &a) { return a.number(); }
inline scalar to_radians(const angle &a) { return a.radians(); }
inline scalar to_degrees(const angle &a) { return a.degrees(); }
inline scalar	sin (const angle &a )  { return (scalar) ::sin ( (double) a.radians() ); }
inline scalar	cos (const angle &a )  { return (scalar) ::cos ( (double) a.radians() ); }
inline scalar	tan (const angle &a )  { return (scalar) ::tan ( (double) a.radians() ); }


inline std::ostream&	operator << ( std::ostream& os, const angle &x ) {
  return os << "degrees(" << to_degrees(x) << ")";
}

#endif	/* angle.h */
