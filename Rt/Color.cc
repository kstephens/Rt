#include "Color.hh"
#include "Raster/rgbtxt.h"

color color_named(const char *name)
{
  color c(0);
  int r, g, b;
  if ( rgbtxt(name, &r, &g, &b) ) {
    double s = 1.0 / 255.999;
    c.r = r * s;
    c.g = g * s;
    c.b = b * s;
  }
  return c;
}
