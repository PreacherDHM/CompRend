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
  R.render_buffer = new char[300 * 200];
  R.render_buffer_size = 300 * 200;

  for (int i = 0; i < R.render_buffer_size; i++) {
      R.render_buffer[i] = ' ';
  }
  for (int i = 80; i < 100; i++) {
      R.render_buffer[i] = '#';
  }
  if(W.size.X * W.size.Y < R.render_buffer_size) {
      R.render_buffer[W.size.X * W.size.Y] = '\0';
  }

  Render::sprite sp;
  sp.bounds = {3, 3};
  sp.data = "#########";
  sp.data_size = 9;
  sp.position = {0, 0};

  Render::init_renderer(&R); // initing renderer
  //Render::add_to_buffer(&R, sp); // adding sprite to be rendered;
  while (true) {
    //Render::render_buffer(&R);
    set_window_buffer(&W, R.render_buffer, R.render_buffer_size);
    window_draw(&W);
    update_window_events(&W);
    //printf("\n%d, %d", W.size.X, W.size.Y);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  lua_State *L = luaL_newstate();
  luaL_dostring(L, "x = 47");
  lua_getglobal(L, "x");
  lua_Number x = lua_tonumber(L, 1);
  printf("hi %d", (int)x);
  lua_close(L);
  return 0;
}
