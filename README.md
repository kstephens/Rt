
Tonight We're Gonna Raytrace Like It's 1991!
============================================

Found this code I wrote back in 1991 on a 3.5" floppy -- A raytracer using the RenderMan shader model.

This was written on a 20 MHz i386 with a Video7 VGA graphics card
running DOS and Borland C++, before templates and STL existed.

Ported to Linux and OSX.

Does not implement The RenderMan Interface, but I was attempting to do so.
Handles shadows and illuminate(), solar(), illuminance() statements.
4 random samples per pixel.

     $ make
     # Run Rt/t/rttest.t; generate Rt/t/test-anim.gif
     $ make test

Renders a GIF animation of a bunch of plastic and reflective Spheres and Cylinders under 3 Pointlights and 1 Distantlight.

Needs netpbm and gifcicle for the test.

1991 - 2013

-- http://devdriven.com/

