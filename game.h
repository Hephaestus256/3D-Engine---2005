#ifndef INCLUDE_GAME
#define INCLUDE_GAME

void check_controls__game__ (camera_type* camera, view_type view);

void check_controls__game__ (camera_type* camera, view_type view)
{
  static int prev_mx = 512, prev_my = 512;
  double rec_inc = 2.0;
  get_mouse_stat_game();
  
  if (_keyb_stat[0x3F].change)
    _collis = !_collis;
  if (_keyb_stat['K'].press) {
    camera->pos.x -= sin(camera->angle_xz + PI / 2) * rec_inc;
    camera->pos.z -= cos(camera->angle_xz + PI / 2) * rec_inc;
  }
  if (_keyb_stat['M'].press) {
    camera->pos.x += sin(camera->angle_xz + PI / 2) * rec_inc;
    camera->pos.z += cos(camera->angle_xz + PI / 2) * rec_inc;
  }
  if (_keyb_stat[72].press) {
    camera->pos.x += sin(camera->angle_xz) * rec_inc;
    camera->pos.z += cos(camera->angle_xz) * rec_inc;
  }
  if (_keyb_stat[80].press) {
    camera->pos.x -= sin(camera->angle_xz) * rec_inc;
    camera->pos.z -= cos(camera->angle_xz) * rec_inc;
  }

  camera->angle_xz = _mouse_status.x;
  camera->angle_yz = -_mouse_status.y;

  for (int i = 0; i < 128; i++)
    _keyb_stat[i].change = false;
}


#endif
