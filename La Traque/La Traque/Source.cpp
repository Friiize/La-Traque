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

pisteur* nbPisteur(char screen[][W], pisteur* pisteurs, const int H, const int W) {
	int input = -1;

	do {
		system("cls");
		drawScreen(screen, H, W);
		printf("Combien de pisteur ? (entre 3 et 10)\n");
		scanf("%d", &input);
	} while (input < 3 || input > 10);

	return (pisteur*)realloc(pisteurs, input * sizeof(pisteur));
}

void posPisteur(pisteur* pisteurs, char screen[][W], int W, int H) {
	int x = -1;
	int y = -1;

	for (int i = 0; i < sizeof(pisteurs); i++) {
		do {
			system("cls");
			drawScreen(screen, H, W);
			printf("Position du pisteur %d\nX : ", i+1);
			scanf("%d", &x);
			printf("Y : ");
			scanf("%d", &y);

			for (int j = 0; j < i; j++) {
				if ((pisteurs[j].x == x) && (pisteurs[j].y == y)) {
					system("cls");
					drawScreen(screen, H, W);
					printf("Un pisteur est deja place ici. (X : %d, Y : %d)\n\n", x, y);
					system("pause");
					j = i;//On forces la fin de la boucle
					i--;//On prévoit qu'il boucle +1 pour qu'il retourne sur le pisteur qui est mal placé
				}//Message d'erreur si le joueur place un pisteur sur un autre pisteur

			}//Boucle autant de fois que de positions attribués

		} while ((x <= 0 || x >= H - 1) || (y <= 0 || y >= W - 1) && ((pisteurs[i].x == x) && (pisteurs[i].y == y)));

		pisteurs[i].x = x;
		pisteurs[i].y = y;
		screen[y][x] = 'P';

	}//On demande au joueur les positions de ces pisteurs
}

void main() {
	char screen[H][W] = { NULL };
	int quit = 1;
	pisteur* pisteurs = (pisteur*)calloc(1, sizeof(pisteur));

	//Initialise le tableau
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

	//Premire affichage du jeu
	drawScreen(screen, H, W);
	printf("Bienvenue dans La Traque !\n\n\n");
	system("pause");
	system("cls");

	pisteurs = nbPisteur(screen, pisteurs, H, W); //Initialise le nombre de pisteur
	posPisteur(pisteurs, screen, W, H); //Gére l'emplacement des pisteurs

	while (quit) {
		system("cls");
		drawScreen(screen, H, W);
		system("pause"); //Temporaire

		for (int i = 0; i < sizeof(pisteurs); i++) {
			quit = 0;
			if (pisteurs[i].isDead == 0) {
				quit = 1;
			}
		}//check si tout les pisteurs sont mort, si oui, le jeu s'arrêtes
	}
}
