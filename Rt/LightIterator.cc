//
// LightIterator.cc - class LightIterator
//
//
#include "Light.hh"
#include "Shader.hh"
#include "EPSINF.hh"
#include "AreaLight.hh"
#include "Scene.hh"
#include "debug.hh"
#include <stdlib.h> // abort()

//#include "LightIterator.hh"

void
LightIterator::init()
{
  sample_coeff = 1.0 / (samples = L->_nsamples);
}

void
LightIterator::next(){
  if ( -- samples <= 0 )
    if ( (L = L->next) != NULL )
      init();
}

int
LightIterator::sample()
{
  while ( L != NULL ) {
    La = L->getActualLight();

    // Probe light for illuminance type.
    La->_set_probe(1);
    La->light();
    La->_set_probe(0);

    switch ( La->_type ) {
    case Light::AMBIENT:
      break;

    case Light::SOLAR:
      La->L = La->_axis;
      lightdist = INFINITY;
      Lunit = - La->L;

      if ( 0 ) {
        E_DEBUG(La->_type);
        E_DEBUG(La->_axis);
        E_DEBUG(L->_angle);
        E_DEBUG(L->_cos_angle);
        E_DEBUG(Lunit);
        E_DEBUG(axis);
        E_DEBUG(Lunit % axis);
      }
      if ( do_ray() )
        goto rtn;
      break;

    case Light::ILLUMINATE:
      La->L = L->getPoint() - P;
      lightdist = ~(La->L);
      Lunit = La->L / lightdist;

      // Make sure that this light ray falls within
      // the cone specified by the shader's illuminate()
      // stmt.
      //
      if ( angle_cos < -1.0 || (Lunit % axis) >= angle_cos ) {
        // Make sure that this light ray falls within the
        // the cone specified by the light's illuminance().
        if ( La->_cos_angle < -1.0 || (Lunit % La->_axis) >= La->_cos_angle ) {
          if ( do_ray() )
            goto rtn;
        }
      }
      break;

    default:
      abort(); break;
    }

    // try another sample
    next();
  }

rtn:
  return L != NULL;
}

int LightIterator::do_ray()
{
  // Prepare Surface shader.
  // L points from surface P to light position.
  S->L = Lunit;

  // Check for shadows between P and L * lightdist.
  Ray R(P, S->L);
  Prim *ignore = L->_isanarealight ? (Prim*) (AreaLight*) L : 0;

  if ( Scene::current->isShadowed(R.fix(S->Ng), lightdist, ignore ) ) {
    S->Cl = 0;
    return 0; // in shadow
  } else {
    // Call the light() shader.
    La->light();

    if ( 0 && La->_type == Light::SOLAR ) {
      E_DEBUG(S);
      E_DEBUG(La);
      E_DEBUG(La->_type);
      E_DEBUG(La->L);
      E_DEBUG(P);
      E_DEBUG(lightdist);
      E_DEBUG(Lunit);
      E_DEBUG(La->Cl);
    }

    // Average the samples.
    S->Cl = sample_coeff * La->Cl;
    S->Ol = 1.0;
    
    // We've got a light sample
    // so return to the surface shader.
    S->_current_light = La;
    return 1;
  }
}
