#include "Entity.h"
#include "Csprite.h"
#include "filesystem"
#include <cmath>

//SETTERS
void set_entity_sprite(entity*E, sprite sprite) {
    E->sprite = sprite;
}

void set_entity_position(entity *E, float x, float y) {
   E->position.x = x;
   E->position.y = y;
   int spx,spy = 0;
   spx = static_cast<int>(round(x));
   spy = static_cast<int>(round(y));
   E->sprite.position = {spx,spy};
}

void set_entity_lua_script(entity*) {
    std::filesystem::path lua_dir = "./lua";
    std::filesystem::path path = lua_dir / "./";
    // TODO ADD LUA FILE PATH
}
void set_entity_id(entity*, int) {}

//GETTERS

/// # Get Entity Position
///
/// This gets the position of the entity.
cordnet get_entity_position(entity* E) { return E->position; }
/// # Get Entity Id
///
/// This gets the id of the entity.
int get_entity_id(entity* E) { return E->id; }

/// # Get Entity Sprite
///
/// Returns the entities csprite.
sprite get_entity_sprite(entity* E) {return E->sprite;}

//MISC

