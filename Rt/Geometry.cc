#include "Geometry.hh"
#include "RPI.hh"

RPIList Geometry::wintersect(const Ray &wr)
{
  RPIList l = intersect(xform->inverse_transform(wr));
  l.wr(wr);
  return l;
}

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
