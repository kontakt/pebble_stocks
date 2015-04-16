#include <pebble.h>
#include "common.h"
#include "main_screen.h"
#include "main.h"

static void data_init(){
  for(int i=0; i < NUMBER_OF_STOCKS; i++){
    send_phone_command(2,i);
  }
}

// Initialization
static void handle_init(void) {
  // Create main window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = s_main_window_load,
    .unload = s_main_window_unload,
  });
  window_stack_push(s_main_window, true);

  // Register communication callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  // Open messenger
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  data_init();
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
