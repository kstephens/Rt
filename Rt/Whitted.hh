#ifndef	__Rt_Whitted_hh
#define	__Rt_Whitted_hh

#include "Shader.hh"
#include "Scene.hh"

class Whitted : public Shader {
public:
  Whitted () : Shader() {}
  Shader* copy() const { return new Whitted(*this); }

  scalar Ka; // ambient coefficent
  scalar Kd; // diffuse coefficent
  scalar Ks; // specular coefficent
  scalar Kss; // specular exponent
  scalar Kr; // reflective coefficent
  scalar Kt; // transmissive coefficent
  scalar M; // index of refraction

  void shader();
};

#endif
