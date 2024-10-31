#ifndef WINDOW_H
#define WINDOW_H

enum window_state { RESIZEABLE, NONRESIZEABLE };

enum window_input_mode { RAW, SUBMITION };

/// # window size
///
/// this struct holds the window size in chars
/// horizontaly and verticly
typedef struct {
  int X;
  int Y;
} window_size;

typedef struct {
    char message[128];
    void* object;
}Event;

struct window {
  window_size size = {0, 0};
  window_state state = {RESIZEABLE};
  window_input_mode input_mode = {RAW};
  const char *name = "";
  const char *buffer = "testing on the test\n thest\n";
  int buffer_size;
  bool resize_event;
};

void window_init(window*);
void update_window_events(window*);

void set_window_size(window *, int, int);
void set_window_state(window *, window_state);
void set_window_input_mode(window *, window_input_mode);
void set_window_name(window *, const char *);
void set_window_buffer(window *, char*, int);
void set_window_get_input();
void set_window_start_input();

window_size get_window_size(window *);
window_input_mode get_window_input_mode(window *);
window_state get_window_state(window *);
const char *get_window_input(window *);
float get_window_delta_time();
bool get_window_key_down(const char);
bool get_window_key_press(const char);

bool get_window_resize_event(window *);

void window_draw(window *);
void window_clear_buffer(window *);
#endif
