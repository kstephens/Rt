//
// Prim.h - class Prim
// KAS 91/06/25
//
#ifndef	__Prim_hh
#define	__Prim_hh

#include "Point.hh"
#include "Param.hh"
#include "Ray.hh"
#include "RPIList.hh"
#include "Xform.hh"

#define rnd() 0.0 // FIXME

class Shader;

class Prim {
  Prim *next;
friend	class Scene;
public:
  Xform  *xform;	// the prim -> world transform
  Shader *surface;// the surface shader
  Prim   *shadow;	// the prim that create shadows

  Prim() : xform(current_xform), surface(0) {
    shadow = this;
  }
virtual	~Prim() {}

//
// The following use the primitive's coordinate system
//
virtual	Point	P(const Param& _p) { return Point(0); }
virtual	Param	p(const Point& _p) { return Param(0); }

virtual	Point	Ngp(const Param& _p) { return dPdup(_p) ^ dPdvp(_p); }
virtual	Point	NgP(const Point& _p) { return dPduP(_p) ^ dPdvP(_p); }
virtual	Point	Ng(RPI* _p); // { return _p->dPdu() ^ _p->dPdv(); }

virtual	Point	dPdup(const Param& _p) { return Point(0); }
virtual	Point	dPduP(const Point& _p) { return dPdup(p(_p)); }
virtual	Point	dPdu(RPI* _p); // { return dPdup(_p->p()); }

virtual	Point	dPdvp(const Param& _p) { return Point(0); }
virtual	Point	dPdvP(const Point& _p) { return dPdvp(p(_p)); }
virtual	Point	dPdv(RPI* _p); // { return dPdvp(_p->p()); }

virtual	Point	dPdwp(const Param& _p) { return Ngp(_p); }
virtual	Point	dPdwP(const Point& _p) { return NgP(_p); }
virtual	Point	dPdw(RPI* _p) { return Ng(_p); }

virtual	RPIList	intersect( const Ray& r ) = 0;
virtual	int	intersects( const Ray& r );

virtual	Point	randomOn() { return P(Param(rnd(),rnd())); }
virtual	Point	randomIn() { return Point(0); }

//
// The following use the world coord sys
//
	RPIList	wintersect ( const Ray& r ) {
		return intersect ( xform->inverse_transform(r)); }
	int	wintersects( const Ray& r ) {
		return intersects ( xform->inverse_transform(r)); }
	Point	wrandomOn() {
		return xform->transform(randomOn()); }
	Point	wrandomIn() {
		return xform->transform(randomIn()); }
};

//
// Now we can include RPI
//
#include "RPI.hh"

#endif

