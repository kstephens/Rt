//
// Cylinder.hh - class Cylinder
// KAS 91/06/29
//
#ifndef	__Cylinder_hh
#define	__Cylinder_hh

#include "Quadric.hh"

class Cylinder : public Quadric {
  scalar radius;
  scalar radius2; // radius * radius
  scalar zmin, zmax;
  scalar zmax_minus_zmin;	// zmax - zmin

  scalar zv(scalar v) const { // Return z(v).
    return zmin + v * zmax_minus_zmin;
  }
  scalar vz(scalar z) const { // Return v(z).
    return (z - zmin) / zmax_minus_zmin;
  }

  int isOn(const Point &p) const;
  Point	random() const;

  int quadradic(const Ray &r, double *t2);

public:
  Cylinder(RtFloat RADIUS, RtFloat ZMIN, RtFloat ZMAX, RtFloat THETAMAX);
  Point	P(const Param& p);
  Param	p(const Point& p);
  
  Point	Ngp(const Param& p);
  Point	NgP(const Point& p);
  Point	Ng(RPI* p);

  Point	dPdup(const Param& p);
  Point	dPdvp(const Param& p);

  Point	randomIn();
  Point	randomOn();
};

#endif
