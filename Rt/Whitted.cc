//
// Whitted.cc - class Whitted
//
//
#include "Whitted.hh"
#include "Light.hh"
#include "angle.hh"

void
Whitted::shader()
{
  N = faceforward(normalize(N), I);
  Ci = Color(0);
  if ( Kd != 0 ) {
    Ci += Cs * (Kd * ambient() + Kd * diffuse(N));
  }
  if ( Ks != 0 ) {
    // specular
    Point V = - normalize(I);
    Ci += Ks * specular(N, V, Kss);
  }

  // Reflective term
  if ( Kr > 0.0 ) {
    Point rIN = reflect(I, N);
    Ci += Kr * trace(rIN);
  }

  // Transmissive term.
  if ( Kt > 0.0 ) {
    scalar eta;
    if ( I % Ng > 0 )
      eta = 1 / M;
    else
      eta = M;
    
    Point T = refract(I, N, eta);
    if ( T != 0 )
      Ci += Kt * trace(T);
  }
  Oi = Os;
}
