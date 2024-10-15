#include "Window.h"

void set_window_size(window* W, int x, int y) {}
void set_window_state(window* W, window_state state) {}
void set_window_input_mode(window* W, window_input_mode inputMode) {}
void set_window_name(window* W, const char* windowName) {}
void set_window_buffer(window* W, char* buffer) {}

window_size get_window_size(window* W) { return {};}
window_input_mode get_window_input_mode(window* W) {return {};}
window_state get_window_state(window* W) { return {}; }
char* get_window_input(window* W) {return "test";}

