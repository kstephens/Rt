//
// RGB.hh - class RGB
//
//
#ifndef	__Raster_RGB_HH
#define	__Raster_RGB_HH

#include "Raster/portable.h"

class RGB {
public:
  U8	r, g, b;

  RGB() {}
  RGB ( U8 i ) : r(i), g(i), b(i) {}
  RGB ( double i ) : r(i * 255.99) { g = b = r; }
  RGB ( U8 R, U8 G, U8 B ) : r(R), g(G), b(B) {}
  RGB ( double R, double G, double B ) : r(R * 255.99), g(G * 255.99), b(B * 255.99) {}
  RGB ( const double *RGB ) : r(RGB[0] * 255.99), g(RGB[1] * 255.99), b(RGB[2] * 255.99) {}
  U8	operator [](int channel) const { return (&r)[channel]; }
  U8&	operator [](int channel) { return (&r)[channel]; }
  const U8 * begin() const { return &r; }
  const U8 * end() const { return &r + 3; }
};

#endif
