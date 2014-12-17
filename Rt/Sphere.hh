//
// Sphere.hh - class Sphere
// KAS 91/06/29
//
#ifndef	__Sphere_hh
#define	__Sphere_hh

#include "Quadric.hh"

class Sphere : public Quadric {
  RtFloat radius;
  RtFloat radius2; // radius * radius
  RtFloat zmin, zmax;
  angle	phimin, phimax;	// zmin, zmax
  angle phimax_minus_phimin;	// phimax - phimin

  angle phi(scalar v) const {
    return phimin + phimax_minus_phimin * v;
  }
  scalar v(angle phi) const {
    return (phi - phimin) / phimax_minus_phimin;
  }
  angle	phiz(scalar z) const {
    angle phi;
    phi.asin(z / radius);
    return phi;
  }
  scalar z(angle phi) const {
    return radius * sin(phi);
  }

  int isOn(const Point& p) const;
  Point	random() const;

public:
  Sphere ( RtFloat RADIUS, RtFloat ZMIN, RtFloat ZMAX, RtFloat THETAMAX ) ;
  Point	P(const Param& p);
  Param	p(const Point& p);

  Point	Ngp(const Param& p);
  Point	NgP(const Point& p);
  Point	Ng(RPI* p);

  Point	dPdup(const Param& p);
  Point	dPdvp(const Param& p);

  RPIList intersect( const Ray& r );
  int 	intersects( const Ray& r );

  Point	randomIn();
  Point	randomOn();

};

#endif
