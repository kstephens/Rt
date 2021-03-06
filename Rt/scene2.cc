//
// scene2.cc
//
#include "Geometries.hh"
#include "Lights.hh"
#include "Shaders.hh"
#include "Sky.hh"
#include "Whitted.hh"
#include "CheckerBoard.hh"
#include "NormalShader.hh"
#include "Scene.hh"
#include "Xforms.hh"
#include "Camera.hh"
#include "ri/RiRand.h"

Scene *scene2(Camera *camera)
{
  Scene *scene = new Scene();

  camera->VL = Point( 0.0, 1.5, 0.0 );	// the look-at point
  camera->VE = Point( 1.0, 5.0, -5.0 );	// the eye point
  camera->Vpd = 5.0;		// distance of camera plane from eye
  camera->VUP = Point( 0.0, 1.0, 0.0 );	// camera up vector

  Point distant_light_axis = Point( 10, 8,   0);
  scene->background_shader = new Sky(distant_light_axis);
  scene->add(new AmbientLight(color(1.0, 1.0, 1.0), 0.1) );
  scene->add(new DistantLight(color(1.0, 1.0, 1.0), distant_light_axis, Point(0), 1.0) );
  scene->add(new PointLight(color(1.0, 0.2, 0.2),   Point(  0, 8,  10), 100.0) );
  scene->add(new PointLight(color(0.2, 1.0, 0.2),   Point(-10, 8,   0), 100.0) );
  scene->add(new PointLight(color(0.2, 0.2, 1.0),   Point(  0, 8, -10), 100.0) );

  int n_prims = 5;
  for ( int i = 0; i < n_prims * n_prims; ++ i ) {
    Shader *surface;
    double ix = i % n_prims; double iy = i / n_prims;
    ix -= n_prims / 2;
    iy -= n_prims / 2;
    ix *= 3;
    iy *= 3;

    switch ( i % 4 ) {
    case 0:
      {
        Whitted *s = new Whitted();
        s->Cs  =   1.0;
        s->Os  =   1.0;
        s->Ka  =   0.1;
        s->Kd  =   0.1;
        s->Ks  =   0.4;
        s->Kss =  1.0/50.0;
        s->Kr  =   0.4;
        s->Kt  =   0.0;
        s->M   =   0.75;
        surface = s;
      }
      break;
    case 1:
      {
        Plastic *s = new Plastic();
        s->Cs = unit(color(RiRand(), RiRand(), RiRand()));
        s->Os = 1.0;
        s->roughness = 1.0/30.0;
        surface = s;
      }
      break;
    case 2:
      {
        CheckerBoard *s = new CheckerBoard;
        s->colors[0][0] = color(0.2);
        s->colors[0][1] = unit(color(RiRand(), RiRand(), RiRand()));
        s->colors[1][0] = s->colors[0][1];
        s->colors[1][1] = s->colors[0][0];
        s->scale = 10.0;
        s->Ka = 0.0;
        s->Kd = 0.8;
        s->Ks = 0.4;
        s->Kss = 1.0/20;
        s->Os = 1;
        surface = s;
      }
      break;
    case 3:
      surface = new NormalShader();
      break;
    }
    
    Geometry *p1;
    switch ( i % 5 ) {
    case 0:
      p1 = new Sphere(1.0, -1.0, 1.0, 360.0);
      break;
    case 1:
      p1 = new Cylinder(1.0, -1.0, 1.0, 360.0);
      break;
    case 2:
      p1 = new Cone(2.0, 1.0, 360.0);
      break;
    case 3:
      p1 = new Disk(0.0, 1.0, 360.0);
      break;
    case 4:
      p1 = new Box(Point(-1.0, -1.0, -1.0), Point(1.0, 1.0, 1.0));
      break;
    }
    p1->surface = surface;

    Xform *x = new Translate(ix, 1 + RiRand() * 2, iy);
    // x->concat(Rotate(degrees(360 * RiRand()), RiRand(), RiRand(), RiRand()));
    p1->xform = x;

    scene->add(p1);
  }

  CheckerBoard *s2 = new CheckerBoard;
  s2->colors[0][0] = 0.00;
  s2->colors[0][1] = 0.33;
  s2->colors[1][0] = 0.66;
  s2->colors[1][1] = 1.00;
  s2->scale = 10.0;
  s2->Ka = 0.0;
  s2->Kd = 0.4;
  s2->Ks = 0.4;
  s2->Kss = 1.0/20;
  s2->Os = 1.0;

  Geometry *p2 = new Plane(Point(-8.5, -1.0, -8.5), Point(8.5, -1.0, 8.5), 1);
  p2->surface = s2;
  p2->xform = new Xform();
  scene->add(p2);

  return scene;
}

