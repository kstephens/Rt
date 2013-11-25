//
// _RPI.hh - class _RPI
//
//
#ifndef	___RPI_hh
#define	___RPI_hh

//
// Define the terminator for RPI linked lists
//
class	RPI;	// forward reference
extern	RPI	_RPITERM;
#define RPINULL	(&_RPITERM)

//
// Base RPI class so we can inline lotsa functions!
//
class _RPI {
	_RPI*	_next;
public:
	_RPI() { _next = (_RPI*) RPINULL; }
	~_RPI() { _next = (_RPI*) RPINULL; }
	_RPI*	next() const { return _next; }
	_RPI*	next(_RPI* n) { return _next = n; }
};


#endif
