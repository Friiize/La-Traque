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

pisteur* initPisteur(char screen[][W], pisteur* pisteurs, const int H, const int W) {
	int input = -1;
	int x = -1;
	int y = -1;

	do {
		system("cls");
		drawScreen(screen, H, W);
		printf("Combien de pisteur ? (entre 3 et 10)\n");
		scanf("%d", &input);
	} while (input < 3 || input > 10);

	pisteurs = (pisteur*)calloc(input, sizeof(pisteur));

	for (int i = 0; i < input; i++) {
		do {
			system("cls");
			drawScreen(screen, H, W);
			printf("Position du pisteur %d\nX : ", i);
			scanf("%d", &x);
			printf("Y : ");
			scanf("%d", &y);

			for (int j = 0; j < i; j++) {
				printf("Ca passe");
				if ((&pisteurs[j].x == &x) && (&pisteurs[j].y == &y)) {
					system("cls");
					drawScreen(screen, H, W);
					printf("Un pisteur est déjà placé ici. (X : %d, Y : %d)", x, y);
					j = input;//On forces la fin de la boucle
				}//Message d'erreur si le joueur place un pisteur sur un autre pisteur
			}//Boucle autant de fois que de positions attribués
		} while ((x == 0 || x == H - 1) || (y == 0 || y == W - 1) && ((&pisteurs[i].x == &x) && (&pisteurs[i].y == &y)));

		screen[y][x] = 'P';
	}//On demande au joueur les positions de ces pisteurs

	return pisteurs;
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

	pisteurs = initPisteur(screen, pisteurs, H, W);//Initialise le nombre de pisteur

	while (quit) {
		system("cls");
		drawScreen(screen, H, W);
		system("pause"); //Temporaire
	}
}
