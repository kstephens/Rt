//
// LightDefs.hh - class AmbientLight, DistantLight, PointLight
//
#ifndef	__Lights_hh
#define	__Lights_hh

#include "Light.hh"

class AmbientLight : public Light {
public:
  Color	lightcolor;
  scalar intensity;

  AmbientLight() : Light() { _type = AMBIENT; }
  AmbientLight(const Color& c, scalar i = 1.0) :
    Light(), lightcolor(c), intensity(i) { _type = AMBIENT; }

  void light();
};

class DistantLight : public Light {
public:
  Color	lightcolor;
  Point	from;
  Point	to;
  scalar intensity;
  Point	tf; // to - from

  DistantLight() : Light() { }
  DistantLight(const Color& c, const Point& f, const Point& t, scalar i = 1.0 ) :
    Light(), lightcolor(c), from(f), to(t), intensity(i), tf(t - f) { }
  
  void light();
};

class PointLight: public Light {
public:
  scalar intensity;
  Color	lightcolor;
  Point	P;

  PointLight() : Light() { }
  PointLight( const Color& c, const Point& p, scalar i = 1.0 ) :
    Light(), intensity(i), lightcolor(c), P(p) {  }

  void light();
};

/*
class SpotLight : public Light {
	scalar	intensity;
	color	lightcolor;
	point	from;
	point	to;
	scalar	coneangle;
	scalar	conedeltaangle;
	scalar	coneexponent;

	SpotLight () : Light() {}
	SpotLight ( const Color& c, const Point& f, const Point& t,
		scalar ca, scalar cda, scalar ce ) :
		Light(), ...

	void	light () {
		scalar	atten, cosangle;
	}
};
*/

#endif
