//
// eat.cc
// KAS 91/02/15
//
#include "eat.hh"

int
eat(std::istream& is, char C ) {
	if ( is ) {
		char	c;
		is.get(c);
		if ( c != C ) {
			is.putback(c);
			is.clear(std::ios::badbit|is.rdstate());
                	return 0;
		}
		return 1;
	}
        return 0;
}

int
eat(std::istream& is, const char* S ) {
	if ( is ) {
		const char	*s;
		for ( s = S; *s; s ++ ) {
			if ( ! eat(is,*s) ) {
				while ( s > S )
				is.putback(*(-- s));
                        	return 0;
			}
		}
		return 1;
	}
        return 0;
}


