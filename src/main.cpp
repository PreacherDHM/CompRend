#include "Entity.h"
#include "Scene.h"
#include "Window/Window.h"
#include "lstate.h"
#include "lua.h"
#include "lua.hpp"
#include <Rendering.h>
#include <filesystem>
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

  csprite sp;
  sp.bounds = {1, 9};
  sp.data = "hii there";
  sp.position = {0, 0};

  entity e;
  e.name = "foo";
  set_entity_position(&e, 3.0f, 8.0f);
  set_entity_sprite(&e, sp);
  set_entity_id(&e, 1);

  //std::ifstream lua_file;
  //lua_file.open(".\\foo.lua");
  //lua_file >> LUA_SCRIPT;


  //printf("%s", e.LUA_SCRIPT);

  float y, x = 0.0f;

  lua_State *L = luaL_newstate();

  lua_newtable(L);
  lua_setglobal(L, "CompRend");

  entity_init_lua(L);
  scene_init_lua(&S, L);
      if(S.entity_count > 0) {
          for(int i = 0; i < S.entity_count; i++) {
            Render::add_to_buffer(&R, &S.entitys[i]->sprite);
          }
      }
  
    while (true) {

      update_window_events(&W);
  //
  //    for (int i = 0; i < 5; i++) {
  //      if (get_window_input(&W)[i] == 'w') {
  //        y += 0.1f;
  //      }
  //      if (get_window_input(&W)[i] == 's') {
  //        y -= 0.1f;
  //      }
  //      if (get_window_input(&W)[i] == 'd') {
  //        x -= 0.1f;
  //      }
  //      if (get_window_input(&W)[i] == 'a') {
  //        x += 0.1f;
  //      }
  //    }
  //
      scene_run_lua(&S,L);
      R.position = {0, 0};
      //set_entity_position(&e, x, y);
      // Render::add_to_buffer(&R, sp);
      set_window_buffer(&W, R.render_buffer, R.render_buffer_size);
      Render::render_buffer(&R);
      window_draw(&W);
    }
  lua_close(L);
}
