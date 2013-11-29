//
// Light.hh - class Light
//
//
#ifndef	__Light_hh
#define	__Light_hh

#include "angle.hh"
#include "Shader.hh"

class Light  {
  Light *next;
friend	class Scene;
friend	class LightIterator;
  Color	getambient() const;

public:
  Color	Cl;	// these are passed to the shader
  Color	Ol;
  Point	L;
  
  enum {
    UNDEFINED = 0,
    AMBIENT = 1,
    ILLUMINATE,
    SOLAR
  } _type;		// the light type

  unsigned	_isanarealight : 1;

  Point	_position;	// for illuminate()
  Point	_axis;		// for illuminate() and solar()
  angle  _angle; // for illuminate() and solar()
  scalar _cos_angle;	// for illuminate() and solar()

  int _nsamples;	// for solar or area lights
  int _probe;

  Light () : next(0), _type(UNDEFINED), _isanarealight(0), _nsamples(1), _probe(0) {}
virtual ~Light() {}

  Color	ambient(Shader *S);	// get the global ambient value

  void _set_probe(int p) {
    _probe = p;
  }

  int _illuminate(const Point &p) {
    if ( _probe ) {
      _type = ILLUMINATE;
      _position = p;
      _axis = 0;
      _angle = degrees(-1);
      _cos_angle = -2;
    }
    return ! _probe;
  }
  int _illuminate(const Point &p, const Point &axis, angle a) {
    if ( _probe ) {
      _type = ILLUMINATE;
      _position = p;
      _angle = a;
      _cos_angle = cos(a);
      _axis = axis.unit();
    }
    return ! _probe;
   }
#define illuminate(ARGS...) if ( _illuminate(ARGS) )

  int _solar() {
    if ( _probe ) {
      _type = SOLAR;
      _axis = 0;
      _angle = degrees(-1);
      _cos_angle = -2.0;
    }
    return ! _probe;
  }
  int _solar(const Point &axis, angle a) {
    if ( _probe ) {
      _type = SOLAR;
      _axis = axis.unit();
      _angle = a;
      _cos_angle = cos(a);
    }
    return ! _probe;
  }
#define solar(ARGS...) if ( _solar(ARGS) )

  void	init();

  virtual Point	getPoint() { return _position; }
  virtual Light *getActualLight() { return this; }
  virtual void	light() {}; // the light shader!!
};

#endif




