#ifndef RENDERING_H
#define RENDERING_H
#include <Window.h>
#include <Shader.h>

namespace Render {
    /// # sprite 
    ///
    /// The sprite holds the char data like a image.
    typedef struct  {
        char* data;
        int data_size;
        struct bounds{
            int x;
            int y;
        };
        struct position {
            int x;
            int y;
        };
    }sprite;


    enum rendering_mode{
        WORLD_SPACE,
        SCREEN_SPACE
    };

    typedef struct {
        window* W;
        char* layers[5];
        rendering_mode mode;
        const char renderBuffer[1024* 12];
    } Renderer;

    
    void set_rendering_mode(Renderer, rendering_mode mode);
    void add_to_buffer(Renderer*, sprite);
    void swop_layer(Renderer*, int);
    void clear_layer(Renderer*, int);
    void clear_layers(Renderer*);
    void set_shader(Renderer*, shader*);
    void build_shader(Renderer*);
}


#endif
