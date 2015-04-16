#pragma once

typedef struct {
  char symbol[5];      // 4 character symbol
  char price[20];      // Price ($1234.56 +999.99%)
} stock;

stock* stocks_list[7];  // Permit up to seven stocks to be tracked
int stocks_count = 0;

#define NUMBER_OF_STOCKS 4
