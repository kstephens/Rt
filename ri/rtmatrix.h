/*
** RtMatrix.h - RtMatrix functions
** KAS 91/06/25
*/
#ifndef	__ri_RtMatrix_h
#define	__ri_RtMatrix_h

#include "ri/ri.h"

#ifdef	__cplusplus
extern "C" {
#endif

extern void	RtMatrix_Invert(RtMatrix*);
extern void	RtMatrix_Mult(RtMatrix* dst, RtMatrix* left, RtMatrix* right );
extern void	RtMatrix_Concat(RtMatrix*, RtMatrix*);
extern void	RtMatrix_SetIdentity(RtMatrix*);
extern RtMatrix*	RtMatrix_Identity();
extern RtMatrix*	RtMatrix_Perspective(RtFloat fov);
extern RtMatrix*	RtMatrix_Translate(RtFloat dx, RtFloat dy, RtFloat dz );
extern RtMatrix*	RtMatrix_Rotate(RtFloat angle, RtInt axis );
/* extern RtMatrix*	RtMatrix_Rotate(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz ); */
extern RtMatrix*	RtMatrix_Scale(RtFloat sx, RtFloat sy, RtFloat sz );
extern RtMatrix*	RtMatrix_Skew(RtFloat angle,
	RtFloat dx1, RtFloat dy1, RtFloat dz1,
	RtFloat dx2, RtFloat dy2, RtFloat dz2 );

#ifdef __cplusplus
}
#endif

#endif
