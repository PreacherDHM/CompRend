#ifndef ENTITY_H
#define ENTITY_H
#include "Rendering.h"


typedef struct {
    bool isInit;
    float x; 
    float y;
    int id;
    const char* LUA_SCRIPT;
    Render::sprite sprite;
} entity;

void set_entity_sprite(entity*, Render::sprite sprite);
void set_entity_position(entity*, float, float );
void set_entity_lua_script(entity*, const char*);
void set_entity_id(entity*, int);

#endif
