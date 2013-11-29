//
// Scene.hh - class Scene
// KAS 91/06/25
//
#ifndef	__Scene_hh
#define __Scene_hh

#include "Geometry.hh"
#include "Light.hh"
#include "AreaLight.hh"

class Scene {
  Geometry *geos;
  Light *_lights;
  color	ambientlight;

  color dolist(RPI* rpi, int depth) const;
public:
  static Scene *current;
  Shader *background_shader;

  Scene()
    : geos(0), _lights(0), ambientlight(0), background_shader(0)
  {
  }

	Geometry *add(Geometry *g) {
          g->next = geos;
          geos = g;
          return g;
	}

	Light*	add ( Light* l ) {
		l->init();
		ambientlight += l->getambient();
		l->next = _lights;
		_lights = l;
                return l;
	}
	void	add ( AreaLight* l ) {
		add( (Geometry*) l );
		add( (Light*) l );
	}
	Light*	lights() const {
		return _lights;
	}

	//	
	// all Ray's are in World coordinates
	//
	int	isShadowed(const Ray &ray, scalar dist, Geometry *ignore) const;
	RPIList	intersect(const Ray &ray) const;
	color	trace(const Ray& ray, int depth = 4) const;
	color	ambient() { return ambientlight; }
};

#endif

