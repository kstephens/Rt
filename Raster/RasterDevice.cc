//
// Device.cc - class RasterDevice
//
//

#include "Raster/RasterDevice.hh"

RasterDevice::~RasterDevice() {}

RasterType
RasterDevice::type() const { return "RasterDevice"; }

int
RasterDevice::isATypeOf(RasterType t ) const {
  return t == type() || Raster::isATypeOf(t);
}

Raster*
RasterDevice::parent() const { return (Raster*) 0L; }

float
RasterDevice::pixelAspectRatioXY() const { return 1.0; }

