#include <lua.h>
#ifndef LUA_RENDERING_H
#define LUA_RENDERING_H

/// # Init Lua Renderer 
///
/// This will init the lua functions for the engine.
void init_lua_renderer();


int lua_add_sprite(lua_State*);
int lua_add_shader(lua_State*);


#endif
