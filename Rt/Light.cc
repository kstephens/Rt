//
// Light.cc - class Light
// KAS 91/06/25
//
#include "Light.hh"

Color
Light::getambient() const {
  return (_type == AMBIENT) ? Cl : Color(0);
}

void
Light::init() {
  L = Point(1,1,1); // just incase ;^)
  light();
}

