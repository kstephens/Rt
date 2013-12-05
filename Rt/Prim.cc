//
// Prim.cc - class Prim
// KAS 91/06/29
//
#include "Prim.hh"
#include "RPI.hh"


Param Prim::p(RPI *rpi)
{
  return p(rpi->P());
}

Point
Prim::Ng(RPI* _p) { return _p->dPdu() ^ _p->dPdv(); }

Point
Prim::dPdu(RPI* _p) { return dPdup(_p->p()); }

Point
Prim::dPdv(RPI* _p) { return dPdvp(_p->p()); }


