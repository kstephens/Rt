//
// CSG.cc - class CSG
// KAS 91/06/29
//
#include "CSG.hh"

RPIList
CSG::intersect ( const Ray& R ) {
	RPIList	L1 = l->intersect(R); L1.sort();
	RPI*	l1 = L1.begin();
	RPIList	L2 = r->intersect(R); L2.sort();
	RPI*	l2 = L2.begin();

	RPIList	L;	// new list

	CSGR	r1 = OUT;	// relation of point to left prim
	CSGR	r2 = OUT;	// relation of point to right prim

	int	oe1 = 0;	// odd/even intersection flag
	int	oe2 = 0;

	while ( l1 != RPINULL || l2 != RPINULL ) {
		RPI*	rpi;

		if ( l1->t <= l2->t ) {
			rpi = l1;
			l1 = l1->next();
			if ( r2 == ON ) {
                          if ( oe2 ) {
                            r2 = IN;
                          } else {
                            r2 = OUT;
                          }
                        }
			r1 = ON;
			oe1 = ! oe1;
		} else {
			rpi = l2;
			l2 = l2->next();
			if ( r1 == ON ) {
                          if ( oe1 ) {
                            r1 = IN;
                          } else {
                            r1 = OUT;
                          }
                        }
			r2 = ON;
			oe2 = ! oe2;
		}

		//
		// Check the relation for ON'ness
		//
		if ( relation ( r1, r2 ) == ON ) {
			invertNg(rpi, r1, r2);
			L.append(rpi);
		} else
		//
		// Just throw it away
		//
			delete rpi;
	}

	return	L;
}
