#include "Scene.h"
#include "lua.hpp"

scene* current_scene;

scene* scene_get_current() {
    return current_scene;
}

void scene_create(scene* S) {
    S->entity_count = 0;
}

bool scene_add_entity(scene* S, entity entity) {
    if(S->entity_count < SCENE_MAX_ENTITY_COUNT) {
        S->entity_count++;
        S->entitys[S->entity_count - 1] = entity;
        return true;
    }
    return false;
}
bool scene_remove_entity(scene* S, entity entity) {
    for(int i = 0; i < S->entity_count; i++) {
        if(S->entitys[i].id == entity.id) {
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
    scene S;
    scene_create(&S);
    lua_pushlightuserdata(L,&S);
    return 1;
}

int scene_add_entity_lua(lua_State* L) {
    scene* S = (scene*)lua_touserdata(L, -3);
    entity* E = (entity*)lua_touserdata(L, -2);
    lua_pushboolean(L,scene_add_entity(S,*E));
    return 1;
}

int scene_remove_entity_lua(lua_State* L) {
    scene* S = (scene*)lua_touserdata(L, -3);
    entity* E = (entity*)lua_touserdata(L, -2);
    lua_pushboolean(L,scene_remove_entity(S,*E));
    return 1;
}

void scene_add_lua_script(scene*, const char*) {}
void scene_run_lua(scene*) {}
void scene_init_lua(scene*, lua_State* L) {
    lua_getglobal(L,"CompRend");
    lua_pushstring(L,"Scene");
    lua_newtable(L);


    // Takes a ud of type scene and makes scene 
    // the current scene.
    lua_pushstring(L, "SetAsCurrent");
    lua_pushcfunction(L, scene_set_current_lua);
    lua_settable(L, -3);


    // Takes a ud of type scene and of type entity 
    // then adds the entity to scene.
    lua_pushstring(L,"AddEntity");
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
}
void scene_update(scene*) {}
