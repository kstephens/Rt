//
// Color.h - class RasterColor
// KAS 91/06/11
//
#ifndef	__RasterColor_hh
#define	__RasterColor_hh

#include "Raster/portable.h"

#include "Raster/RGB.hh"

#include <iostream>


#define	OP(op) \
friend	RasterColorRGB	operator op ( const RasterColorRGB& L, const RasterColorRGB& R ) { \
		return RasterColorRGB ( L.r op R.r, L.g op R.g, L.b op R.b, L.a ); } \
friend	RasterColorRGB	operator op ( const RasterColorRGB& L, const double& R ) { \
		return RasterColorRGB ( L.r op R, L.g op R, L.b op R, L.a ); } \
friend	RasterColorRGB	operator op ( const double& R, const RasterColorRGB& L ) { \
		return RasterColorRGB ( L.r op R, L.g op R, L.b op R, L.a ); } \

#define	AOP(op) \
	RasterColorRGB&	operator op ( const RasterColorRGB& R ) { \
		r op R.r; g op R.g; b op R.b; return *this; } \
	RasterColorRGB&	operator op ( const double& R ) { \
		r op R; g op R; b op R; return *this; } \


inline
double	abs(const double& x) {
	return x >= 0.0 ? x : -x;
}


class RasterColorRGB {
protected:
	double	r, g, b, a;
public:
	RasterColorRGB () { }
	RasterColorRGB ( const char* name, double i = 1.0, double A = 1.0 );
	RasterColorRGB ( U8 R, U8 G, U8 B, U8 A = 0xff ) : r(R / 255.9999), g(G / 255.9999), b(B / 255.9999), a(A / 255.9999) {}
	RasterColorRGB ( double R, double G, double B, double A = 1.0 ) :
		r(R), g(G), b(B), a(A) {}
	RasterColorRGB ( U8 i, U8 A = 0xff ) : r(i / 255.9999), a(A / 255.9999) { g = b = r; }
  RasterColorRGB ( double i, double A = 1.0 ) : r(i), g(i), b(i), a(A) { }
  RasterColorRGB ( const U8 *rgb )
  : r(rgb[0] / 255.9999), g(rgb[1] / 255.9999), b(rgb[2] / 255.9999) { }

	OP(+)
	OP(-)
	OP(/)
	OP(*)
	AOP(+=)
	AOP(-=)
	AOP(/=)
	AOP(*=)

	double	red() const { return r; }
	void	red( double R ) { r = R; }

	double	green() const { return g; }
	void	green( double G ) { g = G; }

	double	blue() const { return b; }
	void	blue( double B ) { b = B; }

	double	alpha() const { return a; }
	void	alpha( double A ) { a = A; }

	double		sum() const {
		return (r + g + b);
	}
	RasterColorRGB	abs() const {
		return RasterColorRGB(::abs(r), ::abs(g), ::abs(b), ::abs(a));
	}

  const double *begin() const { return &r; }
  const double *end() const { return &r + 4; }

  double min(double a, double b) const { return a < b ? a : b; }
  double max(double a, double b) const { return a > b ? a : b; }
  double clamp(double x, double m, double M) const { return max(m, min(M, x)); }

  RasterColorRGB& clamp()
  {
    r = clamp(r, 0, 1);
    g = clamp(g, 0, 1);
    b = clamp(b, 0, 1);
    a = clamp(a, 0, 1);
    return *this;
  }

};

#undef	OP
#undef	AOP

inline std::ostream& operator << (std::ostream &os, const RasterColorRGB &c)
{
  return os << "RasterColorRGB(" << c.red() << ", " << c.green() << ", " << c.blue() << ")";
}

class RasterColorGreyScale : public RasterColorRGB {
public:
	RasterColorGreyScale ( U8 i, U8 A = 0xff ) : RasterColorRGB (i, A) {}
	RasterColorGreyScale ( double i, double A = 1.0 ) : RasterColorRGB (i, A) {}
};

typedef	RasterColorRGB	RasterColor;

#endif

