//
// Shader.cc - class Shader
// KAS 91/06/25
//
#include "Shader.hh"
#include "Scene.hh"
#include "debug.hh"

Point Shader::E;

void
Shader::init()
{
  Cs = Os = 1.0;
}

color Shader::trace(const vector& R)
{
  // Save the shader's state for recursion.
  Shader *temp = copy();
  
  color	Cr, Or;
  Scene::current->trace(Ray(P, R).normalize().fix(Ng), Cr, Or, trace_depth);

  // Restore shader state.
  assign(temp);
  delete temp;
  
  // Save trace result.
  this->Or = Or;
  return this->Cr = Cr;
}

color Shader::ambient()
{
  return Scene::current->ambient();
}

color Shader::diffuse(Point &N)
{
  color C = 0;
  illuminance(P, N, degrees(90)) {
    L = normalize(L);
    C += Cl * (L % N);
  }
  return C;	
}

color Shader::specular(Point &N, Point &V, scalar roughness)
{
  color C = 0;
  scalar one_over_roughness = 1.0 / roughness;
  illuminance(P, N, degrees(90)) {
    Point H = normalize(normalize(L) + V);
    C += Cl * pow(N % H, one_over_roughness);
  }
  return C;
}

color Shader::phong(Point &N, Point &V, scalar size)
{
  color C = 0;
  Point	R = normalize(reflect(-V, N));
  illuminance(P, N, degrees(90)) {
    L = normalize(L);
    C += Cl * pow(R % L, size);
  }
  return C;
}
