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
  format = 7;
  fp = 0;
}

RasterPNM::RasterPNM(const std::string &name, const std::string &mode)
  : Raster(), _name(name), _mode(mode)
{
  ::init();
  init();
}

void
RasterPNM::close()
{
  if ( fp ) {
    fclose(fp);
    fp = 0;
  }
}

RasterPNM::~RasterPNM()
{
  close();
}

void RasterPNM::write(Raster *r)
{
  close();
  fp = fopen(_name.c_str(), _mode.c_str());
  if ( ! fp ) abort();
  RasterSize size = r->size();
  int bpp = r->bitsPerPixel();
  int hasAlpha = r->hasAlpha();

  switch ( format ) {
  case 3: case 6: // PPM
    fprintf(fp, "P%d\n", (int) format);
    fprintf(fp, "%d %d\n", size.x, size.y);
    fprintf(fp, "255\n");
    break;
  case 7: // PAM
    fprintf(fp, "P%d\n", (int) format);
    fprintf(fp, "WIDTH %d\n", (int) size.x);
    fprintf(fp, "HEIGHT %d\n", (int) size.y);
    fprintf(fp, "DEPTH %d\n", (int) 3 + hasAlpha); // RGB or RGBA
    fprintf(fp, "MAXVAL %d\n", (int) 255); // U8
    fprintf(fp, "TUPLTYPE %s%s\n", "RGB", hasAlpha ? "_ALPHA" : "");
    fprintf(fp, "ENDHDR\n");
    break;
  default:
    abort();
  }

  RasterPosition rp;
  for ( rp.y = 0; rp.y < size.y; ++ rp.y ) {
    for ( rp.x = 0; rp.x < size.x; ++ rp.x ) {
      RasterColor c = r->color(rp);
      c.clamp();
      RGBA cb(c.begin());
      switch ( format ) {
      case 3:
        fprintf(fp, "%3d %3d %3d   ", cb.r, cb.g, cb.b);
        break;
      case 6:
        fwrite(&cb, sizeof(cb[0]) * 3, 1, fp);
        break;
      case 7:
        fwrite(&cb, sizeof(cb[0]) * (bpp / 8), 1, fp);
        break;
      }
    }
    if ( format == 3 ) {
      fprintf(fp, "\n");
    }
  }

  close();
}

void RasterPNM::read(Raster *r)
{
  close();
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

