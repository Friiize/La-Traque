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

pisteur* initPisteur(char screen[][W], const int H, const int W) {
	int input = -1;

	do {
		system("cls");
		drawScreen(screen, H, W);
		printf("Combien de pisteur ? (entre 3 et 10)\n");
		scanf("%d", &input);
	} while (input < 3 || input > 10);

	return (pisteur*)calloc(input, sizeof(pisteur));
}

void posPisteur(pisteur* pisteurs) {

}

void main() {
	char screen[H][W] = { NULL };
	int quit = 1;
	pisteur* pisteurs = { NULL };

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i == 0 || i == H-1 || j == 0 || j == W-1) {
				screen[i][j] = '*';
			}
			else { 
				screen[i][j] = ' '; 
			}
		}
	}//Initialise le tableau

	drawScreen(screen, H, W);
	printf("Bienvenue dans La Traque !\n\n\n");

	system("pause");
	system("cls");

	pisteurs = initPisteur(screen, H, W);//Initialise le nombre de pisteur
	posPisteur(pisteurs);

	while (quit) {
		system("cls");
		drawScreen(screen, H, W);
		system("pause"); //Temporaire
	}
}
