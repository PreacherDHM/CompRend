#include "Scene.h"
#include "lauxlib.h"
#include "lua.h"
#include "lua.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

scene* current_scene;

scene* scene_get_current() {
    return current_scene;
}

void scene_create(scene* S) {
    S->entity_count = 0;
}

bool scene_add_entity(scene* S, entity *entity) {
    if(S->entity_count < SCENE_MAX_ENTITY_COUNT) {
        S->entity_count++;
        S->entitys[S->entity_count - 1] = entity;
        return true;
    }
    return false;
}
bool scene_remove_entity(scene* S, entity entity) {
    for(int i = 0; i < S->entity_count; i++) {
        if(S->entitys[i]->id == entity.id) {
            for(int j = i + 1; j < S->entity_count; j++) {
                S->entitys[j - 1] = S->entitys[j];
            }
            S->entity_count--;
            return true;
        }
    }
    return false;
}

int scene_set_current_lua(lua_State* L) {
    current_scene = (scene*)lua_touserdata(L,-1);
    return 0;
}

int scene_create_lua(lua_State* L) {
    scene* S = (scene*)lua_newuserdata(L, sizeof(scene));
    scene_create(S);
    return 1;
}

int scene_add_entity_lua(lua_State* L) {
    
    int len = lua_rawlen(L,-1);
    lua_pushstring(L, "obj");
    lua_gettable(L, -2);
    if(!lua_isuserdata(L,-1)) {
        
        printf("is not table\n");
        return 0;
    }
    lua_pop(L, 1);

    lua_getglobal(L,"CompRend");
    lua_getfield(L, -1, "Scene");
    lua_getfield(L, -1, "Entities");
    len = lua_rawlen(L,-1);
    lua_pushinteger(L, 2);
    lua_rawget(L,-4);
    lua_settable(L, -3);
    

    lua_getfield(L, -1, "Entities");
    len = lua_rawlen(L,-1);
    printf("count %d\n", lua_gettop(L));
    //lua_pop(L, 1);
    //lua_pop(L, 1);
    //lua_pop(L, 1);
    lua_getglobal(L,"CompRend");
    lua_getfield(L, -1, "Scene");
    lua_getfield(L, -1, "Entities");
    return 0;
}

int scene_remove_entity_lua(lua_State* L) {
    scene* S = (scene*)lua_touserdata(L, -3);
    entity* E = (entity*)lua_touserdata(L, -2);
    lua_pushboolean(L,scene_remove_entity(S,*E));
    return 1;
}

void scene_add_lua_script(scene* s, std::filesystem::path p) {
    std::filesystem::path path(std::filesystem::current_path() / p);
    std::string line,text;
    std::cout << path << '\n';
    if(std::filesystem::exists(path)) {
        std::cout << "Loading File " << path << "\n";
        std::ifstream f(path);
        while(std::getline(f, line)) {
            text += line + "\n";
        }
        s->script = text;
        f.close();
    }
}

void scene_run_lua(scene*s, lua_State*L) {
    lua_getglobal(L,"CompRend");
    lua_getfield(L, -1, "Scene");
    lua_getfield(L, -1, "Entities");

    int len = lua_rawlen(L, -1);
    for(int i = 1; i <= len; i++) {
        lua_pushnumber(L, i);
        lua_gettable(L, -2);

        lua_pushstring(L, "active");
        lua_gettable(L, -2);
        if(lua_toboolean(L, -1)) {

        lua_pushstring(L, "update");
        lua_gettable(L, -3);
        //lua_getglobal(L, "update");
        if(!lua_isfunction(L, -1)) { 
            std::cout << "ERROR NO Function skipping\n";
            return;
        }
        lua_pcall(L, 0,0,0);
        }
        lua_pop(L, 1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    lua_pop(L, 1);
    lua_pop(L, 1);
    //printf("\r%d", lua_gettop(L));
}
void scene_init_lua(scene* s, lua_State* L) {
    entity_init_lua(L);
    lua_getglobal(L,"CompRend");
    lua_pushstring(L,"Scene");
    lua_newtable(L);

    lua_pushstring(L, "Entities");
    lua_newtable(L);
    lua_settable(L, -3);

    // Takes a ud of type scene and makes scene 
    // the current scene.
    lua_pushstring(L, "SetAsCurrent");
    lua_pushcfunction(L, scene_set_current_lua);
    lua_settable(L, -3);


    // Takes a ud of type scene and of type entity 
    // then adds the entity to scene.
    lua_pushstring(L,"Add");
    lua_pushcfunction(L, scene_add_entity_lua);
    lua_settable(L, -3);

    // Take a ud of type scene and of type entity 
    // then removes entity from the scene.
    lua_pushstring(L,"RemoveEntity"); 
    lua_pushcfunction(L, scene_add_entity_lua);
    lua_settable(L, -3);

    // returns ud of type scene.
    lua_pushstring(L, "CreateScene"); 
    lua_pushcfunction(L, scene_create_lua);
    lua_settable(L, -3);


    lua_settable(L, -3);

    printf("Test Scrip {\n%s\n}", s->script.c_str());
    int error = luaL_dostring(L, s->script.c_str());
    if(error != LUA_OK) {
        std::cout << "\nERROR [LUA]:"<< lua_tostring(L, -1) << "\n";
    }

    lua_getglobal(L,"CompRend");
    lua_getfield(L, -1, "Scene");
    lua_getfield(L, -1, "Entities");

    int len = lua_rawlen(L, -1);
    printf("setting entities %d", len);
    for(int i = 1; i <= len; i++) {
        printf("index %d\n",i);
        lua_pushnumber(L, i);
        lua_gettable(L, -2);

        if(lua_isnil(L,-1)){
            printf("entity nill at position %d\n", i);
            return;
        }
        if(lua_istable(L,-1)){
            lua_pushstring(L, "obj");
            lua_gettable(L, -2);
            if(lua_isuserdata(L,-1)) {
                entity* e = (entity*)lua_touserdata(L, -1);
                printf("Setting entity\n");
                scene_add_entity(s, e);
            } else {
                printf("no user data");
            }
            lua_pop(L,1);
            lua_pop(L,1);
        } else {
            printf("Not table\n");
        }
    }

    lua_pop(L,1);
    lua_pop(L,1);
    lua_pop(L,1);
}
void scene_update(scene*) {}
