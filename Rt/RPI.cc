//
// RPI.cc - RPI (ray-primative intersection list)
// KAS 91/05/16
//
#include "RPI.hh"
#include "EPSINF.hh"

//
// This is the terminator for RPI lists and the RPI that RPINULL
// points to.  Its also the sentinel for the merge and sort routines.
//
RPI	_RPITERM(INFINITY);

RPI*
RPI::findSmallest() {
	scalar	T = t;
	RPI*	P = this;
	RPI*	p = next();

	for ( ; p != RPINULL; p = p->next() ) {
		if ( p->t < T ) {
			T = p->t;
			P = p;
		}
	}

	return P;
}

RPI*
RPI::findSmallestPositive() {
	scalar	T = INFINITY;
	RPI*	P = RPINULL;
	RPI*	p = this;

	for ( ; p != RPINULL; p = p->next() ) {
		if ( p->t > 0.0001 && p->t < T ) {
			T = p->t;
			P = p;
		}
	}

	return P;
}

RPI*
RPI::findBiggest() {
	scalar	T = t;
	RPI*	P = this;
	RPI*	p = next();

	for ( ; p != RPINULL; p = p->next() ) {
		if ( p->t > T ) {
			T = p->t;
			P = p;
		}
	}

	return P;
}

RPI*
RPI::findPositive() {
	RPI*	p = this;

	for ( ; p != RPINULL; p = p->next() ) {
		if ( p->t > (scalar) rt_EPSILON )
			break;
	}

	return p;
}

