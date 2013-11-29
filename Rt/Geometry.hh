#ifndef	__Geometry_hh
#define	__Geometry_hh

#include "Point.hh"
#include "Param.hh"
#include "Ray.hh"
#include "RPIList.hh"
#include "Xform.hh"
#include "ri/RiRand.h"

class Shader;

class Geometry {
  Geometry *next; // Scene list.
friend class Scene;
public:
  Xform *xform;     // the object -> world transform
  Shader *surface;  // the surface shader
  Geometry *shadow; // the object that create shadows on behalf of this object.

  Geometry()
    : xform(0), surface(0), shadow(this) { }
  virtual ~Geometry() {}

  virtual RPIList intersect(const Ray &r) = 0;
  virtual int intersects(const Ray &r);

  scalar rnd() const { return RiRand(); }

  virtual Point randomOn();
  virtual Point randomIn();

  // R is in world coord sys.
  RPIList wintersect(const Ray &r) { return intersect(xform->inverse_transform(r)); }
  int wintersects(const Ray& r) { return intersects(xform->inverse_transform(r)); }
  Point wrandomOn() { return xform->transform(randomOn()); }
  Point wrandomIn() { return xform->transform(randomIn()); }
};

#endif

