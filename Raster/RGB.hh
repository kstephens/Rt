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
  RGB ( double i ) : r(i * 255.9999) { g = b = r; }
  RGB ( U8 R, U8 G, U8 B ) : r(R), g(G), b(B) {}
  RGB ( double R, double G, double B ) : r(R * 255.9999), g(G * 255.9999), b(B * 255.9999) {}
  RGB ( const double *rgb ) : r(rgb[0] * 255.9999), g(rgb[1] * 255.9999), b(rgb[2] * 255.9999) {}
  U8	operator [](int channel) const { return (&r)[channel]; }
  U8&	operator [](int channel) { return (&r)[channel]; }
  const U8 * begin() const { return &r; }
  const U8 * end() const { return &r + 3; }
};

class RGBA : public RGB {
public:
  U8 a;

  RGBA() {}
  RGBA ( U8 i ) : RGB(i), a(255) {}
  RGBA ( double i ) : RGB(i), a(255) { }
  RGBA ( U8 R, U8 G, U8 B, U8 A = 255 ) : RGB(R, G, B), a(A) {}
  RGBA( double R, double G, double B, double A = 1) : RGB(R, G, B), a(A * 255.9999) {}
  RGBA( const double *rgba ) : RGB(rgba), a(rgba[3] * 255.9999) { }
};

#endif
