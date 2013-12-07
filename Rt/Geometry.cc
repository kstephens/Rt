#include "Geometry.hh"

int Geometry::intersects(const Ray &ray)
{
  RPIList rpi = intersect(ray);
  RPI *i = rpi.begin();
  rpi.delete_all();
  return i != RPINULL;
}

int Geometry::in(const point &P) { return 0; }
int Geometry::on(const point &P) { return 0; }
Point Geometry::randomOn() { return Point(0); }
Point Geometry::randomIn() { return Point(0); }
