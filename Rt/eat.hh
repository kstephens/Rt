//
// eat.hh - eat(istream&is, char), eat(istream&is, const char*)
// KAS 91/02/15
//
#ifndef __eat_hh
#define __eat_hh

#include <iostream>

#define	READ(x) read((char*) &(x), sizeof(x))
#define WRITE(x) write((char*) &(x), sizeof(x))

extern	int	eat( std::istream& is, char c );
extern	int	eat( std::istream& is, const char* s );

#endif
