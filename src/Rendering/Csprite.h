#ifndef C_SPRITE_H
#define C_SPRITE_H
#include <lua.hpp>

/// # sprite
///
/// The sprite holds the char data like a image.
struct csprite_bounds {
  int x;
  int y;
};

typedef struct {
  int x;
  int y;
}csprite_position ;

typedef struct {
    int start_id;
    int end_id;
    int current_id;
} canimation;

typedef struct {
  const char *data;
  int data_size;
  csprite_bounds bounds;
  csprite_position position;
  canimation animation;
} csprite;

csprite sprite_create();
csprite sprite_create(int, int, const char*);
csprite sprite_create(int, int, int, int, const char*);

void csprite_init_lua(lua_State*);
#endif
