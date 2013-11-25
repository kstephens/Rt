/*
** RiNoise.c
** KAS 91/06/29
*/
#include "ri/RiNoise.h"
#include "ri/RiRand.h"

static	int	*P;
extern	RtFloat	randtable[];	/* in rand.c */

#define	ABS(x)	((x) < 0 ? -(x) : (x))
#define	phi(i)	P[ABS((i)) % RANDTABLELEN]

/* static */
RtFloat	W(RtFloat t) {
	t = ABS(t);
	return (t < 1.0 ? t * t * (2.0 * t - 3.0) + 1.0 : 0.0);
}

static
RtFloat
GAMMA1(int i) {
	return randtable[phi(i)];
}

static
RtFloat
GAMMA2(int i, int j) {
	register int	l;
	l = i + phi(j);
	return randtable[phi(l)];
}

RtFloat
GAMMA3(int i, int j, int k) {
	register int l;
	l = j + phi(k);
	return  randtable[phi(i) + phi(l)];
}

static
int floor( RtFloat x ) {
	register int	X = (int) x;
	if ( x < 0.0 )
		X --;
	return X;
}

RtFloat	RiFloatNoiseFloat(RtFloat x ) {
	int	fx = floor(x);
	RtFloat	dx = x - (RtFloat) fx;
	RtFloat	g[2];
	g[0] = GAMMA1(fx);
	g[1] = GAMMA1(fx + 1);

	return g[1] + (g[0] - g[1]) * W(dx);
}

RtFloat RiFloatNoiseFloat2(RtFloat x, RtFloat y ) {
	register int	i, j;
	register int	a, b;
	register int	f[2];
	RtFloat	w[2];
	RtFloat	v[2][2];

	f[0] = floor(x);
	f[1] = floor(y);

	w[0] = W(x - (RtFloat) f[0]);
	w[1] = W(y - (RtFloat) f[1]);

	for ( a = 0, i = f[0]; i <= f[0] + 1; a ++, i ++ ) {
		for ( b = 0, j = f[1]; j <= f[1] + 1; b ++, j ++ ) {
			v[0][b] = GAMMA2(i,j);
		}
		v[1][a] = v[0][1] + (v[0][0] - v[0][1]) * w[1];
	}

	return v[1][1] + (v[1][0] - v[1][1]) * w[0];
}

RtFloat	RiFloatNoisePoint(RtPoint* P ) {
#define	p	(*P)
	register int	i, j, k;
	register int	a, b, c;
	RtFloat	v[3][2];
	RtFloat w[3];
	int	f[3];

	f[0] = floor(p[0]);
	f[1] = floor(p[1]);
	f[2] = floor(p[2]);

	w[0] = W(p[0] - (RtFloat) f[0]);
	w[1] = W(p[1] - (RtFloat) f[1]);
	w[2] = W(p[2] - (RtFloat) f[2]);

	for ( a = 0, i = f[0]; i <= f[0] + 1; a ++, i ++ ) {
		for ( b = 0, j = f[1]; j <= f[1] + 1; b ++, j ++ ) {
			for ( c = 0, k = f[2]; k <= f[2] + 1; c ++, k ++ ) {
				v[2][c] = GAMMA3(i,j,k);
			}
			v[1][b] = v[2][1] + (v[2][0] - v[2][1]) * w[2];
		}
		v[0][a] = v[1][1] + (v[1][0] - v[1][1]) * w[1];
	}
	return v[0][1] + (v[0][0] - v[0][1]) * w[0];
#undef p
}

#define	OFFSET1	1000.0
#define	OFFSET2 2000.0

#define	dst (*DST)

void RiPointNoiseFloat(RtPoint *DST, RtFloat u)
{
  RtFloat v;
  v = u - OFFSET1;
  dst[0] = RiFloatNoiseFloat(u);
  dst[1] = RiFloatNoiseFloat2(u, v);
  v = u - OFFSET2;
  dst[2] = RiFloatNoiseFloat2(v, u);
}

void
RiPointNoiseFloat2(RtPoint* DST, RtFloat u, RtFloat v ) {
	RtFloat s[2];

	s[0] = u - OFFSET1;
	s[1] = v - OFFSET1;

	dst[0] = RiFloatNoiseFloat2(s[0], s[1]);

	dst[1] = RiFloatNoiseFloat2(u,v);

	s[0] = u + OFFSET2;
	s[1] = v + OFFSET2;

	dst[2] = RiFloatNoiseFloat2(s[0], s[1]);
	
#undef dst
}


void
RiPointNoisePoint(RtPoint* DST, RtPoint* P) {
#define	dst (*DST)
#define	p (*P)
	RtPoint	s;
	s[0] = p[0] - OFFSET1;
	s[1] = p[1] - OFFSET1;
	s[2] = p[2] - OFFSET1;

	dst[0] = RiFloatNoisePoint(&s);
	
	dst[1] = RiFloatNoisePoint(P);

	s[0] = p[0] + OFFSET2;
	s[1] = p[1] + OFFSET2;
	s[2] = p[2] + OFFSET2;

	dst[2] = RiFloatNoisePoint(&s);
	
#undef dst
#undef p
}


/*
** temporary for all three-tuple color spaces
*/
void	RiColorNoiseFloat(RtColor* color, RtFloat v) {
	RiPointNoiseFloat((RtPoint*) color, v);
}
	
void	RiColorNoiseFloat2(RtColor* color, RtFloat u, RtFloat v) {
	RiPointNoiseFloat2((RtPoint*) color, u, v);
}
void	RiColorNoisePoint(RtColor* color, RtPoint* pt) {
	RiPointNoisePoint((RtPoint*) color, pt);
}

extern	void*	alloc(int size, int len);

void
RiInitNoise()
{
	int	i, n;
	P = (int*) alloc(sizeof(int), RANDTABLELEN);

	for ( n = 0; n < RANDTABLELEN; n ++ )
		P[n] = n;

	for ( n = 0; n < RANDTABLELEN; n ++ ) {
		int	bonk;

		i = (int) (randtable[n] * (RANDTABLELEN - 1));
		bonk = P[n];
		P[n] = P[i];
		P[i] = bonk;
	}
}
