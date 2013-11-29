//
// Prim.h - class Prim
// KAS 91/06/25
//
#ifndef	__Prim_hh
#define	__Prim_hh

#include "Geometry.hh"

class Prim : public Geometry {
public:
  Prim() : Geometry() { }
  virtual ~Prim() {}

  // In the primitive's coordinate system:
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

virtual	RPIList	intersect(const Ray &r) = 0;

  virtual Point randomOn() { return P(Param(rnd(),rnd())); } // Might not have regular distribution.
  virtual Point randomIn() { return Point(0); }
};

//
// Now we can include RPI
//
#include "RPI.hh"

#endif

