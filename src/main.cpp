#include "Window/Window.h"
#include "lua.hpp"
#include <Rendering.h>
#include <chrono>
#include <cstdio>
#include <stdio.h>
#include <thread>

int main() {
  window W = {};
  window_init(&W);
  Render::Renderer R = {.W = &W};
  R.render_buffer = new char[W.size.X * W.size.Y];
  R.render_buffer_size = W.size.X * W.size.Y;

  Render::init_renderer(&R); // initing renderer

  Render::sprite sp;
  sp.bounds = {1, 1};
  sp.data = "#";
  sp.data_size = 9;
  sp.position = {0, 0};


  set_window_buffer(&W, R.render_buffer, R.render_buffer_size);
    int y = 0;
    bool swop;
  while (true) {

      if((y == 50 && swop)){
          swop = false;
      }
      if(y == -40) {
          swop = true;
      }
      if(swop) {
          
        y++;
      }else {
        y--;
      }
  sp.position = {0 + y, 0 };
    Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {-5 + y, 5 };
    Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {-10 + y, 10 };
    Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {-20 + y, -10 +y};
    Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
    Render::render_buffer(&R);
    Render::clear_layer(&R,0);
    window_draw(&W);
    update_window_events(&W);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
