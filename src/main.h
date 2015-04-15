#pragma once
  
typedef struct {
  char symbol[5];      // 4 character symbol
  char price[20];      // Price ($1234.56 +999.99%)
} stock;

stock* stocks_list[7];  // Permit up to seven stocks to be tracked
int stocks_count = 0;

// Flag to make sure javascript is ready
bool JS_ready = false;

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

//// UTILITY ////
// Communication
static void inbox_received_callback(DictionaryIterator *iterator, void *context);
static void inbox_dropped_callback(AppMessageResult reason, void *context);
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
static void outbox_sent_callback(DictionaryIterator *iterator, void *context);
static void send_phone_command(int command);

//// APP CORE ////
static void handle_init(void);
static void handle_deinit(void);
int main(void);