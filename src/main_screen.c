#include <pebble.h>
#include "common.h"
#include "main_screen.h"
#include "comms.h"

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

  layer_add_child(window_layer, menu_layer_get_layer(s_main_menu));
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
