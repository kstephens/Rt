//
// MedianCut.cc - class Raster::medianCut(Raster* out, RasterValue lutsize)
//
//
#include	"Raster.hh"
#include	"RGB.hh"
#include 	"Histogram.hh"
#include	"BSP.hh"

void
Raster::medianCut( Raster* out, RasterValue lutsize )
{
  if ( lutsize == 0 )
    lutsize = out->LUT()->size();
  
  Histogram	histogram[3];

  //
  // initialize a histogram for each channel.
  //
  histogram[0].size(256);
  histogram[1].size(256);
  histogram[2].size(256);

  histogram[0].clear();
  histogram[1].clear();
  histogram[2].clear();

  //
  // create a histogram of the channels.
  //
  RasterPosition	p;
  RasterSize	s = size();

  for ( p.y = 0; p.y < s.y; p.y ++ ) {
    for ( p.x = 0; p.x < s.x; p.x ++ ) {
      RasterColor	c = color(p);
      RGB	color(c.red(), c.green(), c.blue());
      

      histogram[0].take( color[0] );
      histogram[1].take( color[1] );
      histogram[2].take( color[2] );
    }
  }

  //
  // create a BSPtree for LUTsize values;
  //
  BSPBase*	tree = BSPBase::createTree(lutsize);

  //
  // partition the color space.
  //
  tree->partition(histogram, RGB((U8) 0), RGB((U8) 256));


  //
  // read the raster again to map RGB to LUT indexes.
  //
  for ( p.y = 0; p.y < s.y; p.y ++ ) {
    for ( p.x = 0; p.x < s.x; p.x ++ ) {
      RasterColor	c = color(p);
      RGB	color(c.red(), c.green(), c.blue());
      

      BSPleaf*	leaf = tree->find(color);
      
      leaf->take(color);
      out->value(leaf->index());
    }
  }

  //
  // assign a LUT index to each leaf node.
  // and place the LUT in the output image.
  //
  tree->setLUT(out->LUT());

  //
  // Free the tree!
  //
  delete tree;
}
