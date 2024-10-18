#include "Window/Window.h"
#include "lua.hpp"
#include <Rendering.h>
#include <windows.h>

int main() {
  window W = {};
  window_init(&W); // init window

  Render::Renderer R = {.W = &W};
  Render::init_renderer(&R); // initing renderer
  
  Render::sprite sp;
  sp.bounds = {3,3};
  sp.data = "$#$###$#$";
  sp.position = {40,20};


  int y,x = 0;
  while (true) {
    update_window_events(&W);

      for(int i = 0; i < strlen(get_window_input(&W)); i++) {
          if(get_window_input(&W)[i] == 'w') {
              y--;
          }
          if(get_window_input(&W)[i] == 's') {
              y++;
          }
          if(get_window_input(&W)[i] == 'd') {
              x--;
          }
          if(get_window_input(&W)[i] == 'a') {
              x++;
          }
      }
  R.position = {40 + x,20 + y};
    Render::add_to_buffer(&R, sp);
    set_window_buffer(&W, R.render_buffer, R.render_buffer_size);
    Render::render_buffer(&R);
    Render::clear_layer(&R,0);
    window_draw(&W);
  }
}
