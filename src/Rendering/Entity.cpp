#include "Entity.h"
#include "Scene.h"
#include "Csprite.h"
#include "filesystem"
#include "lauxlib.h"
#include "lua.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <assert.h>
#include <iostream>
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

void set_entity_lua_script(entity *E, std::filesystem::path poo) { 
    std::filesystem::path p("foo.lua");

    std::cout << poo << "\n";
    if(std::filesystem::exists(p)) {
        printf("file exists\n");
        std::ifstream f(p);
        std::string line,text;
        while(std::getline(f, line)) {
            text += line + "\n";
        }

        printf("%s\n",text);
        f.close();
    }
    
    

}

cordnet get_entity_position(entity *E) { return E->position; }
int get_entity_id(entity *E) { return E->id; }
sprite get_entity_sprite(entity *E) { return E->sprite; }

// Creates a entity in lua
int entity_create(lua_State *L) {
    entity* E = (entity*)lua_newuserdata(L, sizeof(entity));
    E->id = rand();
    E->sprite = sprite();
    E->name = "hello there";
    E->position = {4,5};
    //scene_add_entity(scene_get_current(), E);
    
    return 1; 
}

int entity_move(lua_State *L) { 
    entity* e = (entity*)lua_touserdata(L,-3);
    float x = (float)lua_tonumber(L, -2);
    float y = (float)lua_tonumber(L, -1);
    e->position = {x,y};

    return 0; 
}

int entity_change_sprite(lua_State *) { return 0; }
int entity_get_position(lua_State *) { return 0; }
int entity_get_id(lua_State *) { return 0; }
int entity_get_name(lua_State *L) { 
    entity* e =  (entity*)lua_touserdata(L,-1);
    lua_newtable(L);

    lua_pushstring(L,"x");
    lua_pushnumber(L, e->position.x);

    lua_pushstring(L,"y");
    lua_pushnumber(L, e->position.y);

    printf("running");

    return 0; 
}
void entity_init_lua(entity *E, lua_State *L) {

  lua_newtable(L);
  lua_setglobal(L, "CompRend");

  //int table = lua_gettop(L);
  lua_getglobal(L, "CompRend");
  //  printf("table\n");

    lua_pushstring(L, "Entity");
    lua_newtable(L);

    lua_pushstring(L, "Create");
    lua_pushcfunction(L, entity_create);
    lua_settable(L, -3);

    lua_pushstring(L, "Move");
    lua_pushcfunction(L, entity_move);
    lua_settable(L, -3);

    //lua_pushstring(L, "ChangeSprite");
    //lua_pushcfunction(L, entity_change_sprite);
    //lua_settable(L, -3);

    //lua_pushstring(L, "GetId");
    //lua_pushcfunction(L, entity_get_id);
    //lua_settable(L, -3);

    //lua_pushstring(L, "GetName");
    //lua_pushcfunction(L, entity_get_name);
    //lua_settable(L, -3);

    //lua_pushstring(L, "GetPosition");
    //lua_pushcfunction(L, entity_get_name);
    //lua_settable(L, -3);


    lua_settable(L, -3);

    printf("Test Scrip {\n%s\n}", E->LUA_SCRIPT);

}

void entity_run_lua(entity *E, lua_State *) {
    
}
