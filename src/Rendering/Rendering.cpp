#include <tchar.h>
#include "Rendering.h"
#include <cstring>
#include <stdio.h>
#include <iostream>

void Render::init_renderer(Renderer *R) {
  R->mode = {SCREEN_SPACE};
  R->sprite_count = 0;
}

void Render::set_rendering_mode(Render::Renderer *R,
                                Render::rendering_mode mode) {
  R->mode = mode;
}

void Render::add_to_buffer(Renderer *R, csprite *sprite) {
  if (R->sprite_count < MAX_SPRITE_COUNT) {
    R->sprites[R->sprite_count] = sprite;
    R->sprite_count++;
  }
}

void Render::render_buffer(Renderer *R) {
  int shader_offset = 0;


  if (R->W->resize_event) {
    delete R->render_buffer;
    R->render_buffer = new wchar_t[100000];
    R->render_buffer_size = R->W->size.X * R->W->size.Y;
    R->W->resize_event = false;
  }

  // init buffer
  for (int i = 0; i < 100000; i++) {
    R->render_buffer[i] = '&';
  }

  // R->render_buffer[0] = '#';

  // rendering sprites
  for (int i = R->sprite_count - 1; i >= 0; i--) {
    csprite *s = R->sprites[i];
	//std::cout << "Sprite at index" << i << "\n";
    int size_of_shader = 0;
    if (wcslen(s->shader) > 2) {
      size_of_shader = wcslen(s->shader);
    }
    if ((s->position.y - (s->bounds.y / 2) + R->W->size.Y / 2 > 0 ||
         s->position.x - (s->bounds.x / 2) + R->W->size.X / 2 > 0) ||
        (s->position.y + (s->bounds.y / 2) + R->W->size.Y / 2 > R->W->size.Y ||
         s->position.x + (s->bounds.x / 2) + R->W->size.X / 2 > R->W->size.X)) {
      // adding sprite to buffer.
      int render_index = 0;
      bool rendered_shader = false;
      for (int y = 0; y < s->bounds.y; y++) {
          

        rendered_shader = false;
        int last_buffer_index = 0;

        for (int x = 0; x < s->bounds.x; x++) {
          render_index = y * s->bounds.x + x;
          if (s->data[render_index]== ' ') {
            continue;
          }

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


            
            if (size_of_shader > 2 && !rendered_shader) {
              shader_offset += size_of_shader;
            }
            
            int shader_shift;
            int buffer_index =
                ((((R->W->size.Y / 2 * R->W->size.X)) +
                 ((R->position.y - s->position.y - (s->bounds.y / 2) + y) *
                  R->W->size.X)) +
                (((R->W->size.X) / 2) +
                 (R->position.x - s->position.x - (s->bounds.x / 2) + x))) + shader_offset;

            if (size_of_shader > 1 && !rendered_shader) {
              for (int j = 0; j < size_of_shader; j++) {
                R->render_buffer[buffer_index + j - size_of_shader] = s->shader[j];
              }
              rendered_shader = true;
            }
            R->render_buffer[buffer_index] =
                s->data[render_index];
            last_buffer_index = buffer_index +size_of_shader;
          }
        }
        if (rendered_shader) {
          const char *reset = "\e[0m";
          for (int j = 0; j < 4; j++) {
            R->render_buffer[last_buffer_index - size_of_shader + 1 + j] = reset[j];
          }
          shader_offset += 4;
          for(int j = 0; j < size_of_shader + 8; j++) {
            R->render_buffer[last_buffer_index + shader_offset + j] = '-';
          }
        }
      }
    }
  }

  int render_buffer_offset = 0;
  for (int i = 0; i < (R->W->size.X * R->W->size.Y) + shader_offset; i++) {
    if (R->render_buffer[i] == '\e') {
      while (R->render_buffer[i + render_buffer_offset] != 'm') {
        render_buffer_offset++;
      }
    }
    if (R->render_buffer[i + render_buffer_offset] == '&') {
      R->render_buffer[i + render_buffer_offset] = '-';
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
