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
  Oi = Os;
  Ci = 0;
  color OsCs = Os * Cs;
  // Ambient term.
  if ( Ka ) {
    Ci += OsCs * (Ka * ambient());
  }
  // Diffuse term.
  if ( Kd ) {
    Ci += OsCs * (Kd * diffuse(N));
  }
  // Specular term.
  if ( Ks ) {
    Point V = - normalize(I);
    Ci += Ks * specular(N, V, Kss);
  }
  // Reflective term.
  if ( Kr ) {
    Point rIN = reflect(I, N);
    Ci += Kr * trace(rIN);
  }
  // Transmissive term.
  if ( Kt ) {
    scalar eta;
    if ( I % Ng > 0 )
      eta = 1 / M;
    else
      eta = M;
    
    Point T = refract(I, N, eta);
    if ( T != 0 )
      Ci += Kt * trace(T);
  }
}
