#include "Entity.h"
#include "Csprite.h"
#include "filesystem"
#include <cmath>
#include <cstdlib>

// SETTERS
void set_entity_sprite(entity *E, sprite sprite) { E->sprite = sprite; }

void set_entity_position(entity *E, float x, float y) {
  E->position.x = x;
  E->position.y = y;
  int spx, spy = 0;
  spx = static_cast<int>(round(x));
  spy = static_cast<int>(round(y));
  E->sprite.position = {spx, spy};
}

void set_entity_lua_script(entity *) {
  std::filesystem::path lua_dir = "./lua";
  std::filesystem::path path = lua_dir / "./";
  // TODO ADD LUA FILE PATH
}
void set_entity_id(entity *, int) {}

void set_entity_lua_script(entity *E, const char *LUA) { E->LUA_SCRIPT = LUA; }

cordnet get_entity_position(entity *E) { return E->position; }
int get_entity_id(entity *E) { return E->id; }
sprite get_entity_sprite(entity *E) { return E->sprite; }





void entity_create(entity *E,lua_State *L) { 


}
int entity_move(lua_State *) { return 0; }
int entity_change_sprite(lua_State *) { return 0; }
int entity_get_position(lua_State *) { return 0; }
int entity_get_id(lua_State *) { return 0; }
int entity_get_name(lua_State *) { return 0; }
void entity_init_lua(entity * E, lua_State * L) {
    
    lua_getglobal(L, "CompRend");
    int table = lua_gettop(L);
    if(lua_istable(L,table)) {
        lua_getfield(L, table, E->name);
        int object = lua_gettop(L);

        // get name
        lua_getfield(L, object, "name");
        const char* name = lua_tostring(L,object);

        // Get Position
        lua_getfield(L, object, "position");
        int position = lua_gettop(L);
        lua_getfield(L, position, "x");
        lua_Number x = lua_tonumber(L, -1);
        lua_getfield(L, position, "y");
        lua_Number y = lua_tonumber(L, -1);
    }

}
void entity_run_lua(entity * E, lua_State *) {}
