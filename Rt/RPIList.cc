//
// RPIList.cc - RPI (ray-primative intersection list)
// KAS 91/05/16
//
#include "RPIList.hh"
#include "stdarg.h"
#include "EPSINF.hh"
#include "RPI.hh"

RPIList::RPIList( int n, const Ray& R, Prim* P, scalar t, ... ) {
	va_list	arglist;

	first = last = (_RPI*) new RPI(R,P,t);

	va_start(arglist,t);

	while ( -- n )
          append ( new RPI( R, P, (scalar) va_arg(arglist, double)) );

	va_end(arglist);
}


void
RPIList::delete_all()
{
  RPI*	e = begin();
  first = last = RPINULL;
  while ( e != RPINULL ) {
    RPI*	t = e->next();
    delete e;
    e = t;
  }
}

//
// Derived from _Algorithms_, Robert Sedgewick pp165 - 166,
// merge(), mergesort().
//

void
RPIList::merge( RPIList& l ) {
	RPI*	a = begin();
	RPI*	b = l.begin();
	RPI*	c = RPINULL;

	do {
		last = (_RPI*) c;
		if ( a->t <= b->t ) {
			c->next(a);
			c = a;
			a = a->next();
		} else {
			c->next(b);
			c = b;
			b = b->next();
		}
	} while ( c != RPINULL );

	first = (_RPI*) RPINULL->next();

	//
	// reset sentinel.
	//
	RPINULL->next(RPINULL);

	//
	// other list loses all!
	//
	l.first = l.last = (_RPI*) RPINULL;
}

void
RPIList::sort() {
	if ( begin() != RPINULL && first != last ) {
		RPI*	b;
		RPI*	c = begin();

		b = c->next(); b = b->next(); b = b->next();
		while ( b != RPINULL ) {
			c = c->next(); b = b->next(); b = b->next();
		}

		//
		// create two temporary lists
		//
		RPIList	l2 ((_RPI*) c->next(), last);
		RPIList l1 (first, (_RPI*) c);

		c->next(RPINULL);

		l1.sort();
		l2.sort();
		l1.merge(l2);

		first = l1.first;
		last = l1.last;
	}
}

