//
// Shaders.hh
// KAS 91/06/29
//
#ifndef	__Shaders_hh
#define	__Shaders_hh

#include "Shader.hh"

class Constant : public Shader {
public:
  void shader () {
    Oi = Os;
    Ci = Os * Cs;
  }
};

class Matte : public Shader {
public:
  scalar Ka, Kd;
  Matte () : Ka(1.0), Kd(1.0) {}
  Shader *copy() const { return new Matte(*this); }

  void shader () {
    N = faceforward(N,I);
    Oi = Os;
    Ci = Os * Cs * (Ka * ambient() + Kd * diffuse(N));
  }
};

class Metal : public Shader {
public:
  scalar Ka, Ks, roughness;
  Metal() : Ka(1.0), Ks(1.0), roughness(0.25) {}
  Shader *copy() const { return new Metal(*this); }
  
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
  Color	specularcolor;

  Plastic() : Ka(1.0), Kd(0.5), Ks(0.5), roughness(0.1), specularcolor(1.0) {}
  Shader *copy() const { return new Plastic(*this); }

  void shader() {
    N = faceforward(normalize(N), I);
    Point V = normalize(- I);
    Oi = Os;
    Ci = Os * (Cs * (Ka * ambient() + Kd * diffuse(N))
               + specularcolor * Ks * specular(N, V, roughness));
  }
};

#endif

