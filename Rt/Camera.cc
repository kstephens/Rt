//
// Camera.cc
// KAS 91/06/29
//
#include "Camera.hh"
#include "ri/RiRand.h"

Camera::Camera()
{
  trace_depth = 3;
  samples_per_pixel = 4;
}

static
Point lerp(scalar u, const Point &p0, const Point &p1)
{
  return p0 * (1 - u) + p1 * u;
}

void Camera::render(Raster *image)
{
  RasterPosition	size = image->size();

  scalar pixelAspect = image->pixelAspectRatioXY();
  scalar imageAspect = (scalar) size.y / (scalar) size.x;
  scalar aspect = pixelAspect / imageAspect;

  Scene::current = scene;
  Shader::E = VE;

  // Unit vector from eye to lookat.
  vector VD = unit(VL - VE);

  // VP at view distance:
  point VP = VE + VD * Vpd;
  // vector of screen X:
  vector viewu = unit(VD ^ VUP);
  // vector of screen Y:
  vector viewv = (viewu ^ VD);

  vector *ux = new vector [size.x + 1];
  vector *vy = new vector [size.y + 1];

  RasterPosition s;

  for ( s.x = 0; s.x <= size.x; s.x ++ ) {
    scalar u = (s.x - size.x * 0.5) / size.x * 2.0;
    ux[s.x] = viewu * u * aspect;
  }

  for ( s.y = 0; s.y <= size.y; s.y ++ ) {
    scalar v = (s.y - size.y * 0.5) / size.y * -2.0;
    vy[s.y] = viewv * v;
  }

  for ( s.y = 0; s.y < size.y; s.y ++ ) {
    for ( s.x = 0; s.x < size.x; s.x ++ ) {
      // pixel corners:
      vector rect[2][2] = {
        { ux[s.x] + vy[s.y]    , ux[s.x + 1] + vy[s.y] },
        { ux[s.x] + vy[s.y + 1], ux[s.x + 1] + vy[s.y + 1] },
      };

      // Accumulate random samples color and opacity within pixel:
      color Cp(0), Op(0);
      for ( int sample = 0; sample < samples_per_pixel; ++ sample ) {
        scalar su = RiRand(), sv = RiRand();
        vector P = lerp(sv,
                        lerp(su, rect[0][0], rect[0][1]),
                        lerp(su, rect[1][0], rect[1][1]));
        Ray   ray(VE, unit((VP + P) - VE));
        
        color Cr, Or;
        scene->trace(ray, Cr, Or, trace_depth);
        Cp += Cr;
        Op += Or;
      }
      Cp *= 1.0 / samples_per_pixel;
      Op *= 1.0 / samples_per_pixel;

      // std::cerr << "  " << s.x << "," << s.y << " = " << Cp << "," << Op << "\n";
      image->color(s, RasterColor(Cp.r, Cp.g, Cp.b, (Op.r + Op.g + Op.b) / 3));
    }
  }

  delete [] ux;
  delete [] vy;
}

