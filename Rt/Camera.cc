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
  Point	VD = (VL - VE).unit();

  // VP at view distance:
  Point	VP = VE + VD * Vpd;
  Point	viewu = (VD ^ VUP).unit();
  Point	viewv = (viewu ^ VD);

  Point *ux = new Point [size.x + 1];
  Point *vy = new Point [size.y + 1];

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
      Point rect[2][2] = {
        { ux[s.x] + vy[s.y]    , ux[s.x + 1] + vy[s.y] },
        { ux[s.x] + vy[s.y + 1], ux[s.x + 1] + vy[s.y + 1] },
      };
      color C(0);
      for ( int sample = 0; sample < samples_per_pixel; ++ sample ) {
        scalar su = RiRand(), sv = RiRand();
        Point P = lerp(sv, 
                       lerp(su, rect[0][0], rect[0][1]),
                       lerp(su, rect[1][0], rect[1][1]));
        Ray   ray(VE, (VP + P - VE).unit());
        
        C += scene->trace(ray, trace_depth);
      }
      C /= samples_per_pixel;
      // std::cerr << "  " << s.x << "," << s.y << " " << ray << " = " << C << "\n";
      image->color(s, RasterColor(C.r, C.g, C.b));
    }
  }

  delete [] ux;
  delete [] vy;
}

