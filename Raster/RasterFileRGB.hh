#ifndef	__Raster_RasterFileRGB_hh
#define	__Raster_RasterFileRGB_hh

#include <Raster/RasterFile.hh>

class RasterFileRGB : public RasterFile {
public:
  RasterFileRGB( const char* filename );
  RasterFileRGB( const char* filename, const RasterSize &size );

  void color( const RasterPosition &p, const RasterColor &c );
  RasterColor color( const RasterPosition &p ) const;
  
  RasterLUT *LUT() const;
};

#endif
