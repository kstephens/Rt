//
// Disk.cc - class Disk
// KAS 91/06/25
//
#include "Disk.hh"

Disk::Disk ( scalar RADIUS, scalar H, scalar THETAMAX )
  : Quadric(THETAMAX),
    radius(RADIUS), radius2(RADIUS * RADIUS), height(H)
{
  if ( THETAMAX >= 0 ) {
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
Point Disk::Ngp(const Param& p) { return _Ng; }
Point Disk::NgP(const Point& P) { return _Ng; }
Point Disk::Ng(RPI* p)          { return _Ng; }

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
  if ( r.direction.z == rt_EPSILON )
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
  } else {
    return RPIList();
  }
}

Point
Disk::random() const
{
  scalar sr = 2.0 * radius;
  Point	P;

  do {
    P = Point(
              (rnd() - 0.5) * sr,
              (rnd() - 0.5) * sr,
              height);
  } while ( ((Point2&) P) % ((Point2&) P) > radius2 );
  
  return P;
}

Point Disk::randomIn() { return randomOn(); }
Point Disk::randomOn()
{
  Point P;
  
  do {
    P = random();
  } while ( ! isOn(P) );
  
  return P;
}



