#include <cstdio>
#include "Window.h"
#include "lua.hpp"
#include <Rendering.h>
int main() {
    Render::Renderer R = {};
    window W = {};
    window_init(&W);
    while(true) {
        update_window_events(&W);
        window_draw(&W);
    }
    lua_State* L = luaL_newstate();
    luaL_dostring(L, "x = 47");
    lua_getglobal(L, "x");
    lua_Number x = lua_tonumber(L, 1);
    printf("hi %d", (int)x);
    lua_close(L);
    return 0;
}
