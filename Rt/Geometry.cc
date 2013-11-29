#include "Geometry.hh"

int Geometry::intersects(const Ray &ray)
{
  RPIList rpi = intersect(ray);
  RPI *i = rpi.begin();
  rpi.delete_all();
  return i != RPINULL;
}

Point Geometry::randomOn() { return Point(0); }
Point Geometry::randomIn() { return Point(0); }
