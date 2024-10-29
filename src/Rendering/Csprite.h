#ifndef C_SPRITE_H
#define C_SPRITE_H

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
  const char *data;
  int data_size;
  csprite_bounds bounds;
  csprite_position position;
} csprite;

csprite sprite_create();
csprite sprite_create(int, int, const char*);
csprite sprite_create(int, int, int, int, const char*);
#endif
