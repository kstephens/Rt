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
    Shader *s;

    switch ( (int) (RiRand() * 2) ) {
    case 0:
      {
        Whitted *s1 = new Whitted();
        s1->Cs  = Color(1.0);
        s1->Os  = Color(1.0);
        s1->Kd  =   0.1;
        s1->Ks  =   0.4;
        s1->Kss =  20.0;
        s1->Kr  =   0.4;
        s1->Kt  =   0.0;
        s1->M   =   0.75;
        s = s1;
      }
      break;
    case 1:
      {
        Plastic *s2 = new Plastic();
        s2->Cs = Color(RiRand(), RiRand(), RiRand());
        s2->Os = Color(1.0);
        s = s2;
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
    p1->surface = s;
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
  scene->add(p2);

  return scene;
}

