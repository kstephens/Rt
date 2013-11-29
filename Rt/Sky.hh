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
  Color Cground, Csky;
  Point sun, azthmuth;

  Sky(const Point &S = Point(0, 1, 0), const Point &A = Point(0, 1, 0))
    : Light(), sun(normalize(S)), azthmuth(normalize(A))
  {
    Cground = Color(0.25, 0.125, 0.0); // brown
    Csky = Color(0.125, 0.33, 0.9); // sky blue
  }

  Color sky(const Vector &L) {
    Vector Ln = normalize(L);
    scalar d = azthmuth % Ln;
    if ( d <= 0.0 ) {
      return Cground;
    } else {
      scalar d = sun % Ln;
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
