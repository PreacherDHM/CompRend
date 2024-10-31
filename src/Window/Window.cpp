#include "Window.h"

#ifdef _Linux

#include <stdio.h>
#include <thread>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

static bool did_work = false;
std::thread worker;
static char input_buffer[127];
static int input_index;
static char input[127];


const char* clear = "'\033[2J'";
void set_window_size(window *W, int x, int y) {
  //W->size.X = x;
  //W->size.Y = y;
  //WriteFile(outHandle, clear, strlen(clear), NULL, NULL);
  //W->resize_event = true;
}

/// # Set Window State
///
/// This will set the console window state.
void set_window_state(window *W, window_state state) { W->state = state; }

/// # Set Window Input Mode 
/// 
/// This will set the window input mode.
void set_window_input_mode(window *W, window_input_mode input_mode) {
  W->input_mode = input_mode;
}

/// # Set Window name
///
/// This will change the name of the console.
void set_window_name(window *W, const char *window_name) {
  W->name = window_name;
}

/// # Set Window Buffer
///
/// This will set the window buffer that it will be rendering from.
void set_window_buffer(window *W, char *buffer, int size) { W->buffer = buffer; W->buffer_size = size; }

/// # Get Window Size
///
/// This will return the window size.
window_size get_window_size(window *W) { return W->size; }

/// # Get Window Input Mode 
///
/// this returns the input mode of the console.
window_input_mode get_window_input_mode(window *W) { return W->input_mode; }

/// # Get Window State 
///
/// This will return the console window state.
window_state get_window_state(window *W) { return W->state; }

/// # Get Window input 
///
/// This will return the console input from the user.
const char *get_window_input(window *W) { return input; }

/// window_draw
///
/// Draws the window buffer to the console
void window_draw(window *W) {
    write(STDOUT_FILENO,"\033[?25l",6);
    write(STDOUT_FILENO,"\033[0;0f", 6);
    write(STDOUT_FILENO, W->buffer, W->buffer_size);
}

/// # Window Clear Buffer
///
/// This will clear the window buffer.
void window_clear_buffer(window *W) {
  // W->buffer[0] = '\0';
}

// This worker get the input from the user and puts it in input_buffer
void DoWork() {

}
/// # Input Event Start 
///
/// This will start the input event thread.
void input_event_start() { worker = std::thread(DoWork); }

/// # Window Close 
///
/// This runs when the window closes.
void window_close() {}

/// # Get Window Resize Event
///
/// The Returns true if the window has been resize.
///
/// **This will reset the event bake to false when called.**
bool get_window_resize_event(window* W) {
    if(W->resize_event) {
        W->resize_event = false;
        return true;
    }
    return false;
}

/// # Window Init 
/// 
/// This inits the window and starts up cushial functions.
void window_init(window *W) {
  printf("\033[2J");
  printf("\033[s");
  struct winsize ws;
  ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws);
  W->size.X = ws.ws_col;
  W->size.Y = ws.ws_row;
  W->resize_event = true;



  update_window_events(W);

}

/// # Update Window Events 
///
/// This updates all of the console events.
void update_window_events(window *W) {
  struct winsize ws;
  ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws);
  if(W->size.X != ws.ws_col || W->size.Y != ws.ws_row)
  W->size.X = ws.ws_col;
  W->size.Y = ws.ws_row;

}
#endif


/*=====================================================
 * WINDOWS
 *=====================================================
 * */




#ifdef _WIN32
#include "windows.h"
#include "Windows.h"
#include <chrono>
#include <conio.h>
#include <stdio.h>
#include <thread>
#include <winuser.h>

HANDLE outHandle;
HANDLE inHandle;

static bool get_input = false;
std::thread worker;
static char input_buffer[127];
static int input_index;
static char input[127];
static int input_size;

float delta_time;

std::chrono::time_point tp2 = std::chrono::system_clock::now();
std::chrono::time_point tp1= std::chrono::system_clock::now();;

const char* clear = "'\033[2J'";
void set_window_size(window *W, int x, int y) {
  W->size.X = x;
  W->size.Y = y;
  WriteFile(outHandle, clear, strlen(clear), NULL, NULL);
  W->resize_event = true;
}

/// # Set Window State
///
/// This will set the console window state.
void set_window_state(window *W, window_state state) { W->state = state; }

/// # Set Window Input Mode 
/// 
/// This will set the window input mode.
void set_window_input_mode(window *W, window_input_mode input_mode) {
  W->input_mode = input_mode;
}

