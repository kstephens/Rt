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

color
Shader::trace(Point& R)
{
  // Save the shader's state for recursion.
  Shader* temp = copy();
  
  color	Ct = Scene::current->trace(Ray(P,R).fix(Ng), trace_depth);

  // Restore shader state.
  *this = *temp;
  delete temp;
  
  return Ct;
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
    if ( 0 ) {
      E_DEBUG(L);
      E_DEBUG(N);
      E_DEBUG(L % N);
    }
  }
  if ( 0 && C != 0 ) E_DEBUG(C);
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
