#pragma once

//// MAIN SCREEN /////
static Window *s_main_window;      // Main window handle
static MenuLayer *s_main_menu;     // Menu for main window

static void s_main_window_load(Window *window);    // Init
static void s_main_window_unload(Window *window);  // Deinit
// Menu handlers
static uint16_t s_menu_get_num_sections_callback(MenuLayer *menu_layer, void *data);
static uint16_t s_menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data);
static int16_t s_menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data);
static void s_menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data);
static void s_menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data);
static void s_menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data);