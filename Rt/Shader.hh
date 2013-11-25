//
// Shader.hh - class Shader
//
//
#ifndef	__Shader_hh
#define	__Shader_hh

#include "Color.hh"
#include "Point.hh"
#include "Param.hh"
#include "LightIterator.hh"

class Shader {
  virtual void init();
public:
  // Standard shader varables
  Color	Cs;	// Surface color
  Color	Os;	// Surface opacity
  
  Point	P;	// Surface position
  Point	dPdu;	// Derviative of surface position along u
  Point	dPdv;	// Derviative of surface position along v
  Point	N;	// Surface shading normal
  Point	Ng;	// Surface geometric normal

  Param	uvw;	// Surface parameters
  // Param	duvw;	// Change in surface parameters

  Point	L;	// Light ray direction
  Color	Cl;	// Light ray color
  Color	Ol;	// Light ray opacity
  
  Point	I;	// Incident ray direction
  Color	Ci;	// Incident ray color
  Color	Oi;	// Incident ray opacity

static	Point	E;	// Position of the eye

  // Internals
  int	trace_depth;	// set by Object::Trace()
  LightIterator	_LI;	// for illuminate() stmt
  Light *_current_light;

  Shader() { init(); }

virtual	Shader*	copy() const { return new Shader(*this); }

virtual	~Shader() {}

virtual	void	shader () { Ci = Cs; }	// The shader!!

  Color	ambient();
  Color	diffuse(Point& N);
  Color	specular(Point& N, Point& V, scalar roughness);
  Color	phong(Point& N, Point& V, scalar size);
  Color	trace(Point& R);
};

#endif

