#include "Raster/RasterMemory24.hh"

RasterValue RasterMemory24::value(const RasterPosition& p) const
{
  unsigned char *a = address(p.x, p.y);
  return ((RasterValue) a[0]) | ((RasterValue) a[1]) << 8 | ((RasterValue) a[2]) << 16;
}

void RasterMemory24::value(const RasterPosition& p, const RasterValue& v)
{
  unsigned char *a = address(p.x, p.y);
  a[0] = v;
  a[1] = v >> 8;
  a[2] = v >> 16;
}

RasterColor RasterMemory24::color(const RasterPosition& p) const
{
  unsigned char *a = address(p.x, p.y);
  return RasterColor(a[0], a[1], a[2]);
}

void RasterMemory24::color(const RasterPosition& p, const RasterColor& c)
{
  unsigned char *a = address(p.x, p.y);
  RasterColor v = c; v.clamp();
  RGB rgb(v.red(), v.green(), v.blue());
  a[0] = rgb.r;
  a[1] = rgb.g;
  a[2] = rgb.b;
}
