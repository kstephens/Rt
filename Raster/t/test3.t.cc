#include "Raster/RasterLUTFile.hh"
#include "Raster/RasterFileRGB.hh"

int main ( int argc, char** argv )
{
  RasterFileRGB d = RasterFileRGB(argv[2], RasterSize(256, 256));
  RasterFileRGB f = RasterFileRGB(argv[1]);

  f.medianCut(&d);
}
