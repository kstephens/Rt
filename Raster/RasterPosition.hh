//
// RasterPosition.hh - class RasterPosition
// KAS 91/06/11
//
#ifndef	__Raster_RasterPosition_hh
#define	__Raster_RasterPosition_hh

#define	POS	RasterPosition

#define	OP(op) \
friend	POS	operator op ( const POS& l, const POS& r ) { \
	return POS ( l.x op r.x, l.y op r.y ); } \

#define AOP(aop) \
	POS&	operator aop ( const POS& r ) { \
	x aop r.x; y aop r.y; return *this; } \

#define	LOP(lop,joinop) \
friend	int	operator lop ( const POS& l, const POS& r ) { \
	return (l.x lop r.x) joinop (l.y lop r.y); } \

inline short abs ( short x ) { return (x >= 0) ? x : - x; }
inline short sign ( short x ) { return (x > 0) ? 1 : (x < 0) ? -1 : 0; }

class POS {
public:
	short	x, y;
	POS () {}
	POS ( short X, short Y ) : x(X), y(Y) {}
	POS ( short S ) : x(S), y(S) {}

	short&	operator [](int i) { return (&x)[i]; }
	short	operator [](int i) const { return (&x)[i]; }

	POS&	negate() { x = -x; y = -y; return *this; }
	POS	operator -() const { return POS(-x, -y); }

	OP(+)
	OP(-)
	OP(*)
	OP(/)
	AOP(+=)
	AOP(-=)
	AOP(*=)
	AOP(/=)
	LOP(==,&&)
	LOP(!=,||)

	POS	abs () const { return POS(::abs(x), ::abs(y)); }
	POS	sign () const { return POS(::sign(x), ::sign(y)); }
};

#undef LOP
#undef AOP
#undef OP

#endif
