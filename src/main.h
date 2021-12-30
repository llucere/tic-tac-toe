#pragma once
#include <stdint.h>

// the current turn (1 = x, 2 = o)
uint8_t turn = 1;

// the tic tac toe board
uint8_t board[3][3];

// get the symbol for the passed board id
uint8_t sym(uint8_t id);

// draw the current tic tac toe board
void draw(void);

// get and set the next move on the board
void next_move(void);

// get the column the user wants to place their symbol at
void get_column();

// get the row the user wants to place their symbol at
void get_row();