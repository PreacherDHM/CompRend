#include "lua_Wrapers.h"
#include "lua.h"
#include <lua.hpp>

Render::Renderer *R;


int lua_set_camera_pos(lua_State* L) { 
    lua_Number x = lua_tonumber(L, -2);
    lua_Number y = lua_tonumber(L, -1);
    int posX, posY = 0;
    posX = (int)x;
    posY = (int)y;
    Render::set_rendering_position(R ,posX, posY);
    
    return 0;
}

int lua_add_sprite(lua_State* L) { return 0; }

int lua_create_sprite(lua_State* L) {

    Render::sprite* sprite = (Render::sprite*)lua_newuserdata(L, sizeof(Render::sprite));
    return 1;
}

int lua_create_entity(lua_State* L) {
    Render::sprite* sprite = (Render::sprite*)lua_touserdata(L, -3);
    entity* ent = (entity*)lua_newuserdata(L,sizeof(entity));
    ent->x = 0;
    ent->y = 0;
    ent->sprite = *sprite;
    return 1;
}

int lua_move_entity(lua_State* L) {
    entity* ent = (entity*)lua_touserdata(L, -3);
    float x = (float)lua_tonumber(L, -2);
    float y = (float)lua_tonumber(L, -1);
    set_entity_position(ent, x, y);
    return 0;
}

void init_lua(lua_State* L, Render::Renderer& R) {
    // there is a global list of entitys
    // these entities are called back into c land 
    // there update functions and init functions must
    // always be run.


    lua_pushcfunction(L, lua_add_sprite);
    lua_setglobal(L, "add_sprite");
    lua_pushcfunction(L, lua_set_camera_pos);
    lua_setglobal(L, "camera_pos");
}
