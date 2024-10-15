#ifndef WINDOW_H
#define WINDOW_H

    enum window_state {
        RESIZEABLE,
        NONRESIZEABLE
    };
    enum window_input_mode {
        RAW,
        SUBMITION
    };

    typedef struct {
        int X;
        int Y;
    } window_size;

    struct window {
        window_size size = {0,0};
        window_state state = { RESIZEABLE };
        window_input_mode input_state = { RAW };
        const char* name = "";
    };

    void set_window_size(window*, int, int);
    void set_window_state(window*, window_state);
    void set_window_input_mode(window*, window_input_mode);
    void set_window_name(window*, const char*);
    void set_window_buffer(window*, char*);

    window_size get_window_size(window*);
    window_input_mode get_window_input_mode(window*);
    window_state get_window_state(window*);
    char* get_window_input(window*);
#endif
