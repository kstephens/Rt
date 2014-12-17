#ifndef	__Xforms_hh
#define	__Xforms_hh

#include "Xform.hh"
#include "angle.hh"
#include "vector.hh"

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
  Perspective (scalar fov) {
    matrix4_4 m; m.identity();
    // FIXME
    know_invmat = 0;
  }
};

class Translate : public Xform {
public:
  Translate(scalar x, scalar y, scalar z) {
    mat.identity();
    mat[3][0] = x; mat[3][1] = y; mat[3][2] = z;
    invmat.identity();
    invmat[3][0] = - x; invmat[3][1] = - y; invmat[3][2] = - z;
    know_invmat = 1;
  }
};

class Rotate : public Xform {
  void rotate(scalar _cos, scalar _sin, int axis) {
    int	a1 = (axis + 1) % 3;
    int	a2 = (axis + 2) % 3;
    mat[a1][a1] = mat[a2][a2] = _cos;
    mat[a2][a1] = -(mat[a1][a2] = _sin);
  }
  void rotate(angle ang, int axis /* 0=X, 1=Y, 2=Z */) {
    rotate(cos(ang), sin(ang), axis);
  }
  void rotate(scalar w, scalar x, scalar y, scalar z) {
    mat[0][0] = 1 - 2*y*y - 2*z*z;  mat[0][1] = 2*x*y - 2*z*w;     mat[0][2] = 2*x*z + 2*y*w; 
    mat[1][0] = 2*x*y + 2*z*w;      mat[1][1] = 1 - 2*x*x - 2*z*z; mat[1][2] = 2*y*z - 2*x*w; 
    mat[2][0] = 2*x*z - 2*y*w;      mat[2][1] = 2*y*z + 2*x*w;     mat[2][2] = 1 - 2*x*x - 2*y*y;
    mat[0][3] = mat[1][3] = mat[2][3] = 0;
    mat[3][0] = mat[3][1] = mat[3][2] = 0; mat[3][3] = 1;
  }
  void rotate(angle ang, const vector &axis) {
    angle ang_2 = ang / 2;
    vector axis_n = unit(axis) * sin(ang_2);
    rotate(cos(ang_2), axis_n.x, axis_n.y, axis_n.z);
  }

public:
  Rotate(angle ang, const vector &axis) {
    rotate(ang, axis);
    know_invmat = 0;
  }
  Rotate(angle ang, scalar dx, scalar dy, scalar dz) {
    vector axis(dx, dy, dz);
    rotate(ang, axis);
    know_invmat = 0;
  }
  Rotate(angle ang, int axis) {
    mat.identity();
    rotate(ang, axis);
    know_invmat = 0;
  }
};

class Scale : public Xform {
public:
  Scale(scalar sx, scalar sy, scalar sz) {
    mat.identity();
    mat[0][0] = sx; mat[1][1] = sy; mat[2][2] = sz;
    know_invmat = 0;
  }
};

class Skew : public Xform {
public:
  Skew ( scalar angle, scalar dx1, scalar dy1, scalar dz1, scalar dx2, scalar dy2, scalar dz2 ) {
    mat.identity();
    // FIXME
    know_invmat = 0;
  }
};

#endif


