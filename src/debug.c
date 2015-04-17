#include <pebble.h>
#include "debug.h"

void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  APP_LOG(APP_LOG_LEVEL_INFO, "Heartbeat");
}