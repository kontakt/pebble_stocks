#include <pebble.h>
#include "main.h"

// Initialization
static void handle_init(void) {

}

// Deinitilization
static void handle_deinit(void) {
  
}

// Entry point
int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}