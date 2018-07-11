#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "broad.h"

using std::cout;
using std::endl;

char** broadCreation(const int row, const int col) {
	char **broad = (char**)malloc(row * sizeof(char*));
	for(int i = 0; i < row; ++i) {
		broad[i] = (char*)malloc(col * sizeof(char));
	}
	for(int i = 0; i < row; ++i) {
		for(int j = 0; j < col; ++j) {
			broad[i][j] = '*';
		}
	}
	return broad;
}

void broadOutput(char *broad[], const int row, const int col) {
	for(int i = 0; i < row; ++i) {
		printf("%d ", row - (i + 1));
		for(int j = 0; j < col; ++j) {
			printf("%c ", broad[row - i - 1][j]);
		}
		printf("\n");
	}
	printf("  ");
	for(int i = 0; i < col; ++i)
		printf("%d ", i);
	printf("\n");
}

void freebroad(char*** ptBroad, const int row) {
	for(int i = 0; i < row; ++i) {
		free( (*ptBroad)[i] );
	}
	free(*ptBroad);
	*ptBroad = NULL;
}

