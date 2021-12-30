#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"


#if defined(_WIN32)
	#include <windows.h>

	void sleep_cross(int s) {Sleep(s*1000);}
	void cls() {system("cls");}
#else
	#if defined(__linux__) || defined(__unix__)
		void sleep_cross(int s) {sleep(s);}
		void cls() {system("clear");}
	#endif
#endif

char column, column_int;
char row, row_int;

int main(int argc, char* argv[]) {
	for (int i = 0; i < 9; i++) {
		draw();
		next_move();
		turn = turn == 1 ? 2 : 1;
	}

	puts("it's a draw lol. better luck next time");
	sleep_cross(5);

	return 0;
}

uint8_t sym(uint8_t id) {
	switch(id) {
		case (0):
			return ' ';
		case (1):
			return 'x';
		case (2):
			return 'o';
		default:
			return '?';
	}
}

void draw() {
	cls();

	printf("|-----------|\n");
	printf("| %c | %c | %c |\n", sym(board[0][0]), sym(board[0][1]), sym(board[0][2]));
	printf("| %c | %c | %c |\n", sym(board[1][0]), sym(board[1][1]), sym(board[1][2]));
	printf("| %c | %c | %c |\n", sym(board[2][0]), sym(board[2][1]), sym(board[2][2]));
	printf("|-----------|\n");
	puts("");
}

bool check_winner() {
	// i cheated a little bit, looked at some of the logic from https://geekflare.com/tic-tac-toe-python-code/
	// but hey, its a learning experience
		
	for (int i = 0; i < 3; i++) {
		bool win = true;
		for (int j = 0; j < 3; j++) if (board[i][j] != turn) {win = false; break;}
		if (win) return win;
	}

	for (int i = 0; i < 3; i++) {
		bool win = true;
		for (int j = 0; j < 3; j++) if (board[j][i] != turn) {win = false; break;}
		if (win) return win;
	}

	bool win = true;
	for (int i = 0; i < 3; i++) {
		if (board[i][i] != turn) {win = false; break;}
	}
	if (win) return win;

	win = true;
	for (int i = 0; i < 3; i++) {
		if (board[i][3 - 1 - i] != turn) {win = false; break;}
	}
	
	return win;
}

void get_column() {
	printf("'%c' to move! type the column you want to use\n", turn == 1 ? 'X' : 'O');
	fflush(stdin);

	column = fgetc(stdin);
	column_int = column - '0' - 1;

	if (column != '1' && column != '2' && column != '3') {
		draw();
		printf("issue! column is not an integer value between 1 and 3.\n");
		return get_column();
	}

	uint8_t filled = 0;
	for (uint8_t i = 0; i < 3; i++) if (board[column_int][i] != 0) filled++;
	if (filled == 3) {
		draw();
		printf("issue! column %c is already filled.\n", column);
		return get_column();
	}
	printf("success! your column has been set.\n");
}

void get_row() {
	printf("'%c' to move! now, type the row you want to use. type 'r' to restart this prompt\n", turn == 1 ? 'X' : 'O');
	fflush(stdin);

	row = fgetc(stdin);
	row_int = row - '0' - 1;

	if (row == 'r' || row == 'R') {
		draw();
		printf("promt successfully reset.\n");
		get_column();
		return get_row();
	}

	if (row != '1' && row != '2' && row != '3') {
		draw();
		printf("issue! row is not an integer value between 1 and 3.\n");
		return get_row();
	}

	if (board[column_int][row_int] != 0) {
		draw();
		printf("issue! the row is already filled.\n");
		return get_row();
	}

	printf("success! your row has been set.\n");
}

void next_move() {
	get_column();
	get_row();
	
	board[column_int][row_int] = turn;
	if (check_winner()) {
		draw();
		printf("'%c' has won this game of tic-tac-toe! congratulations!!!!\n", turn == 1 ? 'X' : 'O');
		puts("this prompt will automatically close in 5 seconds!");

		sleep_cross(5);

		exit(0);
		return;
	}
}