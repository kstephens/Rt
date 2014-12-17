//
// Cone.cc - class Cone
// KAS 91/06/25
//
#include "Cone.hh"
#include "EPSINF.hh"

Cone::Cone ( scalar HEIGHT, scalar RADIUS, scalar THETAMAX )
  : Quadric(THETAMAX),
    height(HEIGHT), height2(HEIGHT * HEIGHT),
    radius(RADIUS), radius2(RADIUS * RADIUS)
{
}

int Cone::isOn(const Point&P) const
{
  return P.z >= 0.0 && P.z <= height && Quadric::isOn(P);
}

Point Cone::P(const Param& p)
{
  angle a = theta(p.u);
  scalar rxy = radius * (1.0 - p.v);
  return Point(rxy * x(a),
               rxy * y(a),
               height * p.v);
}

Param Cone::p(const Point& p)
{
  return Param(u(theta(p.x, p.y)), p.z / height);
}

#if 0
Point Cone::Ngp(const Param &p)
{
  angle a = theta(p.u);
  return Point(radius * x(a),
               radius * y(a),
               height);
}

Point Cone::NgP(const Point& p)
{
  Point P = p;
  ((Point2&) P).normalize() * radius; // ???
  P.z = radius / height;
  return P;
}

Point Cone::Ng(RPI* p)
{
  return NgP(p->P());
}
#endif

vector Cone::dPdup(const Param& p)
{
  angle a = theta(p.u);
  scalar rxy = radius * to_radians(thetamax);
  return vector(rxy * dx(a),
                rxy * dy(a),
                0.0);
}

vector Cone::dPdvp(const Param& p)
{
  angle a = theta(p.u);
  scalar rxy = - radius;
  return vector(rxy * x(a),
                rxy * y(a),
                height);
}

Point Cone::random() const
{
  scalar sr = 2.0 * radius;
  Point P;
  do {
    P = Point((rnd() - 0.5) * sr,
              (rnd() - 0.5) * sr,
              rnd());
  } while ( ((Point2&)P) % ((Point2&) P) > radius2 * P.z ); // ???
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
  scalar sr = 2.0 * radius, r2;
  Point P;
  // Find point in disk of base.
  do {
    P.x = (rnd() - 0.5) * sr;
    P.y = (rnd() - 0.5) * sr;
  } while ( (r2 = ((Point2&) P) % ((Point2&) P)) > radius2 );
  // Project up from base to height.
  scalar v = 1.0 - (r2 / radius2);
  P.z = height * v;
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
Cone::quadradic(const Ray &r, scalar *t)
{
  return
  Quadric::quadradic(P2(dx) + P2(dy) - (P2(dz) * r2) / h2, // t^2
                     2 * dx * ox +
                     2 * dy * oy +
                     (2 * dz / h - (2 * dz * oz) / h2) * r2, // t
                     P2(ox) + P2(oy) + (-1 + (2 * oz / h) - P2(oz) / h2) * r2,
                     t);
}


