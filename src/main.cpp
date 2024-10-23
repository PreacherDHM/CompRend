#include "Entity.h"
#include "Window/Window.h"
#include "lstate.h"
#include "lua.h"
#include "lua.hpp"
#include <Rendering.h>
#include <fstream>

char *LUA_SCRIPT;

int main() {


  window W = {};
  window_init(&W); // init window

  Render::Renderer R = {.W = &W};
  Render::init_renderer(&R); // initing renderer

  sprite sp;
  sp.bounds = {3, 3};
  sp.data = "$#$###$#$";
  sp.position = {0, 0};

  entity e;
  e.name = "foo";
  set_entity_position(&e, 3.0f, 8.0f);
  set_entity_sprite(&e, sp);
  set_entity_id(&e, 1);

  //std::ifstream lua_file;
  //lua_file.open(".\\foo.lua");
  //lua_file >> LUA_SCRIPT;

  set_entity_lua_script(&e, R"(
local position = {}
CompRend.init = function ()
    
end

CompRend.update = function ()
    position = CompRend.foo:GetPosition()
    position.x += 0.001
    CompRend.foo:move(position)
end
  )");

  printf("%s", e.LUA_SCRIPT);

  float y, x = 0.0f;

  lua_State *L = luaL_newstate();

  entity_init_lua(&e, L);


    while (true) {

        entity_run_lua(&e, L);
  //    update_window_events(&W);
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
  //    R.position = {0, 0};
  //    set_entity_position(&e, x, y);
  //    Render::add_to_buffer(&R, &e.sprite);
  //    // Render::add_to_buffer(&R, sp);
  //    set_window_buffer(&W, R.render_buffer, R.render_buffer_size);
  //    Render::render_buffer(&R);
  //    Render::clear_layer(&R, 0);
  //    window_draw(&W);
    }
  lua_close(L);
}
