#include "ri/ri.h"
#include <math.h>

//E.1 Box Filter
RtFloat
RiBoxFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
  return 1.0;
}

// E.2 Triangle Filter
RtFloat
RiTriangleFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
  return
    ( (1.0 - fabs(x)) / (xwidth*0.5) ) * 
    ( (1.0 - fabs(y)) / (ywidth*0.5) ) ;
}

// E.3 CatmullRom Filter
RtFloat
RiCatmullRomFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
  RtFloat r2 = (x*x + y*y);
  RtFloat r = sqrt(r2);
  return
    r >= 2.0 ? 0.0 :
    r < 1.0 ? (3.0*r*r2 - 5.0*r2 + 2.0) :
    (-r*r2 + 5.0*r2 - 8.0*r + 4.0);
}

// E.4 Gaussian Filter
RtFloat
RiGaussianFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
  x *= 2.0 / xwidth;
  y *= 2.0 / ywidth;
  return exp(-2.0 * (x*x + y*y));
}

// E.5 Sinc Filter
RtFloat
RiSincFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
  RtFloat s, t;
  if (x > -0.001 && x < 0.001)
    s = 1.0;
  else
    s = sin(x)/x;
  if (y > -0.001 && y < 0.001)
    t = 1.0;
  else
    t = sin(y)/y; 
  return s*t;
}
