//
// Box.cc - class Box
// KAS 91/06/13
//
#include "Box.hh"
#include "EPSINF.hh"

/*

    u=0.75    u=0.50
      +---------+
      |         | 
 y    |         |
      |         |
      +---------+
    u=0       u=0.25
           x
*/
inline
Point2 Box::select(scalar u)
{
  if ( u < 0.25 )
    return Point2(l.x + size.x * u * 4.0,
                  l.y);
  else if ( u < 0.5 )
    return Point2(h.x,
                  l.y + size.y * (u - 0.25) * 4.0);
  else if ( u < 0.75 )
    return Point2(h.x - size.x * (u - 0.5) * 4.0,
                  h.y);
  else /* if ( p.U() < 1.0 ) */
    return Point2(l.x,
                  h.y - size.y * (u - 0.75) * 4.0 );
}

Point Box::P(const Param &p)
{
  if ( p.v < 1.0 / 3.0 ) {
    Point2 p1 = (Point2&) center;
    Point2 p2 = select(p.u);
    return Point( p1 + (p2 - p1) * p.v * 3.0, l.z );
  } else if ( p.v < 2.0 / 3.0 ) {
    return Point( select(p.u), l.z + size.z * (p.v - 1.0 / 3.0) * 3.0);
  } else /* if ( v < 1.0 ) */ {
    Point2 p1 = select(p.u);
    Point2 p2 = (Point2&) center;
    return Point( p1 + (p2 - p1) * (p.v - 2.0 / 3.0) * 3.0, h.z );
  }
}

Param Box::p(const Point &P)
{
  scalar u, v;

  if ( P.z == l.z || P.z == h.z ) {
    scalar dx = center.x - P.x / size.x;
    scalar dy = center.y - P.y / size.y;
    scalar ax = dx < 0.0 ? - dx : dx;
    scalar ay = dy < 0.0 ? - dy : dy;
    scalar t;

    if ( ay > ax ) {
      if ( (t = ay * 2.0) == rt_EPSILON ) {
        u = 0.0;
      } else {
        if ( dy < 0.0 )
          u = (dx / ay + 1.0) * 0.125;
        else
          u = (- dx / ay + 1.0) * 0.125 + 0.5;
      }
    } else {
      if ( (t = ax * 2.0) == rt_EPSILON ) {
        u = 0.0;
      } else {
        if ( dx < 0.0 )
          u = (dy / ax + 1.0) * 0.125 + 0.25;
        else
          u = (- dy / ax + 1.0) * 0.125 + 0.75;
      }
    }

    if ( P.z == l.z ) {
      v = t * (1.0 / 3.0);
    } else {
      v = 1.0 - (t * (1.0 / 3.0));
    }

  } else {
    v = (P.z - l.z) / size.z * (1.0 / 3.0) + (1.0 / 3.0);
    if ( P.y == l.y ) {
      u = (P.x - l.x ) / size.x * 0.25;
    } else if ( P.x == h.x  ) {
      u = (P.y - l.y ) / size.y * 0.25 + 0.25;
    } else if ( P.y == h.y ) {
      u = (h.x - P.x) / size.x * 0.25 + 0.5;
    } else if ( P.y == l.y ) {
      u = (h.y - P.y) / size.y * 0.25 + 0.75;
    } else {
      u = 0; // WTF
    }
  }

  return Param(u, v);
}

Point Box::Ngp(const Param &p)
{
  if ( p.v < 1.0 / 3.0 ) {
    return Point( 0.0, 0.0, -1.0 );
  } else if ( p.v < 2.0 / 3.0 ) {
    if ( p.u < 0.25 )
      return Point ( 0.0, -1.0, 0.0 );
    else if ( p.u < 0.5 )
      return Point ( 1.0, 0.0, 0.0 );
    else if ( p.u < 0.75 )
      return Point ( 0.0, 1.0, 0.0 );
    else
      return Point ( -1.0, 0.0, 0.0 );
  } else /* if ( v < 1.0 ) */ {
    return Point( 0.0, 0.0, 1.0 );
  }
}


