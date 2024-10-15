#include "Window.h"
#include <iostream>

void set_window_size(window *W, int x, int y) {
    W->size.X = x;
    W->size.Y = y;
}

void set_window_state(window *W, window_state state) {
    W->state = state;
}
void set_window_input_mode(window *W, window_input_mode input_mode) {
    W->input_mode = input_mode;
}
void set_window_name(window *W, const char *window_name) {
    W->name = window_name;
}
void set_window_buffer(window *W, char *buffer) {
    W->buffer = buffer;
}


window_size get_window_size(window *W) { 
    return W->size; 
}
window_input_mode get_window_input_mode(window *W) { 
    return W->input_mode; 
}
window_state get_window_state(window *W) { 
    return W->state; 
}
const char *get_window_input(window *W) { 
    return W->name; 
}

void window_draw(window *W) {
    std::cout << W->buffer;
}
void window_clear_buffer(window *W) {
    W->buffer[0] = '\0';
}
