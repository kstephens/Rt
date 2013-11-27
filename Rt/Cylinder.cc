//
// Cylinder.cc - class Cylinder
// KAS 91/06/25
//
#include "Cylinder.hh"
#include "ri/RiRand.h"

Cylinder::Cylinder(RtFloat RADIUS, RtFloat ZMIN, RtFloat ZMAX, RtFloat THETAMAX) :
  radius(RADIUS), radius2(RADIUS * RADIUS), zmin(ZMIN), zmax(ZMAX), Quadric(THETAMAX)
{
  zmax_minus_zmin = zmax - zmin;
}

int Cylinder::isOn(const Point &P) const
{
  return P.z >= zmin && P.z <= zmax && Quadric::isOn(P);
}

Point Cylinder::P(const Param &p)
{
  angle	theta = utheta(p[0]);

  return Point(
               radius * thetax(theta),
               radius * thetay(theta),
               vz(p.v));
}

Param Cylinder::p(const Point &p)
{
  return Param(thetau(xytheta(p.x, p.y)), zv(p.z));
}


Point Cylinder::Ngp(const Param& p)
{
  angle	theta = utheta(p[0]);
  scalar rxy = radius * 2.0;
  return Point(
               rxy * thetax(theta),
               rxy * thetay(theta),
               0.0 );
}


Point Cylinder::NgP(const Point &p)
{
  Point	P = p;
  ((Point2&) P).normalize() * (radius * 2.0);
  P.z = 0.0;
  return P;
}

Point Cylinder::Ng(RPI* p)
{
  return NgP(p->P());
}


Point Cylinder::dPdup(const Param &p)
{
  angle	theta = utheta(p[0]);
  scalar rxy = radius * thetamax.radians();

  return Point(
               rxy * dxdtheta(theta),
               rxy * dydtheta(theta),
               0.0 );
}

Point Cylinder::dPdvp(const Param &p)
{
  return Point (
                0.0,
		0.0,
		zmax_minus_zmin);
}

int
Cylinder::quadradic(const Ray &r, double *t)
{
  return
    Quadric::quadradic(r.direction.x * r.direction.x + r.direction.y * r.direction.y,
                       2 * (r.origin.x * r.direction.x + r.origin.y * r.direction.y),
                       r.origin.x * r.origin.x + r.origin.y * r.origin.y - radius2,
                       t);
}

RPIList
Cylinder::intersect( const Ray& r )
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

int
Cylinder::intersects ( const Ray& r )
{
  return ! intersect(r).isEmpty();
}

Point
Cylinder::random() const
{
  scalar sr = 2.0 * radius;
  Point	P;

  do {
    P = Point(
              (RiRand() - 0.5) * sr,
              (RiRand() - 0.5) * sr,
              RiRand());
  } while ( ((Point2&) P) % ((Point2&) P) > radius2 );

  P.z = zmin + P.z * zmax_minus_zmin;

  return P;
}

Point
Cylinder::randomIn()
{
  return random();
}

Point
Cylinder::randomOn()
{
  Point	P;

  do {
    P = random();
    ((Point2&) P).normalize() *= radius;
  } while ( ! isOn(P) );
  
  return P;
}