Point Box::NgP(const Point& P)
{
  Point N(0);
  for ( int i = 0; i < 2; i ++ ) {
    const Point &s = operator[](i);
    for ( int j = 0; j < 3; j ++ ) {
      if ( P[j] == s[j] ) {
        N[j] = i ? 1.0 : -1.0;
        return N;
      }
    }
  }
  return N;
}

Point Box::dPdup(const Param& p)
{
  if ( p.u < 0.25 )
    return Point( 1.0, 0.0, 0.0 );
  else if ( p.u < 0.5 )
    return Point( 0.0, 1.0, 0.0 );
  else if ( p.u < 0.75 )
    return Point( -1.0, 0.0, 0.0 );
  else
    return Point ( 0.0, -1.0, 0.0 );
}

Point Box::dPduP(const Point &P)
{
  scalar dx = (P.x - center.x) / size.x;
  scalar dy = (P.y - center.y) / size.y;
  scalar ax = dx < 0.0 ? - dx : dx;
  scalar ay = dy < 0.0 ? - dy : dy;

  if ( ay > ax )
    if ( dy < 0.0 )
      return Point( 1.0, 0.0, 0.0 );
    else
      return Point( -1.0, 0.0, 0.0 );
  else
    if ( dx < 0.0 )
      return Point ( 0.0, -1.0, 0.0 );
    else
      return Point ( 0.0, 1.0, 0.0 );
  
  return 0;
}


Point Box::dPdvp(const Param& p)
{
  if ( p.v < 1.0 / 3.0 ) {
    return Point(0);
  } else if ( p.v < 2.0 / 3.0 ) {
    return Point ( 0.0, 0.0, 1.0 );
  } else /* if ( v < 1.0 ) */ {
    return Point ( 0 );
  }
}


Point Box::dPdvP(const Point& P)
{
  if ( P.z == l.z ) {
    return Point(P.x - center.x, P.y - center.y, 0.0).unit();
  } else if ( P.z == h.z )  {
    return Point(center.x - P.x, center.y - P.y, 0.0).unit();
  } else {
    return Point(0.0, 0.0, 1.0);
  }
  return Point(0);
}

RPIList
Box::intersect( const Ray& r )
{
  RPIList L;
  int count = 0;

  for ( int j = 0; j < 3; j ++ ) {
    scalar d = r.direction[j];
    if ( d != rt_EPSILON ) {
      for ( int i = 0; i < 2; i ++ ) {
        const Point &s = Bound::operator[](i);
        scalar t = (s[j] - r.origin[j]) / d;
        Point P = r[t];
        P[j] = s[j];
        if ( isIn(P) ) {
          RPI*	p = new RPI(r, this, t);
          p->P(P);

          Point	N(0);
          N[j] = i ? 1.0 : -1.0;
          p->Ng(N);

          L.append(p);

          if ( ++ count == 2 )
            return L;
        }
      }
    }
  }
  
  L.delete_all();
  return L;
}


int
Box::intersects ( const Ray& r )
{
  for ( int j = 0; j < 3; j ++ ) {
    scalar d = r.direction[j];
    if ( d != rt_EPSILON ) {
      for ( int i = 0; i < 2; i ++ ) {
        const Point &s = Bound::operator[](i);
        scalar t = (s[j] - r.origin[j]) / d;
        Point P = r[t];
        P[j] = s[j];
        if ( isIn(P) )
          return 1;
      }
    }
  }

  return 0;
}


Point
Box::randomIn()
{
  return Point(l.x + size.x * rnd(),
               l.y + size.y * rnd(),
               l.z + size.z * rnd() );
}

Point
Box::randomOn()
{
  Point p = randomIn();
  Point d = p - center;
  scalar A, a;

  A = d.x > 0.0 ? d.x : - d.x;
  int axis = 0;

  a = d.y > 0.0 ? d.y : - d.y;
  if ( a > A ) {
    axis = 1;
    A = a;
  }

  a = d.z > 0.0 ? d.z : - d.z;
  if ( a > A )
    axis = 2;

  p[axis] = d[axis] > 0.0 ? h[axis] : l[axis];
  return p;
}




