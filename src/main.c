#include <pebble.h>
#include "main.h"

// Runs when the window first loads
static void s_main_window_load(Window *window) {
  // Now we prepare to initialize the menu layer
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  s_main_menu = menu_layer_create(bounds);
  menu_layer_set_callbacks(s_main_menu, NULL, (MenuLayerCallbacks){
    .get_num_sections = s_menu_get_num_sections_callback,
    .get_num_rows = s_menu_get_num_rows_callback,
    .get_header_height = s_menu_get_header_height_callback,
    .draw_header = s_menu_draw_header_callback,
    .draw_row = s_menu_draw_row_callback,
    .select_click = s_menu_select_callback,
  });
}

// Runs when the window is destroyed
static void s_main_window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(s_main_menu);
}

// Only one section
static uint16_t s_menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return 1;
}

// Return the number of rows in the section
static uint16_t s_menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return stocks_count;
}

// Confirm that the cells will be standard height
static int16_t s_menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Handle drawing the header text
static void s_menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  menu_cell_basic_header_draw(ctx, cell_layer, "Your Stocks");
}

// Handle drawing for each layer
static void s_menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  menu_cell_basic_draw(ctx, cell_layer,
                       stocks_list[cell_index->row]->symbol,
                       stocks_list[cell_index->row]->price,
                       NULL);
}

// Handles the select button on a menu item
static void s_menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  
}

// Communications
static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Get the first pair
  Tuple *t = dict_read_first(iterator);
  // Temp value for recieved stock
  stock* temp;
  temp = malloc(sizeof(stock));
  // Received index for stock
  int index = -1;
   
  // Process all pairs present
  while(t != NULL) {
    // Determine the pair we have
    switch (t->key) {
      case 0:
      index = (int)t->value->int8;
      break;
      case 1:
      strncpy(temp->symbol, t->value->cstring, 4);
      break;
      case 2:
      strncpy(temp->price, t->value->cstring, 20);
      break;
    }

    // Get next pair, if any
    t = dict_read_next(iterator);
  }
  // Check if the stock at index exists. If not, create it.
  if(index != -1 && stocks_list[index] == NULL) {
    APP_LOG(APP_LOG_LEVEL_INFO, "New stock created");
    stocks_list[index] = temp;  // Store pointer to struct in the list
    stocks_count++;             // Increment number of stocks
    menu_layer_reload_data(s_main_menu);  // Tell the main menu it has something new
    APP_LOG(APP_LOG_LEVEL_INFO, stocks_list[index]->symbol);
    APP_LOG(APP_LOG_LEVEL_INFO, stocks_list[index]->price);
  }
  else
    free(temp);
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
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