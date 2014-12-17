//
// vector_imp.hh - class vector2, vector3, class vector4
// KAS 91/02/23
//

#include "eat.hh"
#include <math.h>
#include "scalar.h"

#ifndef vector2_friend
#define vector2_friend vector2
#endif
#ifndef vector3_friend
#define vector3_friend vector3
#endif
#ifndef vector4_friend
#define vector4_friend vector4
#endif

#if vector2_friend == vector2
#define BOP_friend(op,T,TF)
#else
#define BOP_friend(op,T,TF)                               \
friend	T	operator op ( const TF& L, const T& R ) { \
  return T(L.x op R.x, L.y op R.y); }
#endif

//
// Define unary, binary and assignment operator definintion macros
//
#define	UOP(op) \
vector2	operator op () const { \
	return vector2 ( op x, op y ); }
#define	BOP(op) \
friend	vector2	operator op ( const vector2& L, const vector2_friend& R ) { \
  return vector2 ( L.x op R.x, L.y op R.y ); }                          \
 BOP_friend(op,vector2,vector2_friend)                                  \
friend	vector2	operator op ( scalar L, const vector2& R ) { \
	return vector2 ( L op R.x, L op R.y ); } \
friend	vector2	operator op ( const vector2& L, scalar R ) { \
	return vector2 ( L.x op R, L.y op R ); }
#define	AOP(op) \
vector2&	operator op ( const vector2& R ) { \
	x op R.x; y op R.y; return *this; } \
vector2&	operator op ( scalar R ) { \
	x op R; y op R; return *this; }
#define	ROP(op,join) \
friend	int	operator op ( const vector2& L, const vector2& R ) { \
	return L.x op R.x join L.y op R.y; } \
friend	int	operator op ( const vector2& L, scalar R ) { \
	return L.x op R join L.y op R; } \
friend	int	operator op ( scalar L, const vector2& R ) { \
	return L op R.x join L op R.y; }


class vector2 {
public:
	scalar	x, y;

	vector2() {}
	vector2 ( scalar s ) : x(s), y(s) {}
	vector2 ( scalar X, scalar Y ) :
		x(X), y(Y) {}

  int tuples() const { return 2; }
  scalar *begin() { return &x; }
  const scalar *begin() const { return &x; }
  scalar *end() { return &x + tuples(); }
  const scalar *end() const { return &x + tuples(); }

	scalar&		operator[](int i) { return (&x)[i]; }
	scalar		operator[](int i) const { return (&x)[i]; }

	vector2& 	negate() { x = - x; y = - y; return *this; }

	UOP(-)
	BOP(+)
	BOP(-)
	BOP(/)
	BOP(*)
	AOP(+=)
	AOP(-=)
	AOP(/=)
	AOP(*=)
	ROP(==,&&)
	ROP(!=,||)
	ROP(<,&&)
	ROP(<=,&&)
	ROP(>,&&)
	ROP(>=,&&)

friend	scalar	operator % ( const vector2& L, const vector2& R ) {
		return L.x * R.x + L.y * R.y; }
	scalar	operator ~ () const { return sqrt((*this) % (*this)); }

  friend vector2 unit(const vector2 &x) { return x * (1 / ~x); }
  vector2& normalize() { return (*this) *= (1 / ~(*this)); }

  friend	std::ostream&	operator << ( std::ostream& os, const vector2& p ) {
		return os << '[' << p.x << ' ' << p.y << ']';
	}
  friend	std::istream&	operator >> ( std::istream& is, vector2& p ) {
		if ( eat(is,'[') ) {
			is >> p.x >> p.y;
		}
		eat(is,']');
		return is;
	}
};

#undef	ROP
#undef	UOP
#undef	BOP
#undef	AOP
#undef BOP_friend

#if vector3_friend == vector3
#define BOP_friend(op,T,TF)
#else
#define BOP_friend(op,T,TF) \
friend	T	operator op ( const TF& L, const T& R ) { \
  return T(L.x op R.x, L.y op R.y, L.z op R.z ); }
#endif

//
// Define unary, binary and assignment operator definintion macros
//
#define	UOP(op) \
vector3	operator op () const { \
	return vector3 ( op x, op y, op z ); }
#define	BOP(op) \
friend	vector3	operator op ( const vector3& L, const vector3_friend& R ) { \
	return vector3 ( L.x op R.x, L.y op R.y, L.z op R.z ); } \
 BOP_friend(op,vector3,vector3_friend)                       \
friend	vector3	operator op ( scalar L, const vector3& R ) { \
	return vector3 ( L op R.x, L op R.y, L op R.z ); } \
friend	vector3	operator op ( const vector3& L, scalar R ) { \
	return vector3 ( L.x op R, L.y op R, L.z op R ); }
#define	AOP(op) \
vector3&	operator op ( const vector3& R ) { \
	x op R.x; y op R.y; z op R.z; return *this; } \
vector3&	operator op ( scalar R ) { \
	x op R; y op R; z op R; return *this; }
#define	ROP(op,join) \
friend	int	operator op ( const vector3& L, const vector3& R ) { \
	return L.x op R.x join L.y op R.y join L.z op R.z; } \
friend	int	operator op ( const vector3& L, scalar R ) { \
	return L.x op R join L.y op R join L.z op R; } \
friend	int	operator op ( scalar L, const vector3& R ) { \
	return L op R.x join L op R.y join L op R.z; }

class vector3 : public vector2 {
public:
	scalar	z;

	vector3 () : vector2() {}
	vector3 ( scalar s ) : vector2(s), z(s) {}
	vector3 ( scalar X, scalar Y, scalar Z = 0.0) : vector2(X,Y), z(Z) {}
	vector3 ( const vector2& p, scalar Z = 0.0 ) : vector2(p), z(Z) {}
	vector2 v2() const { return vector2 ( x / z, y / z); }

