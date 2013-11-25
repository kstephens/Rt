#include "Scene.hh"
#include "Camera.hh"

#include "Raster/RasterMemory24.hh"
#include "Raster/RasterPNM.hh"

Scene *scene2(Camera *camera);

#ifdef	__MSDOS__
/*
extern	unsigned	_stklen = 64000U;
*/
#endif

int main(int argc, char** argv)
{
  Camera *camera = new Camera();
  camera->trace_depth = 4;
  Scene *scene = camera->scene = scene2(camera);
  int nframes = 32;

  for ( int frame = 0; frame < nframes; frame ++ ) {
    angle a = degrees((scalar) frame / nframes * 360.0 + 8.0);
    scalar r = 20.0;
    camera->VE = Point(r * cos(a), 10.0, r * sin(a));

    char file[256];
    sprintf(file, "t/test-%02d.ppm", frame);
    std::cerr << "Frame: " << frame << "  file: " << file << "\n";
    RasterMemory24 image(RasterSize(640, 480));
    camera->render(&image);

    {
      char pnm_convert[1024];

      RasterPNM f(file, "w+");
      f.write(&image);

      sprintf(pnm_convert, "set -x; pnmtopng %s > %s.png", file, file);
      system(pnm_convert);
    }
  }
}



