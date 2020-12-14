#include "Header.h"

void rapport(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W]) {
	for (int i = 0; j < 8; j++) {
		switch (j) {
		case 1:
			int x = pisteurs[i].x--;
			int y = pisteurs[i].y--;
			if (x == monstres[0].x && y == monstres[0].y) {
				printf("Le monstre est en ");
			}
			break;
		}
	}
}

void pisteurStatus(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur) {
	for (int i = 0; i < nbPisteur; i++) {
		if (pisteurs[i].isDead != 0) {
			cases[pisteurs[i].y][pisteurs[i].x] = '!';
			drawScreen(cases);
			if (pisteurs[i].x == monstres[0].x && pisteurs[i].y == monstres[0].y) {
				printf("Le monstre viens de tuer le pisteur %d en (%d, %d)", i+1, monstres[0].x, pisteurs[i].y);
				cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			}
			else if (pisteurs[i].x != monstres[0].x && pisteurs[i].y != monstres[0].y) {
				printf("Rapport du pisteur %d en cours...", i + 1);
				rapport(pisteurs, monstres, cases, freshCases);
			}
		}
	}
}

void roundHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (freshCases[i][j] != 0) {
				freshCases[i][j]--;
			}
		}
	}

	pisteurStatus(pisteurs, monstres, cases, freshCases, nbPisteur);
}
