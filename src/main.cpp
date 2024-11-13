#include "Entity.h"
#include "Scene.h"
#include "windows.h"
#include "Window/Window.h"
#include "Window/window_lua.h"
#include "lua.h"
#include "lua.hpp"
#include <Rendering.h>
#include <chrono>
#include <filesystem>
#include <thread>
#include <fstream>

char *LUA_SCRIPT;

int main() {

  window W = {};
  window_init(&W); // init window

  Render::Renderer R = {.W = &W};
  Render::init_renderer(&R); // initing renderer
                             //
  scene S;
  scene_add_lua_script(&S, std::filesystem::path("foo.lua"));

  S.R = &R;


  //std::ifstream lua_file;
  //lua_file.open(".\\foo.lua");
  //lua_file >> LUA_SCRIPT;


  //printf("%s", e.LUA_SCRIPT);

  int y, x = 0.0f;
  bool reloaded = false;

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  lua_newtable(L);
  lua_setglobal(L, "CompRend");

  entity_init_lua(L);
  lua_window_init(L);
  csprite_init_lua(L);
  scene_init_lua(&S, L);
  

    while (true) {

      set_window_start_input();
      update_window_events(&W);
      set_window_get_input();

      scene_run_lua(&S,L);
      R.position = {0, x};
      //set_entity_position(&e, x, y);
      // Render::add_to_buffer(&R, sp);
      set_window_buffer(&W, R.render_buffer, R.render_buffer_size);
      Render::render_buffer(&R);
      window_draw(&W);
    }
  lua_close(L);
}
