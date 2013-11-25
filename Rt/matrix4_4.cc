//
// matrix4_4.cc - class matrix4_4
// KAS 91/02/26
//
#ifdef matrix4_4_include

#include <iostream>
#include "Rt/matrix4_4.hh"
#include "Rt/debug.hh"
#include <stdlib.h>
#include <string.h>

matrix4_4::matrix4_4( scalar M[][4] )
{
  memcpy(m, M, sizeof(scalar)* 4 * 4);
}

void
matrix4_4::add( const matrix4_4& l, const matrix4_4& r ) {
	for ( int i = 0; i < 4; i ++ )
		for ( int j = 0; j < 4; j ++ )
			(*this)[i][j] = l[i][j] + r[i][j];
}

void
matrix4_4::sub( const matrix4_4& l, const matrix4_4& r ) {
	for ( int i = 0; i < 4; i ++ )
		for ( int j = 0; j < 4; j ++ )
			(*this)[i][j] = l[i][j] - r[i][j];
}

matrix4_4
matrix4_4::operator * ( scalar s ) const {
	matrix4_4	n;
	for ( int i = 0; i < 4; i ++ )
		for ( int j = 0; j < 4; j ++ )
			n.m[i][j] = m[i][j] * s;
        return n;
}

matrix4_4
matrix4_4::operator * ( const matrix4_4& M ) const {
	matrix4_4	n;
	for ( int i = 0; i < 4; i ++ )
		for ( int j = 0; j < 4; j ++ ) {
			scalar	sum = 0.0;
			for ( int k = 0; k < 4; k ++ )
				sum += m[i][j] * M.m[i][j];
			n.m[i][j] = sum;
		}
	return n;
}


vector3
operator * ( const vector3& p, const matrix4_4& M )
{
  scalar t[3];
  // E_DEBUG(M);
  for ( int i = 0; i < 3; i ++ ) {
    scalar sum = M.m[3][i]; // * p[3] == 1.0
    for ( int j = 0; j < 3; j ++ )
      sum += M.m[j][i] * p[j];
    t[i] = sum;
  }
  scalar unit = 1.0 / (M.m[0][3] + M.m[1][3] + M.m[2][3] + M.m[3][3]);
  return vector3 ( t[0] * unit, t[1] * unit, t[2] * unit );
}

vector4
operator * ( const vector4& p, const matrix4_4& M ) {
	vector4	n;
	for ( int i = 0; i < 4; i ++ ) {
		scalar sum = 0.0;
		for ( int j = 0; j < 4; j ++ )
			sum += M.m[j][i] * p[i];
		n[i] = sum;
	}
	return n;
}

matrix4_4&
matrix4_4::operator *= ( scalar s ) {
	for ( int i = 0; i < 4; i ++ )
		for ( int j = 0; j < 4; j ++ )
			m[i][j] *= s;
	return *this;
}

//
// gaussj() derived from _Numerical Recipes in C_
//

inline	void	SWAP ( scalar &a, scalar &b ) { scalar temp=a; a=b; b=temp; }
inline	scalar	fabs ( scalar x ) { return (x < 0.0) ? - x : x; }

 
void
matrix4_4::gaussj () {
	int	indxc[4],
		indxr[4],
		ipiv[4];

	int	i, icol, irow, j, k, l, ll;
	scalar	big, dum, pivinv, temp;

	for ( j = 0; j < 4; j ++ )
		ipiv[j] = 0;
	for ( i = 0; i < 4; i ++ ) {
		big = 0.0;
		for ( j = 0; j < 4; j ++ )
			if ( ipiv[j] != 1 )
				for ( k = 0; k < 4; k ++ ) {
					if ( ipiv[k] == 0 ) {
		scalar	temp = fabs( m[j][k]);
						if ( temp >= big ) {
							big = temp;
							irow = j;
							icol = k;
						}
					} else if ( ipiv[k] > 1 ) {
                                          std::cerr << "FATAL: matrix4_4:\n" << (*this) << ": gaussj: singular matrix4_4-1\n";
						abort();
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
                  std::cerr << "FATAL: matrix4_4:\n" << *this << ": gaussj: singular matrix4_4-2\n";
			abort();
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
}


std::ostream&	operator << ( std::ostream& os, const matrix4_4& M ) {
	os << "{ 4 4\n";
	for ( int i = 0; i < 4; i ++ ) {
		for ( int j = 0; j < 4; j ++ )
			os << M.m[i][j] << ' ';
		os << '\n';
	}
	return os << '}';
}


std::istream&	operator >> ( std::istream& is, matrix4_4& M ) {
	if ( eat(is,'{') ) {
		int	m, n;
		is >> m >> n;
		if ( m != 4 || n != 4 )
                  is.clear(std::ios::badbit|is.rdstate());
                else
			for ( int i = 0; i < 4; i ++ )
				for ( int j = 0; j < 4; j ++ )
					is >> M.m[i][j];
	}
	return is;
}


matrix4_4&
matrix4_4::diagonal( scalar s ) {
  memset(m, sizeof(m), 0);
  m[0][0] = m[1][1] = m[2][2] = m[3][3] = s;
  return *this;
}

#endif
