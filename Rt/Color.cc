#include "Color.hh"
#include "Raster/rgbtxt.h"

Color color_named(const char *name)
{
  Color c(0);
  int r, g, b;
  if ( rgbtxt(name, &r, &g, &b) ) {
    c.r = (float) r / 255.99;
    c.g = (float) g / 255.99;
    c.b = (float) b / 255.99;
  }
  return c;
}
