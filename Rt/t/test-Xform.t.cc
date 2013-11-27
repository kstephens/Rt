#include "Rt/Xforms.hh"
#include "Rt/debug.hh"

int main(int argc, char **argv)
{
  Point p(0.5,1.5,2.5), p1, p2;
  Ray r(Point(1, 2, 3), Point(1, 1, 1)), r1, r2;

  Xform *x;
#define X_DEBUG() \
  E_DEBUG(*x); \
  E_DEBUG(p); \
  E_DEBUG(r); \
  E_DEBUG(p1 = x->transform(p)); \
  E_DEBUG(r1 = x->transform(r)); \
  E_DEBUG(p2 = x->inverse_transform(p1)); \
  E_DEBUG(r2 = x->inverse_transform(r1))

  x = new Translate(1, 2, 3);
  X_DEBUG();

  x = new Scale(0.5, 2, 2.5);
  X_DEBUG();

  x = new Rotate(degrees(0), 1, 0, 0);
  X_DEBUG();

  x = new Rotate(degrees(90), 0, 0, 1);
  X_DEBUG();

  return 0;
}
