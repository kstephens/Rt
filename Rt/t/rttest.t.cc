#include "Rt/Scene.hh"
#include "Rt/Camera.hh"

#include "Raster/RasterMemory24.hh"
#include "Raster/RasterPNM.hh"

#include "Rt/ProcessManager.hh"

Scene *scene2(Camera *camera);

#ifdef	__MSDOS__
/*
extern	unsigned	_stklen = 64000U;
*/
#endif

int main(int argc, char** argv)
{
  int nframes = 128;
  int n_processes = 8; // 8 cores.

  Camera *camera = new Camera();
  camera->trace_depth = 4;
  camera->samples_per_pixel = 6;
  Scene *scene = camera->scene = scene2(camera);

  if ( argc > 1 )
    n_processes = atoi(argv[1]);

  ProcessManager pm(n_processes);

  for ( int frame = 0; frame < nframes; frame ++ ) {
    angle a = degrees((scalar) frame / nframes * 360.0 + 8.0);
    scalar r = 20.0;
    camera->VE = Point(r * cos(a), 10.0, r * sin(a));

    if ( pm.fork() ) {
      char file[256];
      sprintf(file, "t/test-%03d.ppm", frame);
      std::cerr << "pid: " << getpid() << " Frame: " << frame << "  file: " << file << "\n";
      RasterMemory24 image(RasterSize(640, 480));
      camera->render(&image);

      {
        char pnm_convert[1024];

        RasterPNM f(file, "w+");
        f.write(&image);

        sprintf(pnm_convert, "set -x; pnmtopng %s > %s.png", file, file);
        system(pnm_convert);
      }

      pm.exit(0);
    }
  }

  pm.join();

  return 0;
}


