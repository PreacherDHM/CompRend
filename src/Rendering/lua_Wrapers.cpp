#include "lua_Wrapers.h"
#include "Entity.h"
#include "cstring"

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

    const char* data;
    lua_Number boundsX;
    lua_Number boundsY;

    if(lua_isstring(L, -3)) {
        data = lua_tostring(L, -3);

        if(lua_isnumber(L, -2)) {
            boundsX = lua_tonumber(L, -2);
        }
        if(lua_isnumber(L, -1)) {
            boundsY = lua_tonumber(L, -1);
        }
    } else {
        data = "^*^*^^*^*^^*^*^^*^*^^*^*^";
        boundsX = 5.0f;
        boundsY = 5.0f;
    }

    //sprite* sprite = (sprite*)lua_newuserdata(L, sizeof(sprite));
    //sprite->data = data;
    //sprite->bounds = {(int)boundsX, (int)boundsY};
    //sprite->data_size = (int)boundsX * (int)boundsY;
    return 1;
}



// ENTITY

int lua_create_entity(lua_State* L) {
    //sprite* sprite = (sprite*)lua_touserdata(L, -3);
    entity* ent = (entity*)lua_newuserdata(L,sizeof(entity));
    ent->position = { 0.0f, 0.0f};
    //ent->sprite = *sprite;
    return 1;
}

int lua_move_entity(lua_State* L) {
    entity* ent = (entity*)lua_touserdata(L, -3);
    float x = (float)lua_tonumber(L, -2);
    float y = (float)lua_tonumber(L, -1);
    set_entity_position(ent, x, y);
    return 0;
}


// INIT

void init_lua(lua_State* L, Render::Renderer& R) {
    // there is a global list of entitys
    // these entities are called back into c land 
    // there update functions and init functions must
    // always be run.

    lua_pushcfunction(L, lua_add_sprite);
    lua_setglobal(L, "add_sprite");
    lua_pushcfunction(L, lua_set_camera_pos);
    lua_setglobal(L, "camera_pos");
    lua_pushcfunction(L, lua_create_sprite);
    lua_setglobal(L, "create_sprite");
    lua_pushcfunction(L, lua_create_entity);
    lua_setglobal(L, "create_entity");
    lua_pushcfunction(L, lua_move_entity);
    lua_setglobal(L, "move_entity");
    
}
