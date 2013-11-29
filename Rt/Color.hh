//
// KAS 91/06/29
//
#ifndef	__Color_hh
#define	__Color_hh

#define	scalar	float
#define	vector2	color2
#define	vector3	color
#define	vector4	color4
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

color color_named(const char *name);

#endif
