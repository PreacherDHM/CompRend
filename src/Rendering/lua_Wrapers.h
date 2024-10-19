#ifndef LUA_RENDERING_H
#define LUA_RENDERING_H

#include <lua.hpp>
#include "Rendering.h"

/// # Init Lua Renderer 
///
/// This will init the lua functions for the engine.
void init_lua(lua_State*, Render::Renderer& R);


// sprite
//int lua_add_sprite(lua_State*);
//int lua_create_sprite(lua_State*);
//int lua_add_shader(lua_State*);
//
//// Renderer
//int lua_set_camera_pos(lua_State* L);
//
//// entity 
//int lua_create_entity(lua_State* L);
//int lua_add_entity(lua_State* L);

#endif
