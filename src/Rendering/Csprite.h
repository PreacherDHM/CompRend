#ifndef C_SPRITE_H
#define C_SPRITE_H

/// # sprite
///
/// The sprite holds the char data like a image.
struct bounds {
  int x;
  int y;
};
typedef struct {
  int x;
  int y;
}position ;
typedef struct {
  const char *data;
  int data_size;
  bounds bounds;
  position position;
} sprite;

sprite sprite_create();
sprite sprite_create(int, int, const char*);
sprite sprite_create(int, int, int, int, const char*);
#endif
