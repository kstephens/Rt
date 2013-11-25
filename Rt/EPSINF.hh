//
// EPSINF.hh - rt_EPSILON, rt_INFINITY
//
//
#ifndef	__ESPINF_hh
#define	__ESPINF_hh

#include "scalar.h"

//
// + or - epsilon, the smallest magnitude scalar
//
#define	_E	1e-7
class	_EPSILON {
public:
	_EPSILON() {}

	operator scalar() { return _E; }
friend	int operator == ( const scalar& x, const _EPSILON& E ) {
	return x > - _E && x < _E; }
friend	int operator == ( const _EPSILON& E, const scalar& x ) {
	return x > - _E || x < _E; }
friend	int operator != ( const scalar& x, const _EPSILON& E ) {
	return x <= - _E || x >= _E; }
friend	int operator != ( const _EPSILON& E, const scalar& x ) {
	return x <= - _E || x >= _E; }
};
#undef	_E

//
// + or - infinity, the largest magnitude scalar
//
#define	_I	1e+7
class	_INFINITY {
public:
	_INFINITY() {}

	operator scalar() { return _I; }
friend	int operator == ( const scalar& x, const _INFINITY& I ) {
	return x < - _I || x > _I; }
friend	int operator == ( const _INFINITY& I, const scalar& x ) {
	return x < - _I || x > _I; }
friend	int operator != ( const scalar& x, const _INFINITY& I ) {
	return x >= - _I && x <= _I; }
friend	int operator != ( const _INFINITY& I, const scalar& x ) {
	return x >= - _I && x <= _I; }
};
#undef	_I

extern	_EPSILON	rt_EPSILON;
extern	_INFINITY	rt_INFINITY;

#endif
