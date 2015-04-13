#include <pebble.h>
#include "main.h"

//// MAIN SCREEN /////
static Window *s_main_window;      // Main window handle
static MenuLayer *s_main_menu;     // Menu for main window

static void main_window_load(Window *window) {
 
}

static void main_window_unload(Window *window) {
  
}

// Initialization
static void handle_init(void) {
  // Create main window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

// Deinitilization
static void handle_deinit(void) {
  // Destroy main window
  window_destroy(s_main_window);
}

// Entry point
int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}