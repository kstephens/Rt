//
// Shader.hh - class Shader
//
//
#ifndef	__Shader_hh
#define	__Shader_hh

#include "Color.hh"
#include "Point.hh"
#include "vector.hh"
#include "normal.hh"
#include "Param.hh"
#include "XForm.hh"
#include "LightIterator.hh"

class Shader {
  virtual void init();
public:
  // Standard shader varables
  color	Cs;	// Surface color
  color	Os;	// Surface opacity
  
  Point	P;	// Surface position
  Point	dPdu;	// Derviative of surface position along u
  Point	dPdv;	// Derviative of surface position along v
  Point	N;	// Surface shading normal
  Point	Ng;	// Surface geometric normal

  Param	uvw;	// Surface parameters
  // Param	duvw;	// Change in surface parameters

  Point	L;	// Light ray direction
  color	Cl;	// Light ray color
  color	Ol;	// Light ray opacity
  
  Point	I;	// Incident ray direction
  color	Ci;	// Incident ray color
  color	Oi;	// Incident ray opacity

  color Cr;     // last trace() ray color
  color Or;     // last trace() ray opacity

static	Point	E;	// Position of the eye

  // Internals
  int	trace_depth;	// set by Object::Trace()
  LightIterator	_LI;	// for illuminate() stmt
  Light *_current_light;
  Xform *xform; // to world.

  Shader() { init(); }
  virtual Shader *copy() const { return new Shader(*this); }
  virtual void assign(void *x) { *this = *(const Shader*)x; }

#define Shader_declare(N)                          \
  Shader *copy() const { return new N(*this); }    \
  void assign(void *x) { *this = *(const N*) x; }  \
  N() : Shader()

virtual	~Shader() {}

  virtual void shader() { Oi = Os; Ci = Cs; }	// The shader!!

  // built-in RSL functions.
  color	ambient();
  color	diffuse(Point& N);
  color	specular(Point& N, Point& V, scalar roughness);
  color	phong(Point& N, Point& V, scalar size);
  color	trace(const vector& R);
};

#endif

