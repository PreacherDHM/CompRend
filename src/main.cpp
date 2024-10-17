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
  delete[] R.render_buffer;

  Render::init_renderer(&R); // initing renderer

  Render::sprite sp;
  sp.bounds = {5, 4};
  sp.data = " | |  / \\   |  |_0_|";
  sp.data_size = 9;
  sp.position = {0, 0};

  Render::add_to_buffer(&R, sp); // adding sprite to be rendered;

  sp.position = {-5,-5};

  Render::sprite sp2;  
  sp2.bounds = {5, 4};
  sp2.position = {4,20};
  sp2.data = " | |  / \\   |  |_0_|" ;

  Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {-10,-10};
  Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {-15,-15};
  Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {-20,-20};
  Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {-10,0};
  Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {20,0};
  Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  sp.position = {15,0};
  Render::add_to_buffer(&R, sp); // adding sprite to be rendered;


  while (true) {
      R.render_buffer = new char[W.size.X * W.size.Y];
      R.render_buffer_size = W.size.X * W.size.Y;
    Render::render_buffer(&R);
    update_window_events(&W);
    set_window_buffer(&W, R.render_buffer, R.render_buffer_size);
    window_draw(&W);
    //printf("\n%d,%d", W.size.X, W.size.Y);
    //printf("\n%d, %d", W.size.X, W.size.Y);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
      delete[] R.render_buffer;
  }
  lua_State *L = luaL_newstate();
  luaL_dostring(L, "x = 47");
  lua_getglobal(L, "x");
  lua_Number x = lua_tonumber(L, 1);
  printf("hi %d", (int)x);
  lua_close(L);
  return 0;
}
