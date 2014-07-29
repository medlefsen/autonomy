// Primary Author: Nathan

#include "viewport.hpp"
namespace autonomy { namespace ui {

  viewport::viewport(int width_x, int height_y, int zoom)
  {
    _x = 0;
    _y = 0;
    _x_res = width_x;
    _y_res = height_y;
    _drone_size = zoom;
  }
  viewport::viewport()
  {
    _x = 0;
    _y = 0;
    _x_res = 200;
    _y_res = 200;
    _drone_size = 10;
  }

  void viewport::set_resolution(int width_x, int height_y)
  {
    _x_res = width_x;
    _y_res = height_y;
  }

  void viewport::pan_right(int pixels)
  {
    _x += pixels; 
  }
  void viewport::pan_left(int pixels)
  {
    _x -= pixels; 
  }
  void viewport::pan_up(int pixels)
  {
    _y -= pixels; 
  } 
  void viewport::pan_down(int pixels)
  {
    _y += pixels; 
  }

  int viewport::game_x()
  {
    return static_cast<int>(_x/_drone_size);
  }
  int viewport::game_y()
  {
    return static_cast<int>(_y/_drone_size);
  }
  int viewport::game_x_res()
  {
    return static_cast<int>(_x_res/_drone_size);
  }
  int viewport::game_y_res()
  {
    return static_cast<int>(_y_res/_drone_size);
  }

  int viewport::x()
  {
    return _x;
  }

  int viewport::y()
  {
    return _y;
  }

  void viewport::x(int game_x)
  {
    _x = game_x;
  }
  void viewport::y(int game_y)
  {
    _y = game_y;
  }
  void viewport::set_zoom(int drone_pix_size)
  {
    _drone_size = drone_pix_size;
    if(_drone_size < 1)
      _drone_size = 1;
  }
  void viewport::zoom_out(int drone_pix_size)
  {
    _drone_size -= drone_pix_size;
    if(_drone_size < 1)
      _drone_size = 1;
  }
  void viewport::zoom_in(int drone_pix_size)
  {
    _drone_size += drone_pix_size;
  }
  int viewport::x_res()
  {
    return _x_res;
  }
  int viewport::y_res()
  {
    return _y_res;
  }
  int viewport::x_pos()
  {
    return _x;
  }
  int viewport::y_pos()
  {
    return _y;
  } 
  int viewport::drone_size()
  {
    return _drone_size;
  }

}}
