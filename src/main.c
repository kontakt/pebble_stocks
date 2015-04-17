#include <pebble.h>
#include "common.h"
#include "main_screen.h"
#include "comms.h"
#include "debug.h"
#include "main.h"

// Initialization
void handle_init(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "App Launched");
  
  // Notify which platform is running
  #ifdef PBL_PLATFORM_BASALT
    APP_LOG(APP_LOG_LEVEL_INFO, "Basalt hardware");
  #else
    APP_LOG(APP_LOG_LEVEL_INFO, "Aplite hardware");
  #endif
    
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
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}

// Deinitilization
void handle_deinit(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "App exited");
  // Destroy main window
  window_destroy(s_main_window);
}

// Entry point
int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
