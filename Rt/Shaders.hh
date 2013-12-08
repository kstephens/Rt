//
// Shaders.hh
// KAS 91/06/29
//
#ifndef	__Shaders_hh
#define	__Shaders_hh

#include "Shader.hh"

class Constant : public Shader {
public:
  Shader_declare(Constant) { }
  void shader () {
    Oi = Os;
    Ci = Os * Cs;
  }
};

class Matte : public Shader {
public:
  scalar Ka, Kd;
  Shader_declare(Matte), Ka(1.0), Kd(1.0) {}
  void shader () {
    N = faceforward(N,I);
    Oi = Os;
    Ci = Os * Cs * (Ka * ambient() + Kd * diffuse(N));
  }
};

class Metal : public Shader {
public:
  scalar Ka, Ks, roughness;
  Shader_declare(Metal), Ka(1.0), Ks(1.0), roughness(0.25) {}
  
  void shader() {
    N = faceforward(N,I);
    Point In = - I;
    Oi = Os;
    Ci = Os * Cs * (Ka * ambient() + Ks * specular(N, In, roughness));
  }
};

class Plastic : public Shader {
public:
  scalar Ka, Kd, Ks;
  scalar roughness;
  color	specularcolor;
  Shader_declare(Plastic), Ka(1.0), Kd(0.5), Ks(0.5), roughness(0.1), specularcolor(1.0) {}
  void shader() {
    N = faceforward(normalize(N), I);
    Point V = normalize(- I);
    Oi = Os;
    Ci = Os * (Cs * (Ka * ambient() + Kd * diffuse(N))
               + specularcolor * Ks * specular(N, V, roughness));
  }
};

#endif

