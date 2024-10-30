#include "Csprite.h"
#include "lua.h"

csprite sprite_create() {
    csprite s;
    s.bounds.x = 9;
    s.bounds.y = 1;
    s.position.x = 0;
    s.position.y = 0;
    s.data = "hii there";
    s.data_size = s.bounds.x * s.bounds.y;
    return s;
}

csprite sprite_create(int boundsX,int boundsY, const char* data) {
    csprite s;
    s.bounds.x = boundsX;
    s.bounds.y = boundsY;
    s.position.x = 0;
    s.position.y = 0;
    s.data = data;
    s.data_size = s.bounds.x * s.bounds.y;
    return csprite();
}

csprite sprite_create(int boundsX,int boundsY, int positionX, int positionY, const char* data) {
    csprite s;
    s.bounds.x = boundsX;
    s.bounds.y = boundsY;
    s.position.x = positionX;
    s.position.y = positionY;
    s.data = data;
    s.data_size = s.bounds.x * s.bounds.y;
    return csprite();
}

int lua_csprite_create(lua_State* L) {
    csprite* cs = (csprite*)lua_newuserdata(L, sizeof(csprite));
    lua_gettable(L, -1);
    lua_pushstring(L, "data");
    lua_gettable(L, -2);
    if(lua_istable(L, -1)) {
        int data_size = lua_rawlen(L, -1);
        for (int i = 1; i <= data_size; i++) {
            lua_pushnumber(L, 1);
            lua_gettable(L, -2);

            lua_pushstring(L, "id");
            lua_gettable(L, -1);
            if(lua_isnumber(L, -1)) {
                
            }
        }
    }
    return 0;
}

void csprite_init_lua(lua_State* L) {
    lua_getglobal(L, "CompRend");
    lua_pushstring(L,"CSprie");
    lua_newtable(L);

    lua_pushstring(L, "Create");
    lua_pushcfunction(L,lua_csprite_create);
    lua_settable(L, -3);

    lua_settable(L, -3);
}
