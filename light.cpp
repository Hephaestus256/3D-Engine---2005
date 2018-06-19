#include "stdlib.h"
#include "gfx2d.h"

double inv_sqr_light (double x, double y, double z, double k, double i);
double calc_k (double bright, double d, double i);
int dig_nterp (double c, int x, int y);
int dig_nterp2 (double c, int x, int y);
int dig_nterp3 (double c, int x, int y);
void show_pic_scaled (int w, int h, long* dat, double scale, void* buff);
double get_inv_squared_rad (double k, double abs_i, double z, double i);
double get_inv_squared_max_z (double k, double abs_i, double i);


int dig_nterp (double c, int x, int y)
{
  double frac = (c - int(c));
  double freq_x, freq_y;
  int a;

  freq_x = freq_y = sqrt(frac);
  
  if (x % 2)
    a = .5 * (1 / freq_x);
  else
    a = 0;
    
  if (int((x + 1) * freq_x) - int((x + 0) * freq_x) == 1)
    if (int((y + a + 1) * freq_y) - int((y + a) * freq_y) == 1)
      return c + 1;
    else
      return c;
  else
    return c;
}


int dig_nterp3 (double c, int x, int y)
{
  int r = rand() & 255;
  int f = int(256 * (c - floor(c)));

  if (f >= r)
    return int(c) + 1;
  else
    return int(c);
}


int dig_nterp2 (double c, int x, int y)
{
  double frac = (c - int(c));
  double freq_x = sqrt(1 * frac); // 2
  double freq_y = sqrt(1 * frac);  // .5
  
  if (int((x + 1) * freq_x) - int((x) * freq_x) == 1)
    if (int((x + y + 1) * freq_y) - int((x + y) * freq_y) == 1)
      return c + 1;
    else
      return c;
  else
    return c;
}


int main()
{
/*
  set_vesa_mode(TRUE_COLOR_320x200);
  void* x2_buff = (void*)malloc (_screen.x_res * _screen.y_res * 3);

  for (double a = 125; a >= 0; a -= 1) {
    double acc = 0;
    for (int y = 0; y < 100; y++)
      for (int x = 0; x < 100; x++) {
        int c = 1 * int(a);//dig_nterp3 (a, x, y);
        acc += double(c);
        pxl (x, y, c, c, c, x2_buff);
      }
    copy_scrn_buff (x2_buff, 0);
    getchar();
  }
}
*/
///*
  double z = 54;
  double i = 1;
  double k = 7242.803;//calc_k (i, z, 1);
  int rad;
  
  set_vesa_mode(0x3);
  printf ("%f", get_inv_squared_rad (k, i, z, .01));
  getchar();
  
  set_vesa_mode(TRUE_COLOR_320x200);
  void* x2_buff = (void*)malloc (_screen.x_res * _screen.y_res * 3);
  
  double d = _screen.x_res;
  double cx = _screen.x_res / 2, cy = _screen.y_res / 2;

  for (i = 1; i >= 0; i-=0.05) {
    rad = get_inv_squared_rad (k, i, z, .01);
    if (rad > _screen.x_res / 2);
      rad = _screen.x_res / 2;
    clear_scrn_buff(x2_buff);
    for (int y = cy - rad; y < cy + rad; y++) {
      for (int x = cx - rad; x < cx + rad; x++) {
        double a = .0 + inv_sqr_light(double(x) - cx, double(y) - cy, z, k, i);
        double c = dig_nterp3 (a * 255, x, y);
        pxl (x, y, c, c, c, x2_buff);
      }
    }
    pxl (cx + rad, _screen.y_res / 2, 255, 255, 255, x2_buff);
    copy_scrn_buff (x2_buff, 0);
    getchar();
  }
}


double inv_sqr_light (double x, double y, double z, double k, double i)
{
  double result = k * i * z * pow(x*x + y*y + z*z, -1.5);

  if (result > 1.0)
    return 1;
  else
    return result;
}


void show_pic_scaled (int w, int h, long* dat, double scale, void* buff)
{
  long u, v;
  long du = 65536.0 / scale, dv = 65536.0 / scale;
  int x, y;
  double mul = 1.0;// / (65536.0 * 127.0);// / (65536.0 * 65536.0);
  
  for (v = 0, y = 0; y < h * scale; y++, v += dv)
    for (u = 0, x = 0; x < w * scale; x++, u += du) {
      int i = ((u >> 16) + (v >> 16) * w);
      int c = int(dat[i] * mul);
      if (c > 255)
        pxl (x, y, 255, 255, 255, buff);
      else
        pxl (x, y, c, c, c, buff);
    }
}


double get_inv_squared_rad (double k, double abs_i, double z, double i)
{
  return sqrt(pow((k * abs_i * z) / i, 2.0/3.0) - z * z);
}


double get_inv_squared_max_z (double k, double abs_i, double i)
{
  return sqrt((k * abs_i) / i);
}


double calc_k (double factor, double d, double i)
{
  return i / (factor * d * pow(d*d, -1.5));
}
//*/
