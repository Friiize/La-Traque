#include "Header.h"


void pisteurActionHandler(pisteur* pisteurs, monstre* monstres, char cases[][W]) {
	drawScreen(cases);
}

void rapport(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nb) {
	int count = 0;

	for (int i = 0; i < 8; i++) {
		switch (i) {
		case 1:
			int x = pisteurs[nb].x--;
			int y = pisteurs[nb].y--;
			if (x == monstres[0].x && y == monstres[0].y) {
				printf("Je le vois.\n\n");
				pisteurActionHandler(pisteurs, monstres, cases);
			}
			else if (freshCases[y][x] != 0) {
				printf("Trace fraiche en X : %d, Y : %d", x, y);
				pisteurs[nb].detectArea[count][0] = y;
				pisteurs[nb].detectArea[count][1] = x;
				count++;
			}
			break;
		}
	}

	if (pisteurs[nb].detectArea != NULL) {

	}
	else {
		printf("Rien autour de moi.");
	}
}

void pisteurStatus(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur) {
	for (int i = 0; i < nbPisteur; i++) {
		if (pisteurs[i].isDead == 0) {
			cases[pisteurs[i].y][pisteurs[i].x] = '!';
			drawScreen(cases);
			if (pisteurs[i].x == monstres[0].x && pisteurs[i].y == monstres[0].y) {
				printf("Le monstre viens de tuer le pisteur %d en (%d, %d)", i+1, monstres[0].x, monstres[i].y);
				cases[pisteurs[i].y][pisteurs[i].x] = ' ';
				system("pause");//Temporaire

			}
			else if (pisteurs[i].x != monstres[0].x && pisteurs[i].y != monstres[0].y) {
				printf("Rapport du pisteur %d en cours...", i + 1);
				system("pause");//Temporaire

				//rapport(pisteurs, monstres, cases, freshCases, i);
			}
		}
		else if (pisteurs[i].isDead == 1) {
			drawScreen(cases);
			printf("Le pisteur %d est mort en (%d, %d)", i + 1, pisteurs[i].x, pisteurs[i].y);
			system("pause");//Temporaire

		}
	}
}

void roundHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (freshCases[i][j] != 0) {
				freshCases[i][j]--;
			}//Gére l'usure des empreintes
		}
	}

	pisteurStatus(pisteurs, monstres, cases, freshCases, nbPisteur);
}
