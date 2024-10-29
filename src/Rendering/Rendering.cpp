#include "Rendering.h"
#include <stdio.h>

void Render::init_renderer(Renderer *R) {
  R->mode = {SCREEN_SPACE};
  R->sprite_count = 0;
}

void Render::set_rendering_mode(Render::Renderer *R,
                                Render::rendering_mode mode) {
  R->mode = mode;
}

void Render::add_to_buffer(Renderer *R, csprite* sprite) {
  if (R->sprite_count < MAX_SPRITE_COUNT) {
    R->sprites[R->sprite_count] = sprite;
    R->sprite_count++;
  }
}

void Render::render_buffer(Renderer *R) {
  if (R->W->resize_event) {
    delete R->render_buffer;
    R->render_buffer = new char[R->W->size.X * R->W->size.Y];
    R->render_buffer_size = R->W->size.X * R->W->size.Y;
    R->W->resize_event = false;
  }

  for (int i = 0; i < R->render_buffer_size; i++) {
    R->render_buffer[i] = '\0';
  }
  for (int i = 0; i < R->W->size.X * R->W->size.Y; i++) {
    R->render_buffer[i] = '-';
  }
  // R->render_buffer[0] = '#';
  for (int i = 0; i < R->sprite_count; i++) {
    csprite* s = R->sprites[i];
    if ((s->position.y - (s->bounds.y / 2) + R->W->size.Y / 2 > 0 ||
         s->position.x - (s->bounds.x / 2) + R->W->size.X / 2 > 0) ||
        (s->position.y + (s->bounds.y / 2) + R->W->size.Y / 2 > R->W->size.Y ||
         s->position.x + (s->bounds.x / 2) + R->W->size.X / 2 > R->W->size.X)) {
      // adding sprite to buffer.
      int render_index = 0;
      for (int y = 0; y < s->bounds.y; y++) {
        for (int x = 0; x < s->bounds.x; x++) {
          render_index = y * s->bounds.x + x;
          // sprite
          if ((R->position.x - s->position.x - (s->bounds.x / 2) + x +
                       (R->W->size.X / 2) <
                   R->W->size.X &&
               R->position.y - s->position.y - (s->bounds.y / 2) + y +
                       (R->W->size.Y / 2) <
                   R->W->size.Y) &&
              (R->position.x - s->position.x - (s->bounds.x / 2) + x +
                       (R->W->size.X / 2) >=
                   0 &&
               R->position.y - s->position.y - (s->bounds.y / 2) + y +
                       (R->W->size.Y / 2) >=
                   0)) {

            int buffer_index =
                (((R->W->size.Y / 2 * R->W->size.X)) +
                 ((R->position.y - s->position.y - (s->bounds.y / 2) + y) *
                  R->W->size.X)) +
                ((R->W->size.X / 2) +
                 (R->position.x - s->position.x - (s->bounds.x / 2) + x));
            R->render_buffer[buffer_index] = s->data[render_index];
          }
        }
      }
    }
  }
}
void Render::swop_layer(Renderer *, int) {}
void Render::clear_layer(Renderer *R, int) { R->sprite_count = 0; }
void Render::clear_layers(Renderer *) {}
void Render::set_shader(Renderer *, shader *) {}
void Render::build_shader(Renderer *) {}

void Render::set_rendering_position(Renderer *R, int x, int y) {
  R->position = {x, y};
}
