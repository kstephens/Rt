//
// Cone.cc - class Cone
// KAS 91/06/25
//
#include "Cone.hh"
#include "EPSINF.hh"
#include "ri/RiRand.h"

Cone::Cone ( RtFloat HEIGHT, RtFloat RADIUS, RtFloat THETAMAX )
: height(HEIGHT), height2(HEIGHT * HEIGHT),
  radius(RADIUS), radius2(RADIUS * RADIUS),
  Quadric(THETAMAX)
{
}

int Cone::isOn(const Point&P) const
{
  return P.z >= 0.0 && P.z <= height && Quadric::isOn(P);
}

Point Cone::P(const Param& p)
{
  angle theta = utheta(p[0]);
  scalar rxy = radius * (1.0 - p[1]);

  return Point(
               rxy * thetax(theta),
               rxy * thetay(theta),
               p[1] * height);
}

Param Cone::p(const Point& p)
{
  return Param(thetau(xytheta(p.x, p.y)), p.z / height);
}


Point Cone::Ngp(const Param& p)
{
  angle theta = utheta(p[0]);
  return Point(
               radius * thetax(theta),
               radius * thetay(theta),
               height);
}


Point Cone::NgP(const Point& p)
{
  Point P = p;
  ((Point2&) P).normalize() * radius;
  P.z = radius / height;
  return P;
}

Point Cone::Ng(RPI* p)
{
  return NgP(p->P());
}


Point Cone::dPdup(const Param& p)
{
  angle theta = utheta(p.u);
  RtFloat rxy = radius * thetamax.radians();
  
  return Point(
               rxy * dxdtheta(theta),
               rxy * dydtheta(theta),
               0.0 );
}

Point Cone::dPdvp(const Param& p)
{
  angle theta = utheta(p.u);
  scalar rxy = - radius;
  return Point (
                rxy * thetax(theta),
                rxy * thetay(theta),
                height );
}

inline
Point
Cone::random() const
{
  scalar sr = 2.0 * radius;
  Point P;
  
  do {
    P = Point (
               (RiRand() - 0.5) * sr,
               (RiRand() - 0.5) * sr,
               RiRand());
  } while ( ((Point2&)P) % ((Point2&) P) > radius2 * P.z);
  
  P.z = (1.0 - P.z) * height;
  return P;
}

Point
Cone::randomIn()
{
  return random();
}

Point
Cone::randomOn()
{
  Point P;

  do {
    P = random();
    ((Point2&) P).normalize() * radius * (1.0 - (P.z / height));
  } while ( ! isOn(P) );
  
  return P;
}


/*

x = ox + t dx;
y = oy + t dy;
z = oz + t dz;

f = x^2 + y^2 - (r/h (h - z))^2

(ox + dx t)^2 + (oy + dy t)^2 - (r^2 (h - oz - dz t)^2)/h^2

Collect[Expand[f], t, Collect[#, r] &]
=> 
    ox^2 + oy^2 + (-1 + (2 oz)/h - oz^2/h^2) r^2 +
    (2 dx ox + 2 dy oy + ((2 dz)/h - (2 dz oz)/h^2) r^2) t +
    (dx^2 + dy^2 - (dz^2 r^2)/h^2) t^2
*/

#define ox r.origin.x
#define oy r.origin.y
#define oz r.origin.z
#define dx r.direction.x
#define dy r.direction.y
#define dz r.direction.z
#define h height
#define r2 radius2
#define h2 height2
#define P2(x) ((x) * (x))
int
Cone::quadradic(const Ray &r, double *t)
{
  return
  Quadric::quadradic(P2(dx) + P2(dy) - (P2(dz) * r2) / h2, // t^2
                     2 * dx * ox +
                     2 * dy * oy +
                     (2 * dz / h - (2 * dz * oz) / h2) * r2, // t
                     P2(ox) + P2(oy) + (-1 + (2 * oz / h) - P2(oz) / h2) * r2,
                     t);
}