	int		tuples() const { return 3; }
  scalar *end() { return &x + tuples(); }
  const scalar *end() const { return &x + tuples(); }

	vector3&	negate() { x = - x; y = - y; z = - z; return *this; }

	UOP(-)
	BOP(+)
	BOP(-)
	BOP(/)
	BOP(*)
	AOP(+=)
	AOP(-=)
	AOP(/=)
	AOP(*=)
	ROP(==,&&)
	ROP(!=,||)
	ROP(<,&&)
	ROP(<=,&&)
	ROP(>,&&)
	ROP(>=,&&)

friend	scalar	operator % ( const vector3& L, const vector3& R ) {
		return L.x * R.x + L.y * R.y + L.z * R.z; }
	scalar	operator ~ () const { return sqrt((*this) % (*this)); }

  friend vector3 unit(const vector3 &x) { return x * (1 / ~x); }
  vector3& normalize() { return (*this) *= (1 / ~(*this)); }

friend	vector3	operator ^ ( const vector3& L, const vector3& R ) {
		return vector3 (L.y * R.z - L.z * R.y,
				R.x * L.z - R.z * L.x,
				L.x * R.y - L.y * R.x );
	}
  vector3&	operator ^= ( const vector3& R ) { return *this = *this ^ R; }


  friend	std::ostream&	operator << ( std::ostream& os, const vector3& p ) {
		return os << '[' << p.x << ' ' << p.y << ' ' << p.z << ']';
	}
  friend	std::istream&	operator >> ( std::istream& is, vector3& p ) {
		if ( eat(is,'[') ) {
			is >> p.x >> p.y >> p.z;
		}
		eat(is,']');
		return is;
	}
};
#undef	ROP
#undef	UOP
#undef	BOP
#undef	AOP
#undef BOP_friend

#if vector4_friend == vector4
#define BOP_friend(op,T,TF)
#else
#define BOP_friend(op,T,TF) \
friend	T	operator op ( const TF& L, const T& R ) { \
  return T(L.x op R.x, L.y op R.y, L.z op R.z, L.w op R.w); }
#endif

//
// vector4
//
#define	BOP(op) \
friend	vector4	operator op ( const vector4& L, const vector4_friend& R ) { \
	return vector4 ( L.x op R.x, L.y op R.y, L.z op R.z, L.w op R.w ); } \
 BOP_friend(op,vector4,vector4_friend)                       \
friend	vector4	operator op ( scalar L, const vector4& R ) { \
	return vector4 ( L op R.x, L op R.y, L op R.z, L op R.w ); } \
friend	vector4	operator op ( const vector4& L, scalar R ) { \
	return vector4 ( L.x op R, L.y op R, L.z op R, L.w op R ); }
#define	AOP(op) \
vector4&	operator op ( const vector4& R ) { \
	x op R.x; y op R.y; z op R.z; w op R.w; return *this; } \
vector4&	operator op ( scalar R ) { \
	x op R; y op R; z op R; w op R; return *this; }
#define	UOP(op) \
vector4	operator op () const { \
	return vector4 ( op x, op y, op z, op w ); }
#define	ROP(op,join) \
friend	int	operator op ( const vector4& L, const vector4& R ) { \
	return L.x op R.x join L.y op R.y join L.z op R.z join L.w op R.w; } \
friend	int	operator op ( const vector4& L, scalar R ) { \
	return L.x op R join L.y op R join L.z op R join L.w op R; } \
friend	int	operator op ( scalar L, const vector4& R ) { \
	return L op R.x join L op R.y join L op R.z join L op R.w; }

class vector4 : public vector3 {
public:
	scalar	w;

	vector4 () : vector3() {}
	vector4 ( scalar s, scalar W = 1.0 ) : vector3(s), w(W) {}
	vector4 ( scalar X, scalar Y, scalar Z, scalar W = 1.0 ) :
		vector3(X,Y,Z), w(W) {}
	vector4 ( const vector3& p, scalar W = 1.0 ) : vector3(p), w(W) {}
	vector3 v3() const { return vector3 ( x / w, y / w, z / w); }

	int		tuples() const { return 4; }
  scalar *end() { return &x + tuples(); }
  const scalar *end() const { return &x + tuples(); }

	vector4&	negate() { x = - x; y = - y; z = - z; w = - w; return *this; }

	UOP(-)
	BOP(+)
	BOP(-)
	BOP(*)
	BOP(/)
	AOP(+=)
	AOP(-=)
	AOP(*=)
	AOP(/=)
	ROP(==,&&)
	ROP(!=,||)
	ROP(<,&&)
	ROP(<=,&&)
	ROP(>,&&)
	ROP(>=,&&)

friend	scalar	operator % ( const vector4& L, const vector4& R ) {
	return L.x * R.x + L.y * R.y + L.z * R.z + L.w * R.w; }
	scalar  operator ~ () const { return sqrt((*this) % (*this)); }

  friend vector4 unit(const vector4 &x) { return x * (1 / ~x); }
  vector4& normalize() { return (*this) *= (1 / ~(*this)); }


  friend	std::ostream&	operator << ( std::ostream& os, const vector4& p ) {
	return os << '[' << p.x << ' ' << p.y << ' ' << p.z << ' ' << p.w << ']'; }
  friend	std::istream&	operator >> ( std::istream& is, vector4& p ) {
		if ( eat(is,'[') )
			is >> p.x >> p.y >> p.z >> p.w;
		eat(is,']');
		return is;
	}
};

#undef	ROP
#undef	UOP
#undef	BOP
#undef	AOP
#undef BOP_friend


#undef vector2_friend
#undef vector3_friend
#undef vector4_friend

