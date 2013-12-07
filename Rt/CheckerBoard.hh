//
// CheckerBoard.hh - class CheckerBoard
// KAS 91/05/15
//
#ifndef	__CheckerBoard_hh
#define	__CheckerBoard_hh

#include "Shader.hh"

class CheckerBoard : public Shader {
public:
  CheckerBoard () : Shader() {}
  Shader *copy() const { return new CheckerBoard(*this); }

  Point	scale;
  color	colors[2][2];
  scalar Ka, Kd, Ks, Kss;
void shader()
{
  N = faceforward(normalize(N),I);
  Point V = - normalize(I);

  int cx = (unsigned (uvw.u * scale.x) & 1);
  int cy = (unsigned (uvw.v * scale.y) & 1);
  Cs = colors[cy][cx];

  Oi = Os;
  Ci = Os * Cs * (Ka * ambient() + Kd * diffuse(N))
    + Ks * specular(N, V, Kss);
}
};

#endif
