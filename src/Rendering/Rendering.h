#ifndef RENDERING_H
#define RENDERING_H
#include "Window/Window.h"
#include "Shader.h"

/// # character_colection 
///
/// The character colection holds the char data like 
/// a sprite or an image.
typedef struct  {
    char* colection;
    int colection_size;
    struct size{
        int x;
        int y;
    };
    struct position {
        int x;
        int y;
    };
}character_colection;

typedef struct {
    window* W;
    char* layers[5];
} Renderer;

void render_add_to_buffer(char*);
void render_swop_lair(int);
/// # Clear Lair 
/// 
/// This clears the current working lair.
void render_clear_lair();
void render_clear_lairs();
/// # Set Shader
///
/// Set Shader alows an object to have a *shader*.
/// This could look like the object to be a different
/// color or to have an effect.
void render_set_shader(shader*);


#endif
