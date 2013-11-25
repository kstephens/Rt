#ifndef	__RasterLUTFile_hh
#define	__RasterLUTFile_hh

#include "Raster/RasterLUT.hh"

class RasterLUTFile : public RasterLUT {
	int	fd;
	long	loc;
	RasterValue	_size;
protected:
	void	seek(const RasterValue& v ) const;
public:
	RasterValue	size() const;
	void		size(const RasterValue& v ) { _size = v; }

	RasterColor	color ( const RasterValue& value ) const;
	void		color ( const RasterValue& v, const RasterColor& color );
	void	read(int fd); // read a binary LUT from fd
};

#endif
