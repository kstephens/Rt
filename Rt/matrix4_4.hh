//
// matrix4_4.h - class matrix4_4
// KAS 91/02/26
//
#ifndef	__Rt_matrix4_4_hh
#define	__Rt_matrix4_4_hh

class matrix4_4 {
	scalar	m[4][4];
	void	add ( const matrix4_4& l, const matrix4_4& r);
	void	sub ( const matrix4_4& l, const matrix4_4& r);
public:
	matrix4_4 () {}
	matrix4_4 ( scalar s ) { diagonal(s); }
	matrix4_4 ( scalar M[][4] );

	scalar*	operator [] (int r) { return m[r]; }
	const scalar*	operator [] (int r) const { return m[r]; }


friend	matrix4_4	operator + ( const matrix4_4& l, const matrix4_4& r ) {
		matrix4_4	temp;
		temp.add(l,r);
		return temp;
	}
	matrix4_4&	operator += ( const matrix4_4& r ) {
		add(*this, r);
		return *this;
	}

friend	matrix4_4	operator - ( const matrix4_4& l, const matrix4_4& r ) {
		matrix4_4	temp;
		temp.sub(l,r);
		return temp;
	}
	matrix4_4&	operator -= ( const matrix4_4& r ) {
		sub(*this, r);
		return *this;
	}

	matrix4_4	operator * ( scalar s ) const;
friend	matrix4_4	operator * ( scalar s, const matrix4_4& M ) {
		return M * s;
	}
	matrix4_4	operator / ( scalar s ) const { return *this * (1.0 / s); }
	matrix4_4	operator * ( const matrix4_4& M ) const;
friend	vector3	operator * ( const vector3& p, const matrix4_4& M );
friend	vector4	operator * ( const vector4& p, const matrix4_4& M );

	matrix4_4&	operator *= ( scalar s );
	matrix4_4&	operator /= ( scalar s ) { return *this *= (1.0 / s); }
	matrix4_4&	operator *= ( const matrix4_4& M ) { return *this = (*this) * M; }
friend	vector3&	operator *= ( vector3& p, const matrix4_4& M ) { return p = p * M; }
friend	vector4&	operator *= ( vector4& p, const matrix4_4& M ) { return p = p * M; }

	void	gaussj();			// inverse
	matrix4_4&	inverse() { gaussj(); return *this; }
	matrix4_4	operator ~ () const { return matrix4_4(*this).inverse(); }

	matrix4_4&	diagonal( scalar s );
	matrix4_4&	identity() { return diagonal(1.0); }

  friend	std::ostream&	operator << ( std::ostream& os, const matrix4_4& M );
  friend	std::istream&	operator >> ( std::istream& is, matrix4_4& M );

};

#endif