/// # Set Window name
///
/// This will change the name of the console.
void set_window_name(window *W, const char *window_name) {
  W->name = window_name;
}

/// # Set Window Buffer
///
/// This will set the window buffer that it will be rendering from.
void set_window_buffer(window *W, char *buffer, int size) { W->buffer = buffer; W->buffer_size = size; }

/// # Get Window Size
///
/// This will return the window size.
window_size get_window_size(window *W) { return W->size; }

/// # Get Window Input Mode 
///
/// this returns the input mode of the console.
window_input_mode get_window_input_mode(window *W) { return W->input_mode; }

/// # Get Window State 
///
/// This will return the console window state.
window_state get_window_state(window *W) { return W->state; }

/// # Get Window input 
///
/// This will return the console input from the user.
const char *get_window_input(window *W) { return input; }


float get_window_delta_time() {
    return delta_time;
}


bool get_window_key_down(const char c) { 
    for(int i = 0; i < input_size; i++) {
        if( c == input[i]) {
            return true;
        }
    }
    return false;
}

bool keypressed = false;

bool get_window_key_press(const char c) {
    for(int i = 0; i < input_size; i++) {
        if( c == input[i] ) {
            if(keypressed == false) {
                keypressed = true;
                return true;
            } else  {
                return false;
            }
        }
    }
    keypressed = false;
    return false;
}

/// window_draw
///
/// Draws the window buffer to the console
void window_draw(window *W) {
  DWORD dwBytesWritten = 0;
  WriteConsoleOutputCharacter(outHandle, W->buffer, W->buffer_size, {0,0}, &dwBytesWritten);
}

void set_window_get_input() { 
    get_input = false;
  if(input_index > 0) {
      for(int i = 0; i < input_index; i++){
        input[i] = input_buffer[i];
      }
      input_size = input_index;
  }
  input_index = 0;
}
void set_window_start_input() { 
    get_input = true;
    for(int i = 0; i < input_size; i++){
        input[i] = '\0';
    }
    input_size = 0;
}

/// # Window Clear Buffer
///
/// This will clear the window buffer.
void window_clear_buffer(window *W) {
  // W->buffer[0] = '\0';
  WriteFile(outHandle, "\033[2J", 4,NULL, NULL);

}

// This worker get the input from the user and puts it in input_buffer
void DoWork() {
  char buffer[127];
  DWORD read_count;
  while(true) {
    if(get_input) {
        if(_kbhit()) {
          ReadFile(inHandle,buffer,127,&read_count,NULL);
          for(int i = 0; i < read_count; i++) {
              input_buffer[input_index] = buffer[i];
              input_index ++;
          }
        }
    }
  }
}
/// # Input Event Start 
///
/// This will start the input event thread.
void input_event_start() { worker = std::thread(DoWork); }

/// # Window Close 
///
/// This runs when the window closes.
void window_close() {}

/// # Get Window Resize Event
///
/// The Returns true if the window has been resize.
///
/// **This will reset the event bake to false when called.**
bool get_window_resize_event(window* W) {
    if(W->resize_event) {
        W->resize_event = false;
        return true;
    }
    return false;
}

/// # Window Init 
/// 
/// This inits the window and starts up cushial functions.
void window_init(window *W) {
  outHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(outHandle);
  inHandle = GetStdHandle(STD_INPUT_HANDLE);
  W->resize_event = true;

  DWORD dwMode = 0;
  GetConsoleMode(inHandle, &dwMode);
  dwMode = ENABLE_PROCESSED_INPUT;
  SetConsoleMode(inHandle, dwMode);
  update_window_events(W);

  CONSOLE_CURSOR_INFO lpCursor;
  lpCursor.bVisible = false;
  lpCursor.dwSize = 10;
  SetConsoleCursorInfo(outHandle, &lpCursor);
  //input_event_start();
  tp2 = std::chrono::system_clock::now();
  tp1 = std::chrono::system_clock::now();

}

/// # Update Window Events 
///
/// This updates all of the console events.
void update_window_events(window *W) {

  CONSOLE_SCREEN_BUFFER_INFO cbiInfo;
  GetConsoleScreenBufferInfo(outHandle, &cbiInfo);



  tp2 = std::chrono::system_clock::now();
  std::chrono::duration<float> elapsedTime = tp2 - tp1;
  tp1 = tp2;
  delta_time = elapsedTime.count();


  if (W->size.X != cbiInfo.dwSize.X || W->size.Y != cbiInfo.dwSize.Y) {
    set_window_size(W, (int)cbiInfo.dwSize.X, (int)cbiInfo.dwSize.Y);
  }

}
#endif
