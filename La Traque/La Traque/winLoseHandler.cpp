#include "Header.h"

void winLoseHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W]) {
	for (int i = 0; i < input; i++) {
		quit = 0;
		if (pisteurs[i].isDead == 0) {
			quit = 1;
		}
	}//check si tout les pisteurs sont mort, si oui, le jeu s'arrêtes
}
