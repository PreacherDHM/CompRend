#include "Window/Window.h"
#include "lua.hpp"
#include <Rendering.h>
#include <windows.h>
#include "Entity.h"

const char* LUA_SCRIPT = R"(

local pos 
init = function ()
    pos = get_entity_position()
end
update = function()

position = get_entity_position() -- table {x,y}
if pos.x < 10 then
pos = x + 0.1
end

entity_move(position)
end
)";

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
  set_entity_position(&e, 0.0f, 0.0f);
  set_entity_sprite(&e, sp);
  set_entity_id(&e, 1);
  set_entity_lua_script(&e);

  float y, x = 0.0f;
  while (true) {
    update_window_events(&W);

    for (int i = 0; i < strlen(get_window_input(&W)); i++) {
      if (get_window_input(&W)[i] == 'w') {
        y += 0.1f;
      }
      if (get_window_input(&W)[i] == 's') {
        y -= 0.1f;
      }
      if (get_window_input(&W)[i] == 'd') {
        x -= 0.1f;
      }
      if (get_window_input(&W)[i] == 'a') {
        x += 0.1f;
      }
    }

    R.position = {0,  0};
    set_entity_position(&e, x, y);
    Render::add_to_buffer(&R, &e.sprite);
    //Render::add_to_buffer(&R, sp);
    set_window_buffer(&W, R.render_buffer, R.render_buffer_size);
    Render::render_buffer(&R);
    Render::clear_layer(&R, 0);
    window_draw(&W);
  }
}
