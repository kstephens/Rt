//
// AreaLight.hh - class AreaLight
// KAS 91/06/25
//
#ifndef	__AreaLight_hh
#define	__AreaLight_hh

#include "Light.hh"
#include "Shader.hh"
#include "Prim.hh"

class	AreaLight : public Light, public Prim, public Shader {
	Prim*	prim;
	Light*	_light;
friend	class Light;
public:
	AreaLight ( Prim* p, Light* l, int NSAMPLES = 8 ) :
		Light(), Prim(), Shader(), prim(p), _light(l) {
		prim->surface = (Shader*) this;
		Light::_isanarealight = 1;
		Light::_nsamples = NSAMPLES;
	}
	~AreaLight() {}

	//
	// Prim stuff deferr it to the prim
	//
	
	Point	P(const Param& _p) { return prim->P(_p); }
	Param	p(const Point& _p) { return prim->p(_p); }

	Point	Ngp(const Param& _p) { return prim->Ngp(_p); }
	Point	NgP(const Point& _p) { return prim->NgP(_p); }
	Point	Ng(RPI* _p); // { return prim->Ng(_p); }

	Point	dPdup(const Param& _p) { return prim->dPdup(_p); }
	Point	dPduP(const Point& _p) { return prim->dPduP(_p); }
	Point	dPdu(RPI* _p); // { return prim->dPdu(_p); }

	Point	dPdvp(const Param& _p) { return prim->dPdvp(_p); }
	Point	dPdvP(const Point& _p) { return prim->dPdvP(_p); }
	Point	dPdv(RPI* _p); // { return prim->dPdv(_p); }

	Point	dPdwp(const Param& _p) { return prim->dPdwp(_p); }
	Point	dPdwP(const Point& _p) { return prim->dPdwP(_p); }
	Point	dPdw(RPI* _p) { return prim->dPdw(_p); }

	RPIList	intersect( const Ray& r ) { return prim->intersect(r); }
	int	intersects( const Ray& r ) { return prim->intersects(r); }

	Point	randomOn() { return prim->randomOn(); }
	Point	randomIn() { return prim->randomIn(); }

	Point	getPoint() { return prim->wrandomOn(); }

	Light*	getActualLight() { return _light; }

	void	light () { _light->light(); }

	//
	// Return the light shaders value!
	//
	void	shader () {
		_light->L = - ((Shader*) this)->I;
		_light->light();
		((Shader*) this)->Ci = _light->Cl;
		((Shader*) this)->Oi = 1.0;
	}
};

#endif


