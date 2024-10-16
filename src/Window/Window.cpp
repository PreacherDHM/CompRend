#include "Window.h"

#include "windows.h"
#include <conio.h>
#include <stdio.h>
#include <thread>
#include <winuser.h>

HANDLE outHandle;
HANDLE inHandle;

void set_window_size(window *W, int x, int y) {
  W->size.X = x;
  W->size.Y = y;
}

void set_window_state(window *W, window_state state) { W->state = state; }
void set_window_input_mode(window *W, window_input_mode input_mode) {
  W->input_mode = input_mode;
}
void set_window_name(window *W, const char *window_name) {
  W->name = window_name;
}
void set_window_buffer(window *W, const char *buffer) { W->buffer = buffer; }

window_size get_window_size(window *W) { return W->size; }
window_input_mode get_window_input_mode(window *W) { return W->input_mode; }
window_state get_window_state(window *W) { return W->state; }
const char *get_window_input(window *W) { return W->name; }

void window_draw(window *W) {
  WriteFile(outHandle, W->buffer, W->buffer_size, NULL, NULL);

  SetConsoleCursorPosition(outHandle, {0, 0});
}

void window_clear_buffer(window *W) {
  // W->buffer[0] = '\0';
}

static bool did_work = false;
std::thread worker;
static char input_buffer[127];
static int input_index;
void DoWork() {

	DWORD filesize = 0;
	DWORD nRead;
	char buffer[127];
  while (!did_work) {
		ReadFile(inHandle, buffer, 127, &nRead, NULL);
		input_buffer[input_index] = buffer[0];
        input_index++;


  }

  //printf("\nread = %c", ch);
  //SetConsoleCursorPosition(outHandle, {0, 0});
}
void input_event_start() { 
	worker = std::thread(DoWork); 
	//worker.joinable();
//	 
}

void window_close() {}

void window_init(window *W) {
  outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  inHandle = GetStdHandle(STD_INPUT_HANDLE);
  
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

void update_window_events(window *W) {
  
  CONSOLE_SCREEN_BUFFER_INFO cbiInfo;

  GetConsoleScreenBufferInfo(outHandle, &cbiInfo);
  SetConsoleTitleA("testin");

  if (W->size.X != cbiInfo.dwSize.X || W->size.Y != cbiInfo.dwSize.Y) {
    set_window_size(W, (int)cbiInfo.dwSize.X, (int)cbiInfo.dwSize.Y);
  }


  SetConsoleCursorPosition(outHandle, {0, 0});
  printf("size of window %d,%d", W->size.X, W->size.Y);
  printf("\n\n\n%d input = %s", input_index, input_buffer);
  input_index = 0;
}
