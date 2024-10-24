#ifndef ENTITY_H
#define ENTITY_H
#include "Csprite.h"
#include "lua.hpp"
#include <filesystem>

typedef struct {
    float x;
    float y;
} cordnet;

typedef struct {
    bool isInit;
    cordnet position;
    int id;
    const char* name;
    char* LUA_SCRIPT;
    sprite sprite;
} entity;

// SETTERS
void set_entity_sprite(entity*, sprite sprite);
void set_entity_position(entity*, float, float );
void set_entity_lua_script(entity*, std::filesystem::path);
void set_entity_id(entity*, int);

//GETTERS

/// # Get Entity Position 
///
/// This returns the entities position 
///
/// Returns Cordent
cordnet get_entity_position(entity*);
/// # Get Entity ID 
///
/// This will get the entities ID
///
/// Returns entity ID
int get_entity_id(entity*);
/// # Get Entity Sprite
///
/// This will get the entities sprite.
///
///
/// returns sprite
sprite get_entity_sprite(entity*);

// ----- LUA -----

// LUA_SETTERS

/// # Entity Move (LUA)
///
/// This will move the entity to a cordnet.
///
/// This takes a lua_state*
/// **Returns 0**
int entity_move(lua_State*);
/// # Entity Change Sprite
///
/// This will change the sprite data.
///
/// **Returns 1**
int entity_change_sprite(lua_State*);

// LUA_GETTERS

/// # Entity Get Position
///
/// This will return a table with the position of
/// the entity. {x,y}
/// **Returns 1**
int entity_get_position(lua_State*);
/// # Entity Get ID 
///
/// This will return the entity id.
///
/// **Returns 1**
int entity_get_id(lua_State*);
/// # Entity Get Name 
/// 
/// This will return the name of the entity.
///
/// **Returns 1**
int entity_get_name(lua_State*);

// LUA_MISC

/// # Entity Init Lua
///
/// This will init the entity lua vars.
void entity_init_lua(entity*,lua_State* );
/// # Entity Run Lua 
///
/// This will run the update function for the entity.
void entity_run_lua(entity*, lua_State*);
/// # Entity Create 
/// 
/// This will create a new entity
int entity_create(lua_State *);
#endif
