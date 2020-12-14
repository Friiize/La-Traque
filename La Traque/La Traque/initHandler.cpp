#include "Header.h"

void initScreen(char cases[][W], int freshCases[][W]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == 0 || i == H - 1 || j == 0 || j == W - 1) {
				cases[i][j] = '*';
			}
			else {
				cases[i][j] = ' ';
			}
			freshCases[i][j] = 0;
		}
	}
}

void drawScreen(char cases[][W], int H, int W) {
	system("cls");
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c ", cases[i][j]);
		}
		printf("\n");
	}
}

void firstScreen(char cases[][W]) {
	drawScreen(cases, H, W);
	printf("Bienvenue dans La Traque !\n\n\n");
	system("pause");
}