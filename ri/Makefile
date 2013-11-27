CINCLUDES += -I.
LIB_A=libri.a
LDLIBS += -L. -L../Raster -lRaster -lri
include ../common.make

RiRand.o :: randtable.h
randtable.h : tool/makerandtable.t
	tool/makerandtable.t > $@
tool/makerandtable: tool/makerandtable.c
GARBAGE += tool/makerandtable

