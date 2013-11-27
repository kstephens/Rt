
#include "Raster/RasterColor.hh"
#include <iostream>

int main(int argc, char** argv ) {
  for ( int i = 1; i < argc; i ++ ) {
    RasterColorRGB	color = argv[i];
    std::cout << argv[i] << " = "
              << color.red() << " "
              << color.green() << " "
              << color.blue() << "\n";
  }
}

