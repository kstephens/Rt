#include "Raster/RasterColor.hh"
#include "rgbtxt.h"

RasterColorRGB::RasterColorRGB(const char *name, double i, double A)
  : a(A)
{
  int	R, G, B;
  
  rgbtxt(name, &R, &G, &B);
  
  r = (double) R / 255.0;
  g = (double) G / 255.0;
  b = (double) B / 255.0;
  
  r *= i;
  g *= i;
  b *= i;
}

