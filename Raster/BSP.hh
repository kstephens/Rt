//
// BSP.hh - class BSPBase, BSP, BSPleaf
// KAS 91/06/23
//
#ifndef	__BSP_hh
#define	__BSP_hh

#include "Raster/RGB.hh"
#include "Raster/Histogram.hh"
#include "Raster/RasterLUT.hh"
#include "Raster/RasterColor.hh"

class	BSP;
class	BSPleaf;

class	BSPBase {
public:
virtual	~BSPBase() {}
static	BSPBase*	createTree(int leafnodes);

virtual	void		partition(Histogram histogram[3], RGB low, RGB high ) = 0;
virtual	BSPleaf*	find(const RGB&) = 0;
virtual	void		setLUT(RasterLUT* lut) = 0;
};

class	BSP : public BSPBase {
	BSPBase*	left;
	BSPBase*	right;
public:
	int	channel;
	U8	value;

	BSP ( BSPBase* l = NULL, BSPBase* r = NULL ) : left(l), right(r) {}
	~BSP();

	void	partition ( Histogram histogram[3], RGB l, RGB h );
	BSPleaf*	find (const RGB& color );
	void	setLUT ( RasterLUT* lut );

};

class	BSPleaf : public BSPBase {
	int	_index;
	struct {
		U32	r, g, b;
	} sum;
	U32	count;
public:
	BSPleaf(int i) : _index(i) { sum.r = sum.g = sum.b = 0; count = 1; }

	BSPleaf*	find( const RGB& color);
	void	partition( Histogram histogram[3], RGB l, RGB h );
	void	setLUT( RasterLUT* lut );

	int	index() { return _index; }

	RGB	average() const {
		return RGB(U8(sum.r / count), U8(sum.g / count), U8(sum.b / count));
	}

	void	take(const RGB& color) {
		sum.r += color.r;
		sum.g += color.g;
		sum.b += color.b;
		count ++;
	}


};

#endif

