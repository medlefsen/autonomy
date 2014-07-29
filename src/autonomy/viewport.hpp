// Primary Author: Nathan

#ifndef AUTONOMY_UI_VIEWPORT_HPP
#define AUTONOMY_UI_VIEWPORT_HPP
namespace autonomy { namespace ui {
  class viewport
  {
  public:
    viewport(int width_x, int height_y, int zoom);
    viewport();
    void set_resolution(int width_x, int height_y);

    void pan_right(int pixels);
    void pan_left(int pixels);
    void pan_up(int pixels);
    void pan_down(int pixels);

    // get the pixel position of the viewport
    int x();
    int y();
    int x_res();
    int y_res();
    int x_pos();
    int y_pos();

    // get the game unit position of the viewport
    int game_x();
    int game_y();
    int game_x_res();
    int game_y_res();

    void x(int x);
    void y(int y);
    void set_zoom(int zoom);
    void zoom_out(int in_game_distance);
    void zoom_in(int in_game_distance);
    int drone_size();

  private:
    int _x; // pixels
    int _y;
    int _x_res; 
    int _y_res;
    int _drone_size; // in pixels
  };
}}
#endif
