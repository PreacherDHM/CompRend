#ifndef RENDERING_H
#define RENDERING_H
#include <Window.h>
#include <Shader.h>
#include "Csprite.h"
#ifndef MAX_SPRITE_COUNT
#define MAX_SPRITE_COUNT 25
#endif

namespace Render {
        struct bounds{
            int x;
            int y;
        };
        struct rendering_position {
            int x;
            int y;
        };


    enum rendering_mode{
        WORLD_SPACE,
        SCREEN_SPACE
    };

    typedef struct {
        window* W;
        char* layers[300 * 200];
        rendering_mode mode;
        char* render_buffer;
        csprite* sprites[MAX_SPRITE_COUNT];
        int render_buffer_size;
        int sprite_count;
        int partical_count;
        int current_layer;
        rendering_position position;
    } Renderer;

    
    /// # Set Rendering Mode
    ///
    /// This will set the rendering mode of the renderer. *IE world and ui modes.*
    void init_renderer(Renderer*);
    void set_rendering_mode(Renderer*, rendering_mode mode);
    void add_to_buffer(Renderer*, csprite*);
    void render_buffer(Renderer*);
    void swop_layer(Renderer*, int);
    void clear_layer(Renderer*, int);
    void clear_layers(Renderer*);
    void set_shader(Renderer*, shader*);
    void build_shader(Renderer*);

    void set_rendering_position(Renderer*, int, int);
}


#endif
