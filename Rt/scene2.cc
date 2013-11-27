//
// scene2.cc
//
#include "Sphere.hh"
#include "Cylinder.hh"
#include "Box.hh"
#include "Plane.hh"
#include "Lights.hh"
#include "Shader.hh"
#include "Shaders.hh"
#include "Whitted.hh"
#include "CheckerBoard.hh"
#include "Scene.hh"
#include "Xforms.hh"
#include "Camera.hh"
#include "ri/rirand.h"

Scene *scene2(Camera *camera)
{
  Scene *scene = new Scene();

  camera->VL = Point( 0.0, 0.0, 0.0 );	// the look-at point
  camera->VE = Point( 1.0, 5.0, -5.0 );	// the eye point
  camera->Vpd = 5.0;		// distance of camera plane from eye
  camera->VUP = Point( 0.0, 1.0, 0.0 );	// camera up vector

  scene->add(new AmbientLight(Color(1.0, 1.0, 1.0), 0.1) );
  scene->add(new DistantLight(Color(1.0, 1.0, 1.0), Point(4, 2, 0), Point(0), 0.5) );
  scene->add(new PointLight(Color(1.0, 0.2, 0.2), Point(-10, 6, -10), 100.0) );
  scene->add(new PointLight(Color(0.2, 1.0, 0.2), Point(-10, 6,   0), 100.0) );
  scene->add(new PointLight(Color(0.2, 0.2, 1.0), Point(-10, 6,  10), 100.0) );

  for ( int i = 0; i < 10; ++ i ) {
    Shader *surface;

    switch ( (int) (RiRand() * 2) ) {
    case 0:
      {
        Whitted *s = new Whitted();
        s->Cs  =   1.0;
        s->Os  =   1.0;
        s->Ka  =   0.1;
        s->Kd  =   0.1;
        s->Ks  =   0.4;
        s->Kss =  1.0/20.0;
        s->Kr  =   0.4;
        s->Kt  =   0.0;
        s->M   =   0.75;
        surface = s;
      }
      break;
    case 1:
      {
        Plastic *s = new Plastic();
        s->Cs = Color(RiRand(), RiRand(), RiRand());
        s->Os = 1.0;
        s->roughness = 1.0/15.0;
        surface = s;
      }
      break;
    }
    
    Prim *p1;
    switch ( (int) (RiRand() * 2) ) {
    case 0:
      p1 = new Sphere(1.0, -1.0, 1.0, 360.0);
      break;
    case 1:
      p1 = new Cylinder(1.0, -1.0, 1.0, 360.0);
      break;
    }
    p1->surface = surface;
    p1->xform = new Translate(8.0 * RiRand() - 4.0, 4.0 * RiRand(), 8.0 * RiRand() - 4.0);
    scene->add(p1);
  }

  CheckerBoard *s2 = new CheckerBoard;
  s2->colors[0][0] = Color(0.2, 0.2, 0.2);
  s2->colors[0][1] = Color(0.8, 0.3, 0.5);
  s2->colors[1][0] = Color(0.2, 0.8, 1.3);
  s2->colors[1][1] = Color(1.0, 1.0, 1.0);
  s2->scale = 10.0;
  s2->Ka = 0.0;
  s2->Kd = 0.4;
  s2->Ks = 0.4;
  s2->Kss = 10;
  s2->Os = Color(1);

  Prim *p2 = new Plane(Point(-8.5, -4.0, -8.5), Point(8.5, -4.0, 8.5), 1); 
  p2->surface = s2;
  p2->xform = new Xform();
  scene->add(p2);

  return scene;
}

