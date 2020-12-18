#include "Header.h"

int winLoseHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int input) {
	int option = 0;

	for (int i = 0; i < input; i++) {
		option = 0;
		if (pisteurs[i].isDead == 1) {
			option = 1;
		}
	}//check si tout les pisteurs sont mort, si oui, Game Over.

	
	if (option == 1) {
		cases[monstres[0].y][monstres[0].x] = 'M';
		drawScreen(cases);
		printf("Tout vaut pisteurs ont ete tues.\n");
		printf("Le monstre a gagné, une autre fois...Peut-etre.\n");
		system("pause");
	}
	else if (monstres[0].hp == 0) {
		drawScreen(cases);
		printf("Vous avez gagne ! Felicitation !\n\n");
		system("pause");
		option = 1;
	}

	return option;
}
