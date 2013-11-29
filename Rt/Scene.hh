//
// Scene.hh - class Scene
// KAS 91/06/25
//
#ifndef	__Scene_hh
#define __Scene_hh

#include "Prim.hh"
#include "Light.hh"
#include "AreaLight.hh"

class Scene {
  Prim *prims;
  Light *_lights;
  Color	ambientlight;

  Color dolist(RPI* rpi, int depth) const;
public:
  static Scene *current;
  Shader *background_shader;

  Scene()
    : prims(0), _lights(0), ambientlight(0), background_shader(0)
  {
  }

	Prim*	add ( Prim* p) {
		p->next = prims;
		prims = p;
                return p;
	}

	Light*	add ( Light* l ) {
		l->init();
		ambientlight += l->getambient();
		l->next = _lights;
		_lights = l;
                return l;
	}
	void	add ( AreaLight* l ) {
		add( (Prim*) l );
		add( (Light*) l );
	}
	Light*	lights() const {
		return _lights;
	}

	//	
	// all Ray's are in World coordinates
	//
	int	isShadowed(const Ray& ray, scalar dist, Prim* ignore ) const;
	RPIList	intersect(const Ray& ray) const;
	Color	trace(const Ray& ray, int depth = 4) const;
	Color	ambient() { return ambientlight; }
};

#endif

