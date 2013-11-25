/*
// RiNoise.h
// KAS 91/06/25
*/
#ifndef	__ri_RiNoise_h
#define	__ri_RiNoise_h

#include "ri/ri.h"

#ifdef	__cplusplus
extern "C" {
#endif

extern	RtFloat	RiFloatNoiseFloat(RtFloat v);
extern	RtFloat	RiFloatNoiseFloat2(RtFloat u, RtFloat v);
extern	RtFloat	RiFloatNoisePoint(RtPoint* pt);

extern	void	RiPointNoiseFloat(RtPoint*, RtFloat v);
extern	void	RiPointNoiseFloat2(RtPoint*, RtFloat u, RtFloat v);
extern	void	RiPointNoisePoint(RtPoint*, RtPoint* pt);

extern	void	RiColorNoiseFloat(RtColor*, RtFloat v);
extern	void	RiColorNoiseFloat2(RtColor*, RtFloat u, RtFloat v);
extern	void	RiColorNoisePoint(RtColor*, RtPoint* pt);

extern	void	RiInitNoise();

#ifdef	__cplusplus
}
#endif
#endif
