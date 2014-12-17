/*
// ri.h - RenderMan Declarations
// KAS 91/06/29
*/
/* from RenderMan Interface version 3.0 */
#ifndef	__ri_ri_h
#define	__ri_ri_h

#ifdef	__cplusplus
extern "C" {
#endif

/* p. 4 */
typedef	char	*RtToken;
typedef	short	*RtBoolean;
typedef	long	RtInt;
typedef	float	RtFloat;
typedef	float	RtColor[3];
typedef	float	RtPoint[3];
typedef	float	RtMatrix[4][4];
typedef	float	RtBasis[4][4];
typedef	float	RtBound[6];
typedef	float	(*RtFloatFunc)();
typedef	void	(*RtFunc)();
typedef	void	*RtUntyped;

typedef	RtUntyped	RtObjectHandle;
typedef	RtUntyped	RtLightHandle;

#define	RI_FALSE	0
#define	RI_TRUE		1
#define	RI_INFINITY	1e+8
#define	RI_EPSILON	1e-8
#define	RI_RGB		"rgb"
#define	RI_NULL		0

/* p. 105 */
extern	void		RiAtmosphere(/* RtToken name, ... */);	/* p. 26 */
extern	RtLightHandle	RiAreaLightSource(/* RtToken name, ... */);	/* p. 24 */
extern	void		RiAttributeBegin(/**/);		/* p. 9, 21 */
extern	void		RiAttributeEnd(/**/);		/* p. 9, 21 */
extern	void		RiAttribute();
extern	void		RiBasis(/* RtBasis ubasis, RtBasis vbasis */); /* p. 38 */
extern	void		RiBegin(/* RtToken name */);		/* p. 6 */
extern	void		RiBound(/* RtBound bound */);		/* p. 28 */
extern	void		RiClipping(/* RtFloat near, RtFloat far */);	/* p. 13 */
extern	void		RiColorSamples(/* RtInt n, RtFloat nRGB[], RtFloat RGBn[] */);		/* p. 20 */
extern	void		RiColor(/* RtColor color */);	/* p. 22 */
extern	void		RiConcatTransform(/* RtMatrix transform */);	/* p. 31 */
extern	void		RiCone(/* RtFloat Height, RtFloat radius, RtFloat thetamax, ... */);	/* p. 44 */
extern	void		RiCoordinateSystem(/* RtToken space */);	/* p. 33 */
extern	void		RiCropWindow(/* RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax */);	/* p. 13 */
extern	void		RiCylinder(/* RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ... */);	/* p. 44 */
extern	RtToken		RiDeclare(/* char* name, char* declaration */);	/* p. 5 */
extern	void		RiDeformation(/* RtToken name, ... */);	/* p. 32 */
extern	void		RiDepthOfField(/* RtFloat fstop, RtFloat focallength, RtFloat focaldistance */);	/* p. 14 */
extern	void		RiDetailRange();
extern	void		RiDetail();
extern	void		RiDisk();
extern	void		RiDisplacement();
extern	void		RiDisplay(/* RtToken name, RtToken type, RtToke mode */);	/* p. 19 */
extern	void		RiEnd(); /* p. 6 */
extern	void		RiErrorMode();
extern	void		RiExposure(/* RiFloat gain, RiFloat gamma */);	/* p. 18 */
extern	void		RiExterior();
extern	void		RiFormat(/* RtInt xres, RtInt yres, RtFloat pixelaspectratio */);	/* p. 11 */
extern	void		RiFrameAspectRatio(/* RtFloat frameaspectration */);	/* p. 12 */
extern	void		RiFrameBegin(/* RtInt frame */);	/* p. 7 */
extern	void		RiFrameEnd(/* */);			/* p. 7 */
extern	void		RiGeneralPolygon();
extern	void		RiGeometricApproximation();
extern	void		RiGeometry();
extern	void		RiHider(/* RtToken type, ... */);	/* p. 19 */
extern	void		RiHyperboloid();
extern	void		RiIdentity();
extern	void		RiIlluminate(/* RtLightHandle light, RtBoolean onoff */);	/* p. 24 */
extern	void		RiImager(/* RtToken name, ... */);	/* p. 18 */
extern	void		RiInterior(/* RtToken name, ... */);	/* p. 26 */
extern	RtLightHandle	RiLightSource(/* RtToken name, ... */);	/* p. 24 */
extern	void		RiMakeBump();
extern	void		RiMakeCubeFaceEnvironment();
extern	void		RiMakeLattLongEnvironment();
extern	void		RiMakeShadow();
extern	void		RiMakeTexture();
extern	void		RiMatte();
extern	void		RiMotionBegin(/**/);	/* p.8 */
extern	void		RiMotionEnd(/**/);	/* p.8 */
extern	void		RiNuPatch();
extern	RtObjectHandle	RiObjectBegin(/**/);	/* p.9 */
extern	void		RiObjectEnd();		/* p.9 */
extern	void		RiObjectInstance();
extern	void		RiOpacity(/* RtColor color */);	/* p. 22 */
extern	void		RiOption(/* RtToken name, ... */);	/* p. 21 */
extern	void		RiOrientation();
extern	void		RiParaboloid();
extern	void		RiPatchMesh();
extern	void		RiPatch();
extern	void		RiPerspective();
extern	void		RiPixelFidelity(/* RtFloat variation */);	/* p. 16 */
extern	void		RiPixelFilter(/* RtFloatFunc filterfunc, RtFloat xwidth, RtFloat ywidth */);	/* p. 17 */
extern	void		RiPixelSamples(/* RtFloat xsamples, RtFloat ysamples */);	/* p. 17 */
extern	void		RiPointsGeneralPolygons();
extern	void		RiPointsPolygons();
extern	void		RiPolygon();
extern	void		RiProcedural();
extern	void		RiProjection(/* RtToken name, ... */);	/* p. 13 */
extern	void		RiQuantize(/* RtToken type, RtInt one, RtInt min, RtInt max, RtFloat ditheramplitude */);	/* p. 18 */
extern	void		RiRelativeDetail(/* RtFloat relativedetail */);	/* p. 20 */
extern	void		RiReverseOrientation();
extern	void		RiRotate();
extern	void		RiScale();
extern	void		RiScreenWindow(/* RtFloat left, RtFloat right, RtFloat top, RtFloat bottom */);	/* p. 12 */
extern	void		RiShadingIterpolation();
extern	void		RiShadingRate();
extern	void		RiShutter(/* RtFloat min, RtFloat max */);	/* p. 15 */
extern	void		RiSides();
extern	void		RiSkew();
extern	void		RiSolidBegin(/**/);	/* p. 8 */
extern	void		RiSolidEnd(/**/);	/* p. 8 */
extern	void		RiSphere();
extern	void		RiSurface(/* RtToken name, ... */);	/* p. 26 */
extern	void		RiTextureCoordinates(/* RtFloat s1, RtFloat t1, RtFloat s2, RtFloat t2, RtFloat s3, RtFloat t3, RtFloat s4, RtFloat t4 */);	/* p. 23 */
extern	void		RiTorus();
extern	void		RiTransformBegin(/**/);	/* p. 9 */
extern	void		RiTransformEnd(/**/);	/* p. 9 */
extern	void		RiTransformPoints();
extern	void		RiTransform();
extern	void		RiTranslate();
extern	void		RiTrimCurve();
extern	void		RiWorldBegin(/* */);	/* p. 7 */
extern	void		RiWorldEnd(/* */);	/* p. 7 */
	
extern	RtFloat		RiGaussianFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);	/* p. 18 */
extern	RtFloat		RiBoxFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);		/* p. 18 */
extern	RtFloat		RiTriangleFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);	/* p. 18 */
extern	RtFloat		RiCatmullRomFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);	/* p. 18 */
	
extern	RtBasis	RiBezierBasis;
extern	RtBasis	RiBSplineBasis;
extern	RtBasis	RiCatmullRomBasis;
extern	RtBasis	RiHermiteBasis;
extern	RtBasis	RiPowerBasis;
	
#ifdef	__cplusplus
}
#endif

#endif
