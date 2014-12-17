#include "Raster/RasterMemory32.hh"

RasterValue RasterMemory32::value(const RasterPosition& p) const
{
  unsigned char *a = address(p.x, p.y);
  return ((RasterValue) a[0]) | ((RasterValue) a[1]) << 8 | ((RasterValue) a[2]) << 16 | ((RasterValue) a[3]) << 24;
}

void RasterMemory32::value(const RasterPosition& p, const RasterValue& v)
{
  unsigned char *a = address(p.x, p.y);
  a[0] = v;
  a[1] = v >> 8;
  a[2] = v >> 16;
  a[3] = v >> 24;
}

RasterColor RasterMemory32::color(const RasterPosition& p) const
{
  unsigned char *a = address(p.x, p.y);
  return RasterColor(a[0], a[1], a[2], a[3]);
}

void RasterMemory32::color(const RasterPosition& p, const RasterColor& c)
{
  unsigned char *a = address(p.x, p.y);
  RasterColor v = c; v.clamp();
  RGBA rgba(v.red(), v.green(), v.blue(), v.alpha());
  a[0] = rgba.r;
  a[1] = rgba.g;
  a[2] = rgba.b;
  a[3] = rgba.a;
}
