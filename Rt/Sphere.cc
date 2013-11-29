//
// Sphere.cc - class Sphere
// KAS 91/06/25
//
#include "Sphere.hh"
#include "angle.hh"
#include "ri/RiRand.h"

Sphere::Sphere ( RtFloat RADIUS, RtFloat ZMIN, RtFloat ZMAX, RtFloat THETAMAX )
  : Quadric(THETAMAX),
    radius(RADIUS), radius2(RADIUS * RADIUS), zmin(ZMIN), zmax(ZMAX)
{
  if ( zmin <= -radius )
    phimin.asin(zmin / radius);
  else
    phimin = degrees(-90.0);

  if ( zmax >= radius )
    phimax.asin(zmax / radius);
  else
    phimax = degrees(90.0);

  phimax_minus_phimin = phimax - phimin;
}

int Sphere::isOn(const Point &P) const
{
  return P.z >= zmin && P.z <= zmax && Quadric::isOn(P);
}

Point	Sphere::P(const Param &p)
{
  angle	a = theta(p.u);
  angle	b = phi(p.v);
  scalar rxy = radius * cos(b);
  return Point(
          rxy * x(a),
          rxy * y(a),
          radius * sin(b));
}

Param Sphere::p(const Point &P)
{
  return Param(u(theta(P.x, P.y)), v(phiz(P.z)));
}

Point Sphere::Ngp(const Param& p)
{
  angle	a = theta(p.u);
  angle	b = phi(p.v);
  scalar cos_phi = cos(b);
  return Point(
          x(a) * cos_phi,
          y(a) * cos_phi,
          sin(b) );
}


Point	Sphere::NgP(const Point& P)
{
  return P * 2.0;
}

Point	Sphere::Ng(RPI* p)
{
  return p->P() * 2.0;
}


Point	Sphere::dPdup(const Param& p)
{
  angle	a = theta(p.u);
  angle	b = phi(p.v);
  scalar rxy = radius * cos(b) * to_radians(thetamax);
  return Point(
               rxy * dx(a),
               rxy * dy(a),
               0.0);
}

Point	Sphere::dPdvp(const Param& p)
{
  angle	a = theta(p.u);
  angle	b = phi(p.v);
  scalar rxy = radius * - sin(b) * to_radians(phimax_minus_phimin);
  return Point(
               rxy * x(a),
               rxy * y(a),
               radius * cos(b));
}

RPIList
Sphere::intersect( const Ray& r )
{
  Point	d = r.origin; d.negate();
  scalar d2 = d % d;
  scalar rdnorm = ~ r.direction;
  //
  // assure that r.direction is unit
  // (it may not be when I implement object transformations)
  //
  scalar h = (r.direction / rdnorm) % d;
  scalar i2 = d2 - h * h;

  if ( i2 < radius2 ) {
    scalar j = sqrt(radius2 - i2);
    RPIList	list;
    list.append( check( new RPI(r, this, (h - j) * rdnorm)));
    list.append( check( new RPI(r, this, (h + j) * rdnorm)));
    return list;
  } else {
    return RPIList();
  }
}


int
Sphere::intersects ( const Ray& r )
{
  Point	d = r.origin; d.negate();
  scalar	d2 = d % d;
  scalar	rdnorm = ~ r.direction;
  //
  // assure that r.direction is unit
  // (it may not be when I implement object transformations)
  //
  scalar	h = (r.direction / rdnorm) % d;
  scalar	i2 = d2 - h * h;

  return i2 < radius2;
}

Point
Sphere::random() const
{
  scalar sr = 2.0 * radius;
  Point	P;

  do {
    P = Point(
              (RiRand() - 0.5) * sr,
              (RiRand() - 0.5) * sr,
              (RiRand() - 0.5) * sr );
  } while ( P % P > radius2 );

  return P;
}

Point
Sphere::randomIn()
{
  return random();
}

Point
Sphere::randomOn()
{
  Point	P;
  
  do {
    (P = random()).normalize() * radius;
  } while ( ! isOn(P) );

  return P;
}

