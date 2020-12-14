#include "Header.h"

void initScreen(char screen[][W]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == 0 || i == H - 1 || j == 0 || j == W - 1) {
				screen[i][j] = '*';
			}
			else {
				screen[i][j] = ' ';
			}
		}
	}
}

void drawScreen(char screen[][W], int H, int W) {
	system("cls");
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c ", screen[i][j]);
		}
		printf("\n");
	}
}

void firstScreen(char screen[][W]) {
	drawScreen(screen, H, W);
	printf("Bienvenue dans La Traque !\n\n\n");
	system("pause");
}