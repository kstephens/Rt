/*
** RtMatrix.c
** KAS 91/06/29
*/
#include "ri/ri.h"
#include "ri/RtMatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ri/assign.h"

void
RtMatrix_Inverse(RtMatrix* M) {

#define	SWAP(a,b) { RtFloat temp=a; a=b; b=temp; }
#define	fabs(x) (((x) < 0.0) ? -(x): (x))
#define	m (*M)

	int	indxc[4],
		indxr[4],
		ipiv[4];

	int	i, icol, irow, j, k, l, ll;
	RtFloat	big, dum, pivinv; // , temp;

	for ( j = 0; j < 4; j ++ )
		ipiv[j] = 0;
	for ( i = 0; i < 4; i ++ ) {
		big = 0.0;
		for ( j = 0; j < 4; j ++ )
			if ( ipiv[j] != 1 )
				for ( k = 0; k < 4; k ++ ) {
					if ( ipiv[k] == 0 ) {
		RtFloat	temp = fabs( m[j][k]);
						if ( temp >= big ) {
							big = temp;
							irow = j;
							icol = k;
						}
					} else if ( ipiv[k] > 1 ) {
						fprintf( stderr, "FATAL: gaussj: singular matrix\n");
						exit ( 1 );
					}
				}
		++ (ipiv[icol]);
		if ( irow != icol ) {
			for ( l = 0; l < 4; l ++ )
				SWAP( m[irow][l], m[icol][l] );
		}
		indxr[i] = irow;
		indxc[i] = icol;
		if ( m[icol][icol] == 0.0 ) {
			fprintf(stderr, "FATAL: RtMatrix_Invert: singular matrix\n");
			exit ( 1 );
      }
		pivinv = 1.0 / m[icol][icol];
		m[icol][icol] = 1.0;
		for ( l = 0; l < 4; l ++ )
			m[icol][l] *= pivinv;
		for ( ll = 0; ll < 4; ll ++ )
			if ( ll != icol ) {
				dum = m[ll][icol];
				m[ll][icol] = 0.0;
				for ( l = 0; l < 4; l ++ )
					m[ll][l] -= m[icol][l] * dum;
//				for ( l = 0; l < 4; l ++ )
//					m[ll][l] -= m[icol][l] * dum;
			}
	}
	for ( l = 3; l >= 0; l -- ) {
		if ( indxr[l] != indxc[l] )
			for ( k = 0; k < 4; k ++ )
				SWAP( m[k][indxr[l]], m[k][indxc[l]] );
	}
#undef	m
#undef	SWAP
#undef	fabs
}

void
RtMatrix_Mult(RtMatrix* DST, RtMatrix* L, RtMatrix* R) {
#define	dst (*DST)
#define	l (*L)
#define	r (*R)
	int	i, j, k;
	for ( i = 0; i < 4; i ++ ) {
		for ( j = 0; j < 4; j ++ ) {
			RtFloat	sum;

			sum = 0.0;
			for ( k = 0; k < 4; k ++ )
				sum += l[i][k] * r[k][j];
			dst[i][j] = sum;
		}
	}

#undef r
#undef l
#undef dst
}

void
RtMatrix_Concat(RtMatrix* DST, RtMatrix* M) {
	RtMatrix	temp;
	RtMatrix_Mult(&temp, DST, M);
	ASSIGN((*DST), temp);
}

static	RtMatrix	identity = {
{ 1.0, 0.0, 0.0, 0.0 },
{ 0.0, 1.0, 0.0, 0.0 },
{ 0.0, 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 0.0, 1.0 }
};

void
RtMatrix_Identity(RtMatrix m)
{
  memcpy(m, identity, sizeof(identity));
}

#define	DEGREES(x) ((x) * (M_PI / 180.0))
#define	RADIANS(x) ((x) * (180.0 / M_PI))

void
RtMatrix_Perspective(RtMatrix temp, RtFloat fov ) {
	RtFloat	s, c;

	RtMatrix_Identity(temp);	

	fov = RADIANS(fov) * 0.5;
	s = sin(fov);
	c = cos(fov);

	temp[0][0] =
			temp[1][1] = c;
					temp[2][2] = s; temp[2][3] = s;
							  temp[3][3] = 0;
}

void
RtMatrix_Scale(RtMatrix temp, RtFloat sx, RtFloat sy, RtFloat sz) {
	RtMatrix_Identity(temp);
	temp[0][0] = sx;
	temp[1][1] = sy;
	temp[2][2] = sz;
}

void
RtMatrix_Translate(RtMatrix temp, RtFloat dx, RtFloat dy, RtFloat dz) {
	RtMatrix_Identity(temp);
	temp[0][3] = dx;
	temp[1][3] = dy;
	temp[2][3] = dz;
}

void
RtMatrix_Rotate(RtMatrix temp, RtFloat angle, RtInt axis ) {
	int	i, j;
	angle = RADIANS(angle);

	i = (axis + 1) % 3;
	j = (axis + 2) % 3;

	RtMatrix_Identity(temp);

	temp[i][i] = temp[j][j] = cos(angle);
	temp[j][i] = -(temp[i][j] = sin(angle));
}
