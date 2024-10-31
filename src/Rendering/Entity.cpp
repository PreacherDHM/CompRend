#include "Entity.h"
#include "Csprite.h"
#include "Scene.h"
#include "filesystem"
#include <assert.h>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
// SETTERS
void set_entity_sprite(entity *E, csprite sprite) { E->sprite = sprite; }

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

void set_entity_lua_script(entity *E, std::filesystem::path p) {

  std::filesystem::path path(std::filesystem::current_path() / "bin" / p);
  std::string line, text;
  std::cout << path << '\n';
  if (std::filesystem::exists(path)) {
    printf("file exists\n");
    std::ifstream f(path);
    while (std::getline(f, line)) {
      text += line + "\n";
    }

    printf("file **\n%s\nfile ^^", text.c_str());

    E->script = text;
    f.close();
  }
}

cordnet get_entity_position(entity *E) { return E->position; }
int get_entity_id(entity *E) { return E->id; }
csprite get_entity_sprite(entity *E) { return E->sprite; }

// Creates a entity in lua
int entity_create(lua_State *L) {

  const char *name;
  float x, y;
  csprite sp = sprite_create();

  if(lua_istable(L,-1)){
      name = lua_tostring(L, -4);
      x = (float)lua_tonumber(L, -3);
      y = (float)lua_tonumber(L, -2);

      // Getting sprite data
      lua_pushstring(L, "sprite");
      lua_gettable(L,-2);
      sp.data = lua_tostring(L, -1);

      lua_pop(L, 1);

      lua_pushstring(L, "bounds");
      lua_gettable(L,-2);
      if(lua_istable(L, -1)) {
        
        lua_pushstring(L, "x");
        lua_gettable(L, -2);
        if(lua_isnumber(L, -1)) {
            sp.bounds.x = (int)lua_tonumber(L, -1);
        }

      lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, -2);
        if(lua_isnumber(L, -1)) {
            sp.bounds.y = (int)lua_tonumber(L, -1);
        }

      }

      lua_pop(L, 1);
      lua_pop(L, 1);


  } else {
    name = lua_tostring(L, -3);
    x = (float)lua_tonumber(L, -2);
    y = (float)lua_tonumber(L, -1);
    sp = sprite_create();
  }


  lua_newtable(L); // returned table

  lua_pushstring(L, "obj"); // entity pointer
  entity *E = (entity *)lua_newuserdata(L, sizeof(entity));
  lua_settable(L, -3);

  E->id = rand();
  E->sprite = sp;
  E->name = name;
  set_entity_position(E, x, y);

  lua_pushstring(L, "name"); // creates the name.
  lua_pushstring(L, E->name);
  lua_settable(L, -3);

  lua_pushstring(L, "id"); // creates the id.
  lua_pushnumber(L, E->id);
  lua_settable(L, -3);

  lua_pushstring(L, "sprite"); // creates a sprite.
  lua_pushlightuserdata(L, &E->sprite);
  lua_settable(L, -3);

  lua_pushstring(L, "position");
  lua_newtable(L); // start of position table

  lua_pushstring(L, "x"); // x position
  lua_pushnumber(L, E->position.x);
  lua_settable(L, -3);

  lua_pushstring(L, "y"); // y position
  lua_pushnumber(L, E->position.y);
  lua_settable(L, -3);

  lua_settable(L, -3); // end of position table

  // scene_add_entity(scene_get_current(), E);

  return 1;
}

int entity_translate(lua_State *L) {
  entity *e = (entity *)lua_touserdata(L, -2);
  // printf("--is user data--");

  if (lua_istable(L, -1)) {
    float x = 0.0f;
    float y = 0.0f;

    //printf("\rtable");
    

    lua_pushstring(L, "x");
    lua_gettable(L, -2);
    if (lua_isnumber(L, -1)) {
      x = (float)lua_tonumber(L, -1);
    }
    

    lua_pop(L,1);

    lua_pushstring(L, "y");
    lua_gettable(L, -2);
    if (lua_isnumber(L, -1)) {
      y = (float)lua_tonumber(L, -1);
    }

    e->position = {x, y};
    set_entity_position(e, x, y);
    return 0;
  }
  // printf("--no user data--");
  return 0;
}

int entity_change_sprite(lua_State *) { return 0; }
int entity_get_position(lua_State *L) {
  if (lua_islightuserdata(L, -1)) {
    entity *e = (entity *)lua_touserdata(L, -1);
    lua_newtable(L);

    lua_pushstring(L, "x");
    lua_pushnumber(L, e->position.x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, e->position.y);
    lua_settable(L, -3);
    return 1;
  }
  return 0;
}
int entity_get_id(lua_State *) { return 0; }
int entity_get_name(lua_State *L) {
  entity *e = (entity *)lua_touserdata(L, -1);
  lua_newtable(L);

  lua_pushstring(L, "x");
  lua_pushnumber(L, e->position.x);

  lua_pushstring(L, "y");
  lua_pushnumber(L, e->position.y);

  printf("running");

  return 0;
}
void entity_init_lua(lua_State *L) {

  // int table = lua_gettop(L);
  lua_getglobal(L, "CompRend");
  //  printf("table\n");

  lua_pushstring(L, "Entity");
  lua_newtable(L);

  lua_pushstring(L, "Create");
  lua_pushcfunction(L, entity_create);
  lua_settable(L, -3);

  lua_pushstring(L, "Translate");
  lua_pushcfunction(L, entity_translate);
  lua_settable(L, -3);

  // lua_pushstring(L, "ChangeSprite");
  // lua_pushcfunction(L, entity_change_sprite);
  // lua_settable(L, -3);

  // lua_pushstring(L, "GetId");
  // lua_pushcfunction(L, entity_get_id);
  // lua_settable(L, -3);

  // lua_pushstring(L, "GetName");
  // lua_pushcfunction(L, entity_get_name);
  // lua_settable(L, -3);

  lua_pushstring(L, "GetPosition");
  lua_pushcfunction(L, entity_get_position);
  lua_settable(L, -3);

  lua_settable(L, -3);
}

void entity_run_lua(entity *E, lua_State *L) {
  lua_getglobal(L, "update");
  if (!lua_isfunction(L, -1)) {
    printf("\r is not function");
  }

  lua_pcall(L, 0, 1, 0);
  int t = (int)lua_tonumber(L, -1);
  if (t == 1) {
    printf("\r =====is function=====");
  }
  printf("%d", t);
}
