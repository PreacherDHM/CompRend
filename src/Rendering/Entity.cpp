#include "Entity.h"
#include "Csprite.h"
#include "filesystem"
#include "lauxlib.h"
#include "lua.h"
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

void set_entity_lua_script(entity *E, char *LUA) { E->LUA_SCRIPT = LUA; }

cordnet get_entity_position(entity *E) { return E->position; }
int get_entity_id(entity *E) { return E->id; }
sprite get_entity_sprite(entity *E) { return E->sprite; }

int entity_create(lua_State *L) {
    // TODO FINISH THIS
    lua_pushstring(L,"x");
    lua_gettable(L,-3);
    float x = lua_tonumber(L,-1);
    lua_pushstring(L,"y");
    lua_gettable(L,-3);
    float y = lua_tonumber(L,-1);
    entity E;
    E.id = rand();
    E.sprite = sprite();
    E.position = {x,y};
    lua_pushlightuserdata(L, &E);
    return 1; 
}
int entity_move(lua_State *L) { 
    lua_touserdata(L,-3);
    return 0; 
}
int entity_change_sprite(lua_State *) { return 0; }
int entity_get_position(lua_State *) { return 0; }
int entity_get_id(lua_State *) { return 0; }
int entity_get_name(lua_State *) { return 0; }
void entity_init_lua(entity *E, lua_State *L) {

  lua_newtable(L);
  lua_setglobal(L, "CompRend");

  int table = lua_gettop(L);
  if (lua_istable(L, table)) { // if CompRend exists
    lua_getglobal(L, "CompRend");

    lua_pushstring(L, "Entity");
    lua_newtable(L);

    lua_pushstring(L, "Create");
    lua_pushcfunction(L, entity_create);

    lua_pushstring(L, "Move");
    lua_pushcfunction(L, entity_move);
    lua_settable(L, -3);

    lua_pushstring(L, "ChangeSprite");
    lua_pushcfunction(L, entity_change_sprite);
    lua_settable(L, -3);

    lua_pushstring(L, "GetId");
    lua_pushcfunction(L, entity_get_id);
    lua_settable(L, -3);

    lua_pushstring(L, "GetName");
    lua_pushcfunction(L, entity_get_name);
    lua_settable(L, -3);

    lua_pushstring(L, "GetPosition");
    lua_pushcfunction(L, entity_get_name);
    lua_settable(L, -3);

    lua_settable(L, -3);

  } else {
    printf("Not a table");
  }
}
void entity_run_lua(entity *E, lua_State *) {}
