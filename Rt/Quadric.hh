//
// Quadric.hh - class Quadric
// KAS 91/06/29
//
#ifndef	__Quadric_hh
#define	__Quadric_hh

#include "ri/ri.h"
#include "Prim.hh"
#include "angle.hh"
#include "EPSINF.hh"

class Quadric : public Prim {
protected:
  angle thetamax;

  angle	utheta(RtFloat u) const {
    return u * thetamax;
  }
  RtFloat thetau(angle theta) const {
    return to_number(theta) / to_number(thetamax);
  }
  RtFloat thetax(angle theta) const {
    return cos(theta);
  }
  RtFloat dxdtheta(angle theta) const {
    return - sin(theta);
  }
  RtFloat thetay(angle theta) const {
    return sin(theta);
  }
  RtFloat dydtheta(angle theta) const {
    return cos(theta);
  }
  angle xytheta(RtFloat x, RtFloat y) const {
    if ( x == rt_EPSILON && y == rt_EPSILON )
      return radians(0.0);
    else
      return angle(y, x) + degrees(180.0);
  }
  virtual RPI *check(RPI *rpi) const {
    if ( ! isOn( rpi->P() ) ) {
      delete rpi; rpi = RPINULL;
    }
    return rpi;
  }

  virtual int isOn(const Point& p) const {
    if ( thetamax >= degrees(360.0) )
      return 1;
    else {
      return xytheta(p.x, p.y) <= thetamax;
    }
  }

  // a t^2 + b t + c == 0
  int quadradic(double a, double b, double c, double *t) {
    double r = b * b - 4 * a * c;
    if ( r < 0 ) {
      return 0;
    } else if ( r == 0 ) {
      if ( t )
        t[0] = - b / (2 * a);
      return 1;
    } else {
      if ( t ) {
        r = sqrt(r);
        t[0] = (-b - r) / (2 * a);
        t[1] = (-b + r) / (2 * a);
      }
      return 2;
    }
  }

  virtual int quadradic(const Ray &r, double *t) { return 0; }

  virtual RPIList intersect(const Ray& r)
  {
    RPIList list;
    double t[2];
    switch ( quadradic(r, t) ) {
    case 2:
      list.append( check( new RPI(r, this, t[0])));
      list.append( check( new RPI(r, this, t[1])));
      break;
    }
    return list;
  }

  virtual int intersects(const Ray& r)
  {
    return ! intersect(r).isEmpty();
  }

public:
  Quadric (RtFloat x) : thetamax(degrees(x)) {}
};

#endif
