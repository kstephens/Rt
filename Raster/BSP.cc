//
// BSP.cc - class BSPBase, BSP, BSPleaf
//
//
#include "Raster/BSP.hh"


///////////////////////////////////
//
// BSPBase
//

static
BSPBase*	_createTree(int lowleaf, int highleaf) {
	if ( lowleaf == highleaf - 1 ) 
		return new BSPleaf(lowleaf);
	else {
		int	midleaf = (lowleaf + highleaf) / 2;
		return new BSP (
			_createTree(lowleaf, midleaf),
			_createTree(midleaf, highleaf) );
	}
}

BSPBase*	BSPBase::createTree(int leafnodes) {
	return	_createTree(0, leafnodes);
}

////////////////////////////////////////
//
// BSP
//

BSP::~BSP() { delete left; delete right; }

void	BSP::partition(Histogram histogram[3], RGB l, RGB h) {
	//
	// find the channel with the most dynamic range.
	//
	int	i;
	int	dynamicRange = 0;

	for ( i = 0; i < 3; i ++ ) {
		//
		// Narrow down the cube, too.
		//
		l[i] = histogram[i].min( l[i], h[i] );
		h[i] = histogram[i].max( l[i], h[i] );

		int	d = h[i] - l[i];

		if ( d > dynamicRange ) {
			dynamicRange = d;
			channel = i;
		}
	}

	//
	// split the BSP on the median of the channel
	//
	int	value = histogram[channel].median(l[i], h[i]);

	//
	// now do each of the partitions.
	//
	RGB	highLeft = h;
	highLeft[channel] = value;
	RGB	lowRight = l;
	lowRight[channel] = value;

	right->partition(histogram, l, highLeft);
	left->partition(histogram, lowRight, h);

}

BSPleaf*
BSP::find (const RGB& color ) {
	if ( color[channel] < value )
		return left->find(color);
	else
		return right->find(color);
}

void
BSP::setLUT ( RasterLUT* lut ) {
	left->setLUT(lut);
	right->setLUT(lut);
}


///////////////////////////////////
//
// BSPleaf
//

void
BSPleaf::partition( Histogram histogram[3], RGB l, RGB h ) { return; }

BSPleaf*
BSPleaf::find( const RGB& color) { return this; }

void
BSPleaf::setLUT( RasterLUT* lut ) {
	RGB	avg = average();
	lut->color(_index, RasterColor(avg.r, avg.g, avg.b));
}

