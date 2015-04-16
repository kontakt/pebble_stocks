#pragma once

// Flag to make sure javascript is ready
bool JS_ready = false;

//// UTILITY ////
// Data handling
static void data_init();

//// APP CORE ////
static void handle_init(void);
static void handle_deinit(void);
int main(void);
