//
// RPI.hh - class RPI (Ray-Primitive Intersection)
// KAS 91/03/10
//
#ifndef	__RPI_hh
#define	__RPI_hh

#include "Point.hh"
#include "Param.hh"
#include "Ray.hh"
#include "Prim.hh"
#include "Xform.hh"
#include "_RPI.hh"

class RPI : public _RPI {
public:
	RPI*	next() const { return (RPI*) _RPI::next(); }
	RPI*	next(RPI* n ) { return (RPI*) _RPI::next((RPI*) n); }

	Ray	r;	// the intersecting ray in primitive coord sys
	Prim*	prim;	// the intersected primitive

	scalar	t;	// distance of intersection along r.
private:
	//
	// transform a vector (bound to P) to world coordinates
	//
	Point	wv ( const Point& v ) {
		return prim->xform->transform(P() + v) - wP();
	}
		
	Point	_P;	// the point of intersection
	Point	_wP;	// " in world coordinates
	Param	_p;	// the parametric of intersection
	Point	_Ng;	// surface normal at intersection
	Point	_wNg;	// " in world coordinates
	Point	_dPdu;	// partial deriv. of P with respect to u
	Point	_wdPdu;	// " in world coordinates
	Point	_dPdv;	// partial deriv. of P with respect to u
	Point	_wdPdv;	// " in world coordinates
	Point	_dPdw;	// partial deriv. of P with respect to w
	Point	_wdPdw;	// " in world coordinates
	union	{
		unsigned flags;
		struct {
			unsigned
				know_P : 1,
				know_wP : 1,
				know_p : 1,
				know_Ng : 1,
				know_wNg : 1,
				know_dPdu : 1,
				know_wdPdu : 1,
				know_dPdv : 1,
				know_wdPdv : 1,
				know_dPdw : 1,
				know_wdPdw : 1,
				invert_Ng : 1;
		} f;
	}; // calculated attribute flags
public:
	RPI() : flags(0) {}
	RPI(scalar T) : t(T), flags(0) {}
	RPI( const Ray& R, Prim* P, scalar T) :
		r(R), prim(P), t(T), flags(0) {}

	//
	// linked list functions
	//
	RPI*	removeNext() {
		RPI* temp = next();
		next(next()->next());
		temp->next(RPINULL);
		return temp; }
	void	insertNext( RPI* p ) {
		p->next(next());
		next(p);
	}
	RPI*	findSmallest();
	RPI*	findSmallestPositive();
	RPI*	findBiggest();
	RPI*	findPositive();

	// Parameters at intersections.
	const Point&	P() {
		if ( ! f.know_P ) {
			_P = r[t];
			f.know_P = 1;
		}
		return _P; }

	void	P(const Point& p) { _P = p; f.know_P = 1; }

	const Point&	wP() {
		if ( ! f.know_wP ) {
			_wP = prim->xform->transform(P());
			f.know_wP = 1;
		}
		return _wP;
	}

	const Param&	p() {;
		if ( ! f.know_p ) {
			_p = prim->p(this);
			f.know_p = 1;
		}
		return _p; }

	void	p(const Param& m) { f.know_p = 1; _p = m; }

	const Point&	Ng() {
		if ( ! f.know_Ng ) {
			_Ng = prim->Ng(this);
			f.know_Ng = 1;
			if ( f.invert_Ng )
				_Ng.negate();
		}
		return _Ng;
	}
	void	Ng(const Point& p) {
		f.know_Ng = 1; f.invert_Ng = 0; _Ng = p; }

  const Point &wNg() {
    if ( ! f.know_wNg ) {
      _wNg = wv(Ng());
      f.know_wNg = 1;
    }
    return _wNg;
  }

	void	invertNg() {
		f.invert_Ng = ~ f.invert_Ng;
		if ( f.know_Ng )
                  _Ng.negate();
		if ( f.know_wNg )
                  _wNg.negate();
	}
	int	Nginverted() { return f.invert_Ng; }

#define	INTERFACE(X) \
	const Point&	X () { \
		if ( ! f.know_##X ) { _##X = prim->X(this); f.know_##X = 1; } \
		return _##X; } \
	const Point&	w##X () { \
		if ( ! f.know_w##X ) { _w##X = wv(X()); f.know_w##X = 1; } \
		return _w##X; } \
	void	X ( const Point& x ) { _##X = x; f.know_##X = 1; }

	INTERFACE(dPdu);
	INTERFACE(dPdv);
	INTERFACE(dPdw);

#undef	INTERFACE

};

inline std::ostream & operator << (std::ostream & os, const RPI &rpi)
{
  return os << "RPI(" << rpi.r << ", " << (void*) rpi.prim << ", " << rpi.t << ")";
}

#endif

