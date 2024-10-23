#ifndef SCENE_H
#define SCENE_H
#define SCENE_MAX_ENTITY_COUNT 20
#include "Entity.h"
#include "lua.hpp"

typedef struct {
    int entity_count;
    entity entitys[SCENE_MAX_ENTITY_COUNT];
    const char* LUA_SCRIPT;
} scene;

scene* scene_get_current();

void scene_create(scene*);
bool scene_add_entity(scene*, entity);
bool scene_remove_entity(scene*, entity);
void scene_add_lua_script(scene*, const char*);
void scene_run_lua(scene*);
void scene_init_lua(scene*, lua_State*);
void scene_update(scene*);
#endif
