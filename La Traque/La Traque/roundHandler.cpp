#include "Header.h"

void deplacementHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur){

}

void pisteurActionHandler(pisteur* pisteurs, monstre* monstres, char cases[][W]) {
	drawScreen(cases);
}

void rapport(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nb) {
	int count = 0;

	for (int i = 0; i < 8; i++) {
		switch (i) {
		case 0:
			if (pisteurs[nb].x - 1 == monstres[0].x && pisteurs[nb].y - 1 == monstres[0].y) {
				printf("Je le vois.\n\n");
				system("pause");//Temporaire

				//pisteurActionHandler(pisteurs, monstres, cases);
			}
			else if (freshCases[pisteurs[nb].y - 1][pisteurs[nb].x - 1] != 0) {
				printf("Trace fraiche en X : %d, Y : %d", pisteurs[nb].x - 1, pisteurs[nb].y - 1);
				pisteurs[nb].detectedArea[count][0] = pisteurs[nb].y - 1;
				pisteurs[nb].detectedArea[count][1] = pisteurs[nb].x - 1;
				count++;
				system("pause");//Temporaire
			}
			break;
		}
	}

	if (pisteurs[nb].detectedArea == NULL) {
		printf("Rien autour de moi.");
		system("pause");//Temporaire
	}
	else {
		printf(" ");

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
				rapport(pisteurs, monstres, cases, freshCases, i);
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
	deplacementHandler(pisteurs, monstres, cases, freshCases, nbPisteur);
}
