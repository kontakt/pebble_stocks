#include <pebble.h>
#include "common.h"
#include "main_screen.h"
#include "comms.h"

bool JS_ready = false;

// Communications
void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Packet recieved");

  // Get the first pair
  Tuple *t = dict_read_first(iterator);

  // Temp value for recieved stock
  stock* temp;
  temp = malloc(sizeof(stock));

  // Received index for stock
  int index = -1;
  
  // Process all keypairs present
  while(t != NULL) {
    // Determine the keypair
    switch ((int)t->key) {
      case 0:
        JS_ready = true;            // Flag as ready
        send_phone_command(2, 0);   // Tell the app to execute command 1, 0
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        index = (int)t->value->int8;
        break;
      case 4:
        strncpy(temp->symbol, t->value->cstring, 4);
        break;
      case 5:
        strncpy(temp->price, t->value->cstring, 20);
        break;
      default:
        APP_LOG(APP_LOG_LEVEL_WARNING, "Case not handled");
        break;
    }

    // Get next keypair, if any
    t = dict_read_next(iterator);
  }
  
  // Check if the stock at index exists. If not, create it.
  if(index != -1 && stocks_list[index] == NULL) {
    APP_LOG(APP_LOG_LEVEL_INFO, "New stock created");
    stocks_list[index] = temp;  // Store pointer to struct in the list
    stocks_count++;             // Increment number of stocks
    menu_layer_reload_data(s_main_menu);  // Tell the main menu it has something new
  }
  else {
    free(temp);
  }
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

int retries;
void send_phone_command(int command, int detail){
  // Prepare dictionary
  DictionaryIterator *iterator;
  app_message_outbox_begin(&iterator);

  // Write data
  dict_write_int(iterator, 1, &command, sizeof(int), true /* signed */);
  dict_write_int(iterator, 2, &detail, sizeof(int), true /* signed */);

  // Send the data
  if(app_message_outbox_send() != APP_MSG_OK && retries < 3){
    APP_LOG(APP_LOG_LEVEL_WARNING, "Message unsuccessful, retrying");
    retries++;
    send_phone_command(command, detail);
  }
  else if(app_message_outbox_send() != APP_MSG_OK && retries >= 3){
    APP_LOG(APP_LOG_LEVEL_WARNING, "Message FAILED");
  }
  retries = 0;
}
