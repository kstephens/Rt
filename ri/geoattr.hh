//
// GeoAttribute.hh - class GeoAttribute
// KAS 91/06/25
//
#ifndef	__ri_GeoAttr_hh
#define	__ri_GeoAttr_hh

#include "ri/ri.h"
#endif

#include "ri/RiMatrix.h"

class GeoAttributes {
  RiMatrix	_transform;	// Object to World transform
  RiMatrix	_itransform;	// World to Object transform
  char		know_it;
public:
  GeoAttributes() {
    identity();
  }
  const RiMatrix&	transform () const {
    return _transform;
  }
  const RiMatrix&	itransform () {
    if ( ! know_it ) {
      RiMatrix_Invert(itransform = _transform);
      know_it = 1;
    }
    return itransform;
  }
  void		RiIdentity () {
    RiMatrix_identity(&_transform);
    RiMatrix_Identity(&_itransform);
    know_it = 1;
  }

  void		RiTransform (const RiMatrix& transform) {
    _transform = transform;
    know_it = 0;
  }

  void		RiConcatTransform (const RiMatrix& transform) {
    RiMatrix_Concat(&_transform, &transform );
    know_it = 0;
  }

  void		RiPerspective ( RiFloat fov ) {
    RiMatrix_Concat(&_tranform, RiMatrix_Perspective(fov));
    know_it = 0;
  }

  //	void		RiRotate ( RiFloat angle, RiFloat dx, RiFloat dy, RiFloat dz );
  void		RiRotate ( RiFloat angle, RiInt axis ) {
    RiMatrix_Concat(&_transform, RiMatrix_RiRotate( angle, axis ) );
    know_it = 0;
  }
  void		RiScale ( RiFloat sx, RiFloat sy, RiFloat sz ) {
    RiMatrix_Concat(&_transform, RiMatrix_Scale( sx, sy, sz ));
    know_it = 0;
  }
//	void		RiSkew ( RiFloat angle, ... );
};
#endif
