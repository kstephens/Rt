#include "Lights.hh"
#include "debug.hh"

void AmbientLight::light()
{
  Cl = lightcolor * intensity;
}

void DistantLight::light()
{
  solar(tf /* to - from */, degrees(0.0)) {
    // E_DEBUG(this);
    Cl = lightcolor * intensity;
  }
}

void PointLight::light()
{
  illuminate(P) {
    // E_DEBUG(L % L);
    Cl = lightcolor * (intensity / (L % L));
  }
}
