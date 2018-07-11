#include "queen.h"
#include "broad.h"
#include <iostream>

void place(char* broad, const int & col_num);
bool can_place(char** broad, const int & row_num, const int & col_num, const int & n);
bool rowQueen(char** broad, const int & row_num, const int & n);
bool colQueen(char** broad, const int & col_num, const int & n);
bool diagonalQueen(char** broad, const int & row_num, const int & col_num, const int &n);
bool leftDiagonalQueen(char** broad, const int & row_num, const int & col_num, const int & n);
bool rightDiagonalQueen(char** broad, const int & row_num, const int & col_num, const int & n);

void find_n_queen(char** broad, const int & n, const int & row_num) {
	for(int col_num = 0; col_num < n; ++col_num) {
		if( can_place(broad, row_num, col_num, n) ) {
			broad[row_num][col_num] = 'Q';
			if(row_num == n - 1) {
				broadOutput(broad, n, n);
                std::cout << std::endl;
			} else {
				find_n_queen(broad, n, row_num + 1);
			}
            broad[row_num][col_num] = '*';
		}
	}
}

void place(char* broad, const int & col_num) {
	for(int i = 0; i < col_num; ++i) {
		broad[i] = '*';
	}
	broad[col_num] = 'Q';
}

bool can_place(char** broad, const int & row_num, const int & col_num, const int & n) {
	return rowQueen(broad, row_num, n) && colQueen(broad, col_num, n) && diagonalQueen(broad, row_num, col_num, n); 
}

bool rowQueen(char** broad, const int & row_num, const int & n) {
	for(int i = 0; i < n; ++i) {
		if(broad[row_num][i] == 'Q')
			return false;
	}
	return true;
}

bool colQueen(char** broad, const int & col_num, const int & n) {
	for(int i = 0; i < n; ++i) {
		if(broad[i][col_num] == 'Q')
			return false;
	}
	return true;
}

bool diagonalQueen(char** broad, const int & row_num, const int & col_num, const int & n) {
	return leftDiagonalQueen(broad, row_num, col_num, n) && rightDiagonalQueen(broad, row_num, col_num, n);
}

bool leftDiagonalQueen(char** broad, const int & row_num, const int & col_num, const int & n) {
	for(int i = 1, j = 1; (i + row_num < n && j + col_num < n); ++i, ++j) {
		if(broad[i + row_num][j + col_num] == 'Q')
			return false;
	}
	
	for(int i = -1, j = -1; (i + row_num >= 0 && j + col_num >= 0); --i, --j) {
		if(broad[i + row_num][j + col_num] == 'Q')
			return false;
	}
	return true;
}

bool rightDiagonalQueen(char** broad, const int & row_num, const int & col_num, const int & n) {
	for(int i = 1, j = -1; (i + row_num < n && j + col_num >= 0); ++i, --j) {
		if(broad[i + row_num][j + col_num] == 'Q')
			return false;
	}
	
	for(int i = -1, j = 1; (i + row_num >= 0 && j + col_num < n); --i, ++j) {
		if(broad[i + row_num][j + col_num] == 'Q')
			return false;
	}
	return true;
}





