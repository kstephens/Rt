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
	double	r;
	angle ( double a ) { r = a; }
  static  angle _radians(double a) { return angle(a); }
  static  angle _degrees(double a) { return angle(M_PI / 180.0 * a); }

public:
	angle ( ) {}
	angle ( double y, double x ) { r = ::atan2((double) y, (double) x); }

  double number() const { return r; }
  double radians() const { return r; }
  double degrees() const { return 180.0 / M_PI * r; }

	void	asin ( double y ) { r = ::asin ( (double) y ); }
	void	acos ( double x ) { r = ::acos ( (double) x ); }
	void	atan ( double y, double x ) { r = ::atan2 ( (double) y, (double) x ); }
	void	atan ( double yx ) { r = ::atan( (double) yx ); }

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
friend	angle	operator op ( const angle& L, double s ) { \
		return angle ( L.r op s ); } \
friend	angle 	operator op ( double s, const angle& R ) { \
		return angle ( s op R.r ); } \
friend	angle 	operator op ( const angle& L, const angle& R ) { \
		return angle ( L.r op R.r ); } \
	angle&	operator op##= ( const angle& R ) { \
		r op##= R.r; return *this; } \
	angle&  operator op##= ( double s ) { \
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

        friend angle degrees(double a);
  friend angle degrees(double a);
  friend angle radians(double a);
  friend double to_radians(const angle &a);
  friend double to_degrees(const angle &a);
  friend double	sin (const angle &a );
  friend double	cos (const angle &a );
  friend double	tan (const angle &a );

};

inline angle degrees(double a) { return angle::_degrees(a); }
inline angle radians(double a) { return angle::_radians(a); }

inline double to_number(const angle &a) { return a.number(); }
inline double to_radians(const angle &a) { return a.radians(); }
inline double to_degrees(const angle &a) { return a.degrees(); }
inline double	sin (const angle &a )  { return (double) ::sin ( (double) a.radians() ); }
inline double	cos (const angle &a )  { return (double) ::cos ( (double) a.radians() ); }
inline double	tan (const angle &a )  { return (double) ::tan ( (double) a.radians() ); }


inline std::ostream&	operator << ( std::ostream& os, const angle &x ) {
  return os << "degrees(" << to_degrees(x) << ")";
}

#endif	/* angle.h */
