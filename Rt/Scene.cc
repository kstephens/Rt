//
// Scene.cc - class Scene
// KAS 91/06/13
//
#include "Scene.hh"

Scene *Scene::current;

// Collect all primitive intersections along ray.
RPIList Scene::intersect(const Ray &r) const
{
  RPIList L;

  for ( Geometry *p = geos; p; p = p->next ) {
    RPIList l = p->wintersect(r);
    L.append(l);
  }

  return L;
}

//
// this finds out if a ray hits any objects on the way to a light source.
//	This should return a color, based on the amount of light
//	passed by the objects intersected.  Too lazy, ya know!
//
int Scene::isShadowed(const Ray &ray, scalar dist, Geometry *ignore) const
{
  for ( Geometry *p = geos; p; p = p->next ) {
    // If the shadow ray hits an object that
    // creates shadows, and it's not the area light
    // source object that we want to ignore,
    // and there is an intersection between
    // 0 and the distance to the light point.
    if ( p->shadow != NULL && p->shadow != ignore ) {
      RPIList l = p->shadow->wintersect(ray);
      RPI *f = l.begin()->findSmallestPositive();
      if ( f != l.end() && f->wt(&l) < dist ) {
        l.delete_all();
        return 1;
      }
      l.delete_all();
    }
  }
  
  return 0;
}


// This is it!  The ray tracing routine!
int Scene::dolist(RPI *rpi, color &Cr, color &Or, int depth) const
{
  // The ray color and opacity.
  Cr = 0.0;
  Or = 1.0;

  // From front to back...
  while ( rpi != RPINULL ) {
    // std::cerr << "  rpi = " << *rpi << "\n";
    // Initialize the surface shader varables.
    Shader *S = rpi->prim->surface;

    S->P = rpi->wP();
    S->dPdu = rpi->wdPdu();
    S->dPdv = rpi->wdPdv();
    S->N = S->Ng = rpi->wNg();
    
    S->uvw = rpi->p();

    // I is directed toward P from E.
    S->I = rpi->r.direction;

    S->trace_depth = depth - 1;

    // Call the shader.
    S->shader();

    // Use the factored opacity value.
    // Ray opacity diminishes by the opacity of the incidence.
    Cr += S->Ci * Or;
    Or *= (1.0 - S->Oi);
    // std::cerr << "    depth=" << depth << " rpi=" << *rpi << " Ci=" << S->Ci << " Oi=" << S->Oi << " Cr=" << Cr << " Or=" << Or << "\n";

    // If this surface is fully opaque,
    //	don't process the remaining surfaces.
    if ( Or <= 0 )
      return 1;

    rpi = rpi->next();
  }

  return 0; // Partially opaque?
}

int Scene::trace(const Ray& r, color &Cr, color &Or, int depth) const
{
  // std::cerr << " ray = " << r << ", depth = " << depth << "\n";
  if ( depth <= 0 )
    return 0;

  RPIList _rpi = intersect(r);

  if ( ! _rpi.isEmpty() ) {
    // Sort the ray-primitive list,
    //  and find the first positive
    //  so we can handle transparent surfaces.
    _rpi.sort();
    RPI *rpi = _rpi.begin()->findSmallestPositive();

    if ( rpi != RPINULL ) {
      dolist(rpi, Cr, Or, depth);
      _rpi.delete_all();
      Or = 1 - Or;
      return 1;
    }
  }
  _rpi.delete_all();

  // Nothing was hit, try background?
  if ( background_shader ) {
    Shader *S = background_shader;
    // I is directed toward P from E.
    S->I = r.direction;
    S->shader();
    Cr = S->Ci;
    Or = S->Oi;
    return 1;
  } else {
    // some funky grey background
    Cr = color(0.25, 0.25, 0.25);
    Or = 0;
    return 0;
  }
}

