//
// CheckerBoard.cc - class CheckerBoard
// KAS 91/05/15
//
#include "CheckerBoard.hh"
#include "Light.hh"
#include "debug.hh"

void
CheckerBoard::shader()
{
  N = faceforward(normalize(N),I);
  Point V = - normalize(I);

  int cx = (unsigned (uvw.u * scale.x) & 1);
  int cy = (unsigned (uvw.v * scale.y) & 1);
  Cs = colors[cy][cx];

  Oi = Os;
  Ci = Ka * ambient();
  Ci += Kd * diffuse(N);
  Ci += Ks * specular(N, V, Kss);
  if ( 0 && Ci != 0 ) E_DEBUG(Ci);
  Ci *= Cs;
}
