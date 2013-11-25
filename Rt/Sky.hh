//
// Sky.hh
//
//
#ifndef	__Sky_hh
#define	__Sky_hh

#include "Light.hh"

class Sky : public Light {
public:
  Sky() : Light() {}
  Sky(const Point& A) : Light(), azthmuth(normalize(A)) {
    ground = Color(0.25, 0.125, 0.0); // brown
    sky = Color ( 0.125, 0.33, 0.9 ); // sky blue
  }
  Color ground, sky;
  Point	azthmuth;

  void light() {
    solar() {
      scalar d = azthmuth % normalize(L);
      if ( d < 0.0 ) {
        Cl = ground;
      } else {
        Cl = sky * (d * .5 + .5);
      }
    }
  }
};

#endif
