//
// CheckerBoard.hh - class CheckerBoard
// KAS 91/05/15
//
#ifndef	__CheckerBoard_hh
#define	__CheckerBoard_hh

#include "Shader.hh"
#include "Scene.hh"

class CheckerBoard : public Shader {
public:
  CheckerBoard () : Shader() {}
  Shader *copy() const { return new CheckerBoard(*this); }

  Point	scale;
  color	colors[2][2];
  scalar Ka, Kd, Ks, Kss;
  void	shader();
};

#endif
