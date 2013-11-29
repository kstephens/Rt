//
// Cylinder.cc - class Cylinder
// KAS 91/06/25
//
#include "Cylinder.hh"
#include "ri/RiRand.h"

Cylinder::Cylinder(RtFloat RADIUS, RtFloat ZMIN, RtFloat ZMAX, RtFloat THETAMAX)
  : Quadric(THETAMAX),
    radius(RADIUS), radius2(RADIUS * RADIUS), zmin(ZMIN), zmax(ZMAX)
{
  zmax_minus_zmin = zmax - zmin;
}

int Cylinder::isOn(const Point &P) const
{
  return P.z >= zmin && P.z <= zmax && Quadric::isOn(P);
}

Point Cylinder::P(const Param &p)
{
  angle	a = theta(p.u);
  return Point(
               radius * x(a),
               radius * y(a),
               zv(p.v));
}

Param Cylinder::p(const Point &P)
{
  return Param(u(theta(P.x, P.y)), vz(P.z));
}


Point Cylinder::Ngp(const Param &p)
{
  angle	a = theta(p.u);
  scalar rxy = radius * 2.0;
  return Point(
               rxy * x(a),
               rxy * y(a),
               0.0);
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
  angle	a = theta(p.u);
  scalar rxy = radius * to_radians(thetamax);

  return Point(
               rxy * dx(a),
               rxy * dy(a),
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



