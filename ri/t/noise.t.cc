#include "Raster/RasterFileRGB.hh"
#include "ri/RiNoise.h"

extern "C" RtFloat W(RtFloat t);

int main(int argc, char **argv)
{
  RasterSize d_size(640, 480);
  RasterFileRGB rf("t/test.ras", d_size);
  Raster &r = rf;

  RiInitNoise();

  RasterPosition	p;
  RasterPosition	s = r.size();

  RasterColor	color ( "flesh", 0.7);

  for ( p.y = 0; p.y < s.y; p.y ++ ) {
    RtFloat v = (RtFloat) p.y * 0.1;
    for ( p.x = 0; p.x < s.x; p.x ++ ) {
      RtFloat	u = (RtFloat) p.x * 0.1;
      RtFloat sum = 0.0;
      RtFloat scale = 1.0;
      RtFloat inv_scale = 1.0;
      
      while ( scale > RI_EPSILON ) {
        sum += scale * RiFloatNoiseFloat2(u * inv_scale, v * inv_scale );
        scale *= 0.5;
        inv_scale *= 2.0;
      }
      r.color( p, color * sum );
    }
  }

  return 0;
}

