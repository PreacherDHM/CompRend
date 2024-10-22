#include "Window.h"

#ifdef _WIN32
#include "windows.h"
#include <conio.h>
#include <stdio.h>
#include <thread>
#include <winuser.h>

HANDLE outHandle;
HANDLE inHandle;

static bool did_work = false;
std::thread worker;
static char input_buffer[127];
static int input_index;
static char input[127];

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

/// window_draw
///
/// Draws the window buffer to the console
void window_draw(window *W) {
  DWORD dwBytesWritten = 0;
  WriteConsoleOutputCharacter(outHandle, W->buffer, W->buffer_size, {0,0}, &dwBytesWritten);
}

/// # Window Clear Buffer
///
/// This will clear the window buffer.
void window_clear_buffer(window *W) {
  // W->buffer[0] = '\0';
}

// This worker get the input from the user and puts it in input_buffer
void DoWork() {

  DWORD filesize = 0;
  DWORD nRead;
  char buffer[127];
  while (!did_work) {
    ReadFile(inHandle, buffer, 127, &nRead, NULL);
    for (int i = 0; i < nRead; i++) {
      input_buffer[input_index] = buffer[i];
      input_index ++;
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
  outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
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
  input_event_start();
}

/// # Update Window Events 
///
/// This updates all of the console events.
void update_window_events(window *W) {

  CONSOLE_SCREEN_BUFFER_INFO cbiInfo;
  GetConsoleScreenBufferInfo(outHandle, &cbiInfo);


  if (W->size.X != cbiInfo.dwSize.X || W->size.Y != cbiInfo.dwSize.Y) {
    set_window_size(W, (int)cbiInfo.dwSize.X, (int)cbiInfo.dwSize.Y);
  }

  if(input_index > 0) {
      for(int i = 0; i < sizeof(input_buffer)/sizeof(input_buffer[0]); i++){
        input[i] = input_buffer[i];
      }
      input_index = 0;
  }else {
      for(int i = 0; i < sizeof(input)/sizeof(input[0]); i++){
        input[i] = '\0';
      }
      
  }
}
#endif
