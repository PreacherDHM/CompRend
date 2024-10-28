#ifndef SCENE_H
#define SCENE_H
#define SCENE_MAX_ENTITY_COUNT 20
#include "Entity.h"
#include "lua.hpp"
#include "Rendering.h"

typedef struct {
    int entity_count;
    int scene_id;
    entity *entitys[SCENE_MAX_ENTITY_COUNT];
    Render::Renderer* R;
    std::string script;
} scene;

scene* scene_get_current();

void scene_create(scene*);
bool scene_add_entity(scene*, entity*);
bool scene_remove_entity(scene*, entity*);
void scene_add_lua_script(scene*, std::filesystem::path);
void scene_run_lua(scene*, lua_State*);
void scene_init_lua(scene*, lua_State*);
void scene_update(scene*);
#endif
