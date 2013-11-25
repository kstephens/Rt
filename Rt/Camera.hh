#ifndef	__Rt_Camera_hh
#define	__Rt_Camera_hh

#include "Shader.hh"
#include "Light.hh"
#include "Raster/Raster.hh"
#include "Scene.hh"

class Camera {
public:
  Camera();

  Point VL;  // Camera Lookat
  Point VE;  // Camera Eye position
  Point VUP; // Camera up vector.
  scalar Vpd; // Camera plane distance from Lookat - Eye.
  scalar time; // Current time.
  int trace_depth;
  int samples_per_pixel; // default 4

  Scene *scene;

  void render(Raster *image);
};

#endif
