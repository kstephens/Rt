#ifndef __Raster_RasterPNM_hh
#define __Raster_RasterPNM_hh

#include "Raster/Raster.hh"
#include <stdio.h>
#include <string>

class RasterPNM : public Raster {
  std::string _name, _mode;
  void init();
  FILE *fp;
public:
  int text;
  RasterPNM(const std::string &name, const std::string &mode);
  ~RasterPNM();
  int bitsPerPixel() const { return 24; }
  void write(Raster *r);
  void read(Raster *r);
  void close();
};

#endif
