//
// CSG.hh - class CSG, CSGU, CSGI, CSGS
// KAS 91/06/29
//
#ifndef __CSG_hh
#define	__CSG_hh

#include "Prim.hh"
#include "RPI.hh"

class CSG : public Prim {
protected:
	Prim*	l;
	Prim*	r;
public:
	CSG( Prim* L, Prim* R ) : l(L), r(R) {}
	~CSG() { delete l; delete r; }

	RPIList	intersect( const Ray& R );

	//
	// IMPLEMENT!!!
	//
virtual	Point   randomOn() { return l->randomOn(); }
virtual	Point	randomIn() { return l->randomIn(); }

	enum CSGR { OUT = 1, IN = 2, ON = 4 };
virtual	CSGR	relation ( CSGR L, CSGR R ) = 0;
virtual	void	invertNg ( RPI* rpi, CSGR L, CSGR R ) {}
};

class CSGU : public CSG {
public:
	CSGU ( Prim* r, Prim* l) : CSG(r,l) {}
	CSGR	relation ( CSGR r1, CSGR r2 ) {
		if ( (r1 == OUT && (r2 == ON))
		|| (r1 == ON && (r2 & (OUT|ON))) )
			return ON;
		return OUT;
	}
};

class CSGI : public CSG {
public:
	CSGI ( Prim* r, Prim* l) : CSG(r,l) {}
	CSGR	relation ( CSGR r1, CSGR r2 ) {
		if ( (r1 == IN && (r2 == ON))
		|| (r1 == ON && (r2 & (IN|ON))) )
			return ON;
		return OUT;
	}
};

class CSGS : public CSG {
public:
	CSGS ( Prim* r, Prim* l) : CSG(r,l) {}

	CSGR	relation ( CSGR r1, CSGR r2 ) {
		if ( (r1 == IN && r2 == ON)
		|| (r1 == ON && (r2 & (OUT|ON))) )
			return ON;
		return OUT;
	}
	void	invertNg ( RPI* rpi, CSGR r1, CSGR r2 ) {
		if ( r2 == ON )
			rpi->invertNg(); }
};


////////////////////////////
//
// friendly operators ;^)
//

inline
Prim&	operator | ( Prim& l, Prim& r ) {
	return *(new CSGU(&l,&r)); }
inline
Prim&	operator * ( Prim& l, Prim& r ) {
	return *(new CSGI(&l,&r)); }
inline
Prim&	operator - ( Prim& l, Prim& r ) {
	return *(new CSGS(&l,&r)); }
#endif
