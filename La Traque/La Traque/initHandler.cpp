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

void drawScreen(char cases[][W]) {
	system("cls");
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c ", cases[i][j]);
		}
		printf("\n");
	}
}

void firstScreen(char cases[][W]) {
	drawScreen(cases);
	printf("Bienvenue dans La Traque !\n\n\n");
	
	system("pause");

	drawScreen(cases);
	printf("Les pisteurs ont une detection de 8 cases tout autour d'eux\n");
	printf("allant de 1 a 9.\n");
	system("pause");

	drawScreen(cases);
	printf("Gardez bien en tetes les données que le jeu vous donnera.\n");
	printf("C'est un jeu de mémoire, jouez avec le moins de pisteur pour le rendre plus dur.\n");
	system("pause");
}