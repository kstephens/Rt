#ifndef	__NormalShader_hh
#define	__NormalShader_hh

#include "Shader.hh"

class NormalShader : public Shader {
public:
  NormalShader() : Shader() {}
  Shader *copy() const { return new NormalShader(*this); }
  void shader()
  {
    N = normalize(N);
    normal Nc = N * 0.5 + 0.5;
    Oi = Os;
    Ci = Os * color(Nc.x, Nc.y, Nc.z);
  }
};

#endif
