#ifndef	__Xforms_hh
#define	__Xforms_hh

#include "Xform.hh"
#include "angle.hh"

class Identity : public Xform {
public:
	Identity() { 
		mat.identity();
		invmat.identity();
		know_invmat = 1;
	}
};

class Perspective : public Xform {
public:
	Perspective ( scalar fov ) {
		matrix4_4	m; m.identity();
                know_invmat = 0;
	}
};

class Translate : public Xform {
public:
	Translate ( scalar x, scalar y, scalar z ) {
		mat.identity();
		mat[3][0] = x; mat[3][1] = y; mat[3][2] = z;
                know_invmat = 0;
	}
};

class Rotate : public Xform {
	void	rotate ( angle ang, scalar dx, scalar dy, scalar dz ) {
	}
	void	rotate ( angle ang, int axis /* 0=X, 1=Y, 2=Z */ ) {
          rotate ( cos(ang), sin(ang), axis);
	}
	void	rotate ( scalar _cos, scalar _sin, int axis ) {
		int	a1 = (axis + 1) % 3;
		int	a2 = (axis + 2) % 3;
		mat[a1][a1] = mat[a2][a2] = _cos;
		mat[a2][a1] = -(mat[a1][a2] = _sin);
	}
public:
//	Rotate ( angle ang, scalar dx, scalar dy, scalar dz ) {
	Rotate ( angle ang, int axis ) {
		mat.identity();
		rotate(ang, axis);
                know_invmat = 0;
	}
};

class Scale : public Xform {
public:
	Scale ( scalar sx, scalar sy, scalar sz ) {
		mat.identity();
		mat[0][0] = sx; mat[1][1] = sy; mat[2][2] = sz;
                know_invmat = 0;
	}
};

class Skew : public Xform {
public:
	Skew ( scalar angle, scalar dx1, scalar dy1, scalar dz1, scalar dx2, scalar dy2, scalar dz2 ) {
		mat.identity();
                know_invmat = 0;
	}
};

#endif


