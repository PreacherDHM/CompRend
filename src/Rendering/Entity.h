#ifndef ENTITY_H
#define ENTITY_H
#include "Csprite.h"

typedef struct {
    float x;
    float y;
} cordnet;

typedef struct {
    bool isInit;
    cordnet position;
    int id;
    const char* name;
    const char* LUA_SCRIPT;
    sprite sprite;
} entity;

// SETTERS
void set_entity_sprite(entity*, sprite sprite);
void set_entity_position(entity*, float, float );
void set_entity_lua_script(entity*, const char*);
void set_entity_id(entity*, int);

//GETTERS
cordnet get_entity_position(entity*);
int get_entity_id(entity*);
sprite get_entity_sprite(entity*);

// MISC

void update_entity_sprite(entity*);
#endif
