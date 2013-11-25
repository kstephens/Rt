//
// Color.hh - class Color
// KAS 91/06/29
//
#ifndef	__Color_hh
#define	__Color_hh

#define	scalar	float
#define	vector2	Color2
#define	vector3	Color
#define	vector4	Color4
#define	x	r
#define	y	g
#define	z	b

#include "vector_imp.hh"

#undef	scalar
#undef	vector2
#undef	vector3
#undef	vector4
#undef	x
#undef	y
#undef	z

Color color_named(const char *name);

#endif
