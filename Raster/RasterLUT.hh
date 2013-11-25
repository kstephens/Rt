//
// LUT.hh - class RasterLUT
//
//
#ifndef	__Raster_RasterLUT_hh
#define	__Raster_RasterLUT_hh

#include "Raster/RasterValue.hh"
#include "Raster/RasterColor.hh"

class RasterLUT {
protected:
  void	copy(const RasterLUT& l );
public:
  virtual	~RasterLUT() {}
  virtual	RasterLUT&	operator = ( const RasterLUT& l ) { copy(l); return *this; }
  virtual	RasterValue	size() const = 0;
  virtual	void	size(const RasterValue& s);
  virtual	RasterValue	value ( const RasterColor& color ) const;
  virtual	RasterColor	color ( const RasterValue& value ) const = 0;
  virtual	void		color ( const RasterValue& v, const RasterColor& color ) = 0;
  virtual	void	read(int fd); 		// read a binary LUT from fd
  void	write(int fd) const; 	// write a binary LUT from fd
};

#endif
