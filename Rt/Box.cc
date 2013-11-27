//
// Box.cc - class Box
// KAS 91/06/13
//
#include "Box.hh"
#include "EPSINF.hh"
#include "ri/RiRand.h"

inline
Point2	Box::select ( float u ) {
	if ( u < 0.25 )
		return Point2 ( lo().x + size.x * u * 4.0, lo().y );
	else if ( u < 0.5 )
		return Point2 ( hi().x, lo().y + size.x * (u - 0.25) * 4.0 );
	else if ( u < 0.75 )
		return Point2 ( hi().x - size.x * (u - 0.5) * 4.0, hi().y );
	else /* if ( p.U() < 1.0 ) */
		return Point2 ( lo().x, hi().y - size.x * (u - 0.75) * 4.0 );
}

Point	Box::P(const Param& p) {
	float	u = p[0];
	float	v = p[1];
	if ( v < 1.0 / 3.0 ) {
		Point2 p1 = (Point2&) center;
		Point2 p2 = select(u);
		return Point( p1 + (p2 - p1) * v * 3.0, lo().z );
	} else if ( v < 2.0 / 3.0 ) {
		return Point( select(u), lo().z + size.z * (v - 1.0 / 3.0) * 3.0);
	} else /* if ( v < 1.0 ) */ {
		Point2 p1 = select(u);
		Point2 p2 = (Point2&) center;
		return Point( p1 + (p2 - p1) * (v - 2.0 / 3.0) * 3.0, hi().z );
	}
}


Param	Box::p(const Point& p) {
	float	u;
	float	v;

	float	x = p.x;
	float	y = p.y;

	if ( p.z == lo().z || p.z == hi().z ) {
		float	dx = center.x - p.x / size.x;
		float	dy = center.y - p.y / size.y;
		float	ax = dx < 0.0 ? - dx : dx;
		float	ay = dy < 0.0 ? - dy : dy;
		float	t;

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

		if ( p.z == lo().z ) {
			v = t * (1.0 / 3.0);
		} else {
			v = 1.0 - (t * (1.0 / 3.0));
		}

	} else {
		v = (p.z - lo().z) / size.z * (1.0 / 3.0) + (1.0 / 3.0);
		if ( y == lo().y ) {
			u = (x - lo().x ) / size.x * 0.25;
		} else if ( x == hi().x  ) {
			u = (y - lo().y ) / size.y * 0.25 + 0.25;
		} else if ( y == hi().y ) {
			u = (hi().x - x) / size.x * 0.25 + 0.5;
		} else if ( x == lo().x) {
			u = (hi().y - y) / size.y * 0.25 + 0.75;
		}
	}

	return Param(u, v);
}


Point	Box::Ngp(const Param& p) {
	float v = p[1];
	if ( v < 1.0 / 3.0 ) {
		return Point( 0.0, 0.0, -1.0 );
	} else if ( v < 2.0 / 3.0 ) {
		float 	u = p.u;
		if ( u < 0.25 )
			return Point ( 0.0, -1.0, 0.0 );
		else if ( u < 0.5 )
			return Point ( 1.0, 0.0, 0.0 );
		else if ( u < 0.75 )
			return Point ( 0.0, 1.0, 0.0 );
		else
			return Point ( -1.0, 0.0, 0.0 );
	} else /* if ( v < 1.0 ) */ {
		return Point( 0.0, 0.0, 1.0 );
	}
}


Point	Box::NgP(const Point& p) {
	Point	N (0,0,0);

	for ( int i = 0; i < 2; i ++ ) {
		const Point&	s = operator[](i);
		for ( int j = 0; j < 3; j ++ ) {
			if ( p[j] == s[j] ) {
				N[j] = i ? 1.0 : -1.0;
				return N;
			}
		}
	}
	return N;
}

Point	Box::dPdup(const Param& p) {
	float 	u = p[0];
	if ( u < 0.25 )
		return Point( 1.0, 0.0, 0.0 );
	else if ( u < 0.5 )
		return Point( 0.0, 1.0, 0.0 );
	else if ( u < 0.75 )
		return Point( -1.0, 0.0, 0.0 );
	else
		return Point ( 0.0, -1.0, 0.0 );
}

Point	Box::dPduP(const Point& p ) {
	float	dx = (p.x - center.x) / size.x;
	float	dy = (p.y - center.y) / size.y;
	float	ax = dx < 0.0 ? - dx : dx;
	float	ay = dy < 0.0 ? - dy : dy;

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


Point	Box::dPdvp(const Param& p) {
	float 	v = p[1];

	if ( v < 1.0 / 3.0 ) {
		return Point(0);
	} else if ( v < 2.0 / 3.0 ) {
		return Point ( 0.0, 0.0, 1.0 );
	} else /* if ( v < 1.0 ) */ {
		return Point ( 0 );
	}
}


Point	Box::dPdvP(const Point& p) {
	if ( p.z == lo().z ) {
		return Point(p.x - center.x, p.y - center.y, 0.0).unit();
	} else if ( p.z == hi().z )  {
		return Point(center.x - p.x, center.y - p.y, 0.0).unit();
	} else {
		return Point(0.0, 0.0, 1.0);
	}
	return Point(0);
}

RPIList
Box::intersect( const Ray& r ) {
	RPIList	L;
	int	count = 0;

	for ( int j = 0; j < 3; j ++ ) {
		float	d = r.direction[j];
		if ( d != rt_EPSILON ) {
			for ( int i = 0; i < 2; i ++ ) {
				const Point&	s = Bound::operator[](i);
				float	t = (s[j] - r.origin[j]) / d;
				Point	P = r[t];
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
Box::intersects ( const Ray& r ) {
	for ( int j = 0; j < 3; j ++ ) {
		float	d = r.direction[j];
		if ( d != rt_EPSILON ) {
			for ( int i = 0; i < 2; i ++ ) {
				const Point&	s = Bound::operator[](i);
				float	t = (s[j] - r.origin[j]) / d;
				Point	P = r[t];
				P[j] = s[j];
				if ( isIn(P) )
					return 1;
			}
		}
	}

	return 0;
}


Point
Box::randomIn() {
	return Point ( lo().x + size.x * RiRand(),
		lo().y + size.y * RiRand(),
		lo().z + size.z * RiRand() );
}

Point
Box::randomOn() {
	Point	p = randomIn();
	Point	d = p - center;

	float	A, a;

	A = d.x > 0.0 ? d.x : - d.x;
	int	axis = 0;

	a = d.y > 0.0 ? d.y : - d.y;
	if ( a > A ) {
		axis = 1;
		A = a;
	}

	a = d.z > 0.0 ? d.z : - d.z;
	if ( a > A )
		axis = 2;

	p[axis] = d[axis] > 0.0 ? hi()[axis] : lo()[axis];
	return p;
}





