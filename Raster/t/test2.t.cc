#include "Raster/RasterFileRGB.hh"

int main(int argc, char **argv)
{
  RasterSize rr_s(256, 256);
  RasterFileRGB rr = RasterFileRGB("temp.ras1", rr_s);
  RasterSize	s = rr.size();
  RasterFileRGB	r = RasterFileRGB("temp.ras", s);

  RasterPosition p(0,0);
  for ( ; p.y < 10; p.y ++ ) {
    r.horizontal(p, s.x, p.y);
  }
  r.vector(RasterPosition(0,0), s, RasterColor(.25, .5, .75));

  for ( p.y = 0; p.y < s.y; p.y ++ ) {
    for ( p.x = 0; p.x < s.x; p.x ++ ) {
      rr.value(p, r.value(p));
    }
  }
}
