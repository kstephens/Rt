//
// Sky.hh
//
//
#ifndef	__Sky_hh
#define	__Sky_hh

#include "Light.hh"
#include "Vector.hh"

class Sky : public Light {
public:
  color Cground, Csky;
  Vector sun, azthmuth;

  Sky(const Point &S = Point(0, 1, 0), const Point &A = Point(0, 1, 0))
    : Light(), sun(normalize(S)), azthmuth(normalize(A))
  {
    Cground = color(0.25, 0.125, 0.0); // brown
    Csky = color(0.125, 0.33, 0.9); // sky blue
  }

  color sky(const Vector &v) {
    Vector vn = normalize(v);
    scalar d = azthmuth % vn;
    if ( d <= 0.0 ) {
      return Cground;
    } else {
      d = sun % vn;
      return Csky * (d * .5 + .5);
    }
  }

  void shader() {
    Oi = Os;
    Ci = Oi * sky(I);
  }

  void light() {
    solar() {
      Cl = sky(L);
    }
  }
};

#endif
