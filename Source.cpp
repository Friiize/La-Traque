#include "Header.h"

const int W = 31;
const int H = 16;

void drawScreen(char screen[][W], const int H, const int W) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c ", screen[i][j]);
		}
		printf("\n");
	}
}

void main() {
	char screen[H][W] = { NULL };
	int quit = 0;
	pisteur* pisteurs = { NULL };
	eventHandler();

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == 0 || i == H-1 || j == 0 || j == W-1) {
				screen[i][j] = '*';
			}
			else { 
				screen[i][j] = ' '; 
			}

		}
	}

	drawScreen(screen, H, W);
	printf("Bienvenue dans La Traque !\n\n\n");

	system("pause");

	while (quit) {

	}
}
