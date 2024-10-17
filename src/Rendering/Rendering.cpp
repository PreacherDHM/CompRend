#include "Rendering.h"

void Render::init_renderer(Renderer *R) {
  R->mode = {SCREEN_SPACE};
  R->sprite_count = 0;
}

void Render::set_rendering_mode(Render::Renderer *R,
                                Render::rendering_mode mode) {
  R->mode = mode;
}

void Render::add_to_buffer(Renderer *R, sprite sprite) {
  if (R->sprite_count < MAX_SPRITE_COUNT) {
    R->sprites[R->sprite_count] = sprite;
    R->sprite_count++;
  }
}

void Render::render_buffer(Renderer *R) {
  if (R->mode == WORLD_SPACE) {
    for (int i = 0; i < R->sprite_count; i++) {
      sprite s = R->sprites[i];
      if ((s.position.y - s.bounds.y / 2 + R->W->size.Y / 2 > 0 &&
           s.position.x - s.bounds.x / 2 + R->W->size.X / 2 > 0) ||
          (s.position.y + s.bounds.y / 2 + R->W->size.Y / 2 > R->W->size.Y &&
           s.position.x + s.bounds.x / 2 + R->W->size.X / 2 > R->W->size.X)) {
        // adding sprite to buffer.
        int render_index = 0;
        for (int y = 0; y < s.bounds.y; y++) {
          for (int x = 0; x < s.bounds.x; x++) {
            render_index = y * s.bounds.x + x;
            // sprite
            if ((s.position.x + (s.bounds.x / 2) + x + R->W->size.X / 2 <
                     R->W->size.X &&
                 s.position.y + (s.bounds.y / 2) + x + R->W->size.Y / 2 <
                     R->W->size.Y) ||
                (s.position.x + (s.bounds.x / 2) + x + R->W->size.X / 2 > 0 &&
                 s.position.y + (s.bounds.y / 2) + x + R->W->size.Y / 2 > 0)) {

              int buffer_index =
                  (((R->W->size.Y * R->W->size.X) / 2) +
                   ((s.position.y - (s.bounds.y / 2 + y)) * R->W->size.X)) +
                  (R->W->size.X / 2 + (s.position.x - (s.bounds.x / 2)));
              R->render_buffer[buffer_index] = s.data[render_index];
            }
          }
        }
      }
    }
  }
}
void Render::swop_layer(Renderer *, int) {}
void Render::clear_layer(Renderer *, int) {}
void Render::clear_layers(Renderer *) {}
void Render::set_shader(Renderer *, shader *) {}
void Render::build_shader(Renderer *) {}
