#pragma once

typedef struct {
  char symbol[5];      // 4 character symbol
  char price[20];      // Price ($1234.56 +999.99%)
} stock;

extern stock* stocks_list[7];  // Permit up to seven stocks to be tracked
extern int stocks_count;

#define NUMBER_OF_STOCKS 4
