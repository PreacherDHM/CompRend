#ifndef SCENE_H
#define SCENE_H
#include "Entity.h"

typedef struct {
    entity entitys[20];
    const char* LUA_SCRIPT;
} scene;
#endif
