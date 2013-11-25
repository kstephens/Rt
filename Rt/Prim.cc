//
// Prim.cc - class Prim
// KAS 91/06/29
//
#include "Prim.hh"
#include "RPI.hh"

Point
Prim::Ng(RPI* _p) { return _p->dPdu() ^ _p->dPdv(); }

Point
Prim::dPdu(RPI* _p) { return dPdup(_p->p()); }

Point
Prim::dPdv(RPI* _p) { return dPdvp(_p->p()); }

int
Prim::intersects ( const Ray& ray ) {
	RPIList	rpi = intersect(ray);
	RPI*	i = rpi.begin();
	rpi.delete_all();
	return i != RPINULL;
}


