#ifndef	__LightIterator_hh
#define	__LightIterator_hh

#include "Point.hh"
#include "angle.hh"

//
// 	The LightIterator class handles the illuminate() shader stmt
// It sets up a for loop that dispatches to the lights.
//
class Light;
class Shader;
class LightIterator {
  Light *L;  // the current light
  Light *La; // the actual Light object.
  Shader *S; // the shader being illuminated.
  int samples; 	// samples left for L.
  scalar sample_coeff;

  Point	P;    // the point being illuminated.
  Point	axis; // the axis of illumination cone from P.
  angle _angle;
  scalar angle_cos; // the cosine of the cone angle
  scalar lightdist;
  Point Lunit; // Unit vector L.

public:
  LightIterator() : L(NULL), S(NULL) {}
  LightIterator(Light *l, Shader *s, const Point &p, const Point &a, const angle &A) :
    L(l), S(s),
    P(p), axis(unit(a)), _angle(A), angle_cos(cos(A))
  { init(); }
  LightIterator(Light* l, Shader* s, const Point &p) :
    L(l), S(s),
    P(p), axis(0), _angle(degrees(-1)), angle_cos(-2)
  { init(); }
  void init();
  void next();
  int sample(); // the illuminance() stmt integrator
  int do_ray();
};

//
// Define Shader lighting stmts
//
#define	illuminance(POSITION...) \
  for ( _LI = LightIterator(Scene::current->lights(),this,POSITION); _LI.sample(); _LI.next())

#endif

