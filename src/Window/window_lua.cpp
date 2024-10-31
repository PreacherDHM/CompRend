#include "window_lua.h"
#include "Window.h"
#include "Windows.h"

int lua_window_get_key_down(lua_State*L) {
    if(lua_isstring(L, -1)) {
        const char* c = lua_tostring(L, -1);
        lua_pushboolean(L, GetAsyncKeyState((unsigned short)c[0]) & 0x8000);
        return 1;
    }
    lua_pushboolean(L, false);
    return 1;
}

int lua_window_get_key_press(lua_State*L) {
    if(lua_isstring(L, -1)) {
        const char* c = lua_tostring(L, -1);

        lua_pushboolean(L, GetAsyncKeyState((unsigned short)c[0]) & 0x8000);
        return 1;
    }
    lua_pushboolean(L, false);
    return 1;
}


int lua_window_get_delta_time(lua_State* L) {
    lua_pushnumber(L,get_window_delta_time());
    return 1;
}

void lua_window_init(lua_State* L) {
    lua_getglobal(L, "CompRend");

    lua_pushstring(L, "GetKeyDown");
    lua_pushcfunction(L,lua_window_get_key_down);
    lua_settable(L, -3);

    lua_pushstring(L, "GetKey");
    lua_pushcfunction(L,lua_window_get_key_press);
    lua_settable(L, -3);

    lua_pushstring(L, "DeltaTime");
    lua_pushcfunction(L,lua_window_get_delta_time);
    lua_settable(L, -3);


    lua_pop(L, -1);

}
