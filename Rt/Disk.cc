//
// Disk.cc - class Disk
// KAS 91/06/25
//
#include "Disk.hh"

Disk::Disk ( scalar h, scalar r, scalar t )
  : Quadric(t),
    radius(r), radius2(r * r), height(h)
{
  if ( t >= 0 ) {
    _Ng = Point(0.0, 0.0, 1.0);
  } else {
    _Ng = Point(0.0, 0.0, -1.0);
  }
}

Point Disk::P(const Param& p)
{
  angle	a = theta(p.u);
  float	rxy = radius * (1.0 - p.v);
  return Point(
               rxy * x(a),
               rxy * y(a),
               height);
}

Param Disk::p(const Point& P)
{
  scalar v = 1.0 - (~ ((Point2&) P) / radius);
  return Param(u(theta(P.x, P.y)), v);
}

// Geometric normal is constant.
normal Disk::Ngp(const Param& p) { return _Ng; }
normal Disk::NgP(const Point& P) { return _Ng; }
normal Disk::Ng(RPI* p)          { return _Ng; }

vector Disk::dPdup(const Param& p)
{
  angle	a = theta(p.u);
  scalar rxy = radius * to_radians(thetamax);
  return vector(rxy * dx(a),
                rxy * dy(a),
                0.0);
}

vector Disk::dPdvp(const Param& p)
{
  angle a = theta(p.u);
  scalar rxy = - radius;
  return vector(rxy * x(a),
                rxy * y(a),
                0.0);
}

RPIList
Disk::intersect(const Ray &r)
{
  if ( r.direction.z == 0 )
    return RPIList();
  scalar t = (height - r.origin.z) / r.direction.z;
  Point	p = r[t];
  p.z = height;
  if ( p.x * p.x + p.y * p.y <= radius2 && isOn(p) ) {
    RPIList list;
    RPI *rpi = new RPI(r, this, t);
    rpi->P(p);
    list.append(rpi);
    return list;
  }
  return RPIList();
}

Point Disk::randomOn()
{
  scalar sr = 2.0 * radius;
  Point	P;

  do {
    P = Point(
              (rnd() - 0.5) * sr,
              (rnd() - 0.5) * sr,
              height);
  } while ( P.x * P.x + P.y * P.y > radius2 && isOn(P) );
  
  return P;
}

Point Disk::randomIn() { return randomOn(); }


