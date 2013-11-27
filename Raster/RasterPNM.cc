#include "RasterPNM.hh"
#include "RGB.hh"
#include <iostream>
#include <stdlib.h> // abort()

static void init()
{
  static int inited;
  if ( ! inited ) {
    // pm_init("Raster", 0);
    inited = 1;
  }
}

void RasterPNM::init()
{
  text = 0;
  fp = 0;
}


RasterPNM::RasterPNM(const std::string &name, const std::string &mode)
  : _name(name), _mode(mode)
{
  ::init();
}

void
RasterPNM::close()
{
  if ( fp )
    fclose(fp);
}

RasterPNM::~RasterPNM()
{
  close();
}

void RasterPNM::write(Raster *r)
{
  fp = fopen(_name.c_str(), _mode.c_str());
  if ( ! fp ) abort();
  RasterSize size = r->size();

  if ( text ) {
    fprintf(fp, "P3\n");
  } else {
    fprintf(fp, "P6\n");
  }

  fprintf(fp, "%d %d\n", size.x, size.y);
  fprintf(fp, "255\n");

  RasterPosition rp;
  for ( rp.y = 0; rp.y < size.y; ++ rp.y ) {
    for ( rp.x = 0; rp.x < size.x; ++ rp.x ) {
      RasterColor c = r->color(rp);
      c.clamp();
      RGB rgb(c.begin());
      if ( text ) {
        fprintf(fp, "%3d %3d %3d   ", rgb.r, rgb.g, rgb.b);
      } else {
        fwrite(&rgb, sizeof(rgb), 1, fp);
      }
    }
    if ( text ) {
      fprintf(fp, "\n");
    }
  }
  close();
}

void RasterPNM::read(Raster *r)
{
  fp = fopen(_name.c_str(), _mode.c_str());
  if ( ! fp ) abort();
  close();
}

#if 0
void RasterPNM::write(Raster *r)
{
  FILE *fp = fopen(_name.c_str(), _mode.c_str());
  if ( ! fp ) abort();

  RasterSize size = r->size();

  struct pam p = { 0 };
  p.size = sizeof(p);
  p.len = sizeof(p); // PAM_STRUCT_SIZE();
  p.file = fp;
  p.width = size.x;
  p.height = size.y;
  p.depth = 3;
  p.maxval = 255;
  p.format = RPPM_FORMAT;
  pnm_writepaminit(&p);
  RGB *row = new RGB [size.x];
  RasterPosition rp;
  for ( rp.y = 0; rp.y < size.y; ++ rp.y ) {
    for ( rp.x = 0; rp.x < size.x; ++ rp.x ) {
      RasterColor c;
      r->color(rp, c);
      // std::cerr << "  " << rp.x << " " << rp.y << " = " << c << "\n";
      row[rp.x] = RGB(c.red(), c.green(), c.blue());
    }
    std::cerr << "  " << _name << "  row: " << rp.y << "\n";
    pnm_writepamrow(&p, (tuple*) row);
  }
  delete row;
  fclose(fp);
}

void RasterPNM::read(Raster *r)
{
  FILE *fp = fopen(_name.c_str(), _mode.c_str());
  if ( ! fp ) abort();
  struct pam p = { 0 };
  pnm_readpaminit(fp, &p, sizeof(p));
  RasterSize size(p.width, p.height);
  r->size(size);

  RGB *row = new RGB [size.x];

  RasterPosition rp;
  for ( rp.y = 0; rp.y < size.y; ++ rp.y ) {
    pnm_readpamrow(&p, (tuple*) row);
    for ( rp.x = 0; rp.x < size.x; ++ rp.x ) {
      r->color(rp, row[rp.x]);
    }
  }

  delete row;
  fclose(fp);
}

#endif

