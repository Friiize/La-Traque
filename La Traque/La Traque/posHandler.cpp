#include "Header.h"

void posPisteur(pisteur* pisteurs, char cases[][W], int input) {
	int x = -1;
	int y = -1;
	int isPlaced = 0;

	for (int i = 0; i < input; i++) {
		do {
			drawScreen(cases);
			printf("Position du pisteur %d\nX (MAX %d) : ", i+1, W - 2);
			scanf("%d", &x);
			printf("Y (MAX %d) : ", H - 2);
			scanf("%d", &y);

			for (int j = 0; j < i; j++) {
				isPlaced = 1;
				if ((pisteurs[j].x == x) && (pisteurs[j].y == y)) {
					drawScreen(cases);
					printf("Un pisteur est deja place ici. (X : %d, Y : %d)\n\n", x, y);
					system("pause");
					j = i;//On forces la fin de la boucle
					i--;//On prévoit qu'il boucle +1 pour qu'il retourne sur le pisteur qui est mal placé
					isPlaced = 0;
				}//Message d'erreur si le joueur place un pisteur sur un autre pisteur

			}//Boucle autant de fois que de positions attribués

		} while ((x < 1 || x > 29) || (y < 1 || y > 14) && isPlaced == 0);

		//Attribue les valeurs une fois la pos validé
		pisteurs[i].x = x;
		pisteurs[i].y = y;
		cases[y][x] = 'P';

	}//On demande au joueur les positions de ces pisteurs
}

void initMonstre(monstre* monstres, pisteur* pisteurs, char cases[][W], int freshCases[][W], int input) {
	int isPlaced = 0;
	do {//Tant que le monstre est incorrectement placé
		monstres[0].x = rand() % W - 1;
		monstres[0].y = rand() % H - 1;

		for (int i = 0; i < input; i++) {
			isPlaced = 1;
			if ((monstres[0].x == pisteurs[i].x) && (monstres[0].y == pisteurs[i].y)) {
				isPlaced = 0;
				i = input;
			}
		} //Vérification que la pos du monstre soit différente de la pos des pisteurs

	} while ((monstres[0].x < 1 || monstres[0].x > 29) || (monstres[0].y < 1 || monstres[0].y > 14) && isPlaced == 0);

	//Attribue les valeurs une fois la pos validé
	cases[monstres[0].y][monstres[0].x] = 'M';
	freshCases[monstres[0].y][monstres[0].x] = 16;
}

void posHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int input) {
	posPisteur(pisteurs, cases, input); //Gére l'emplacement des pisteurs
	initMonstre(monstres, pisteurs, cases, freshCases, input);//Gére l'emplacement du monstre
}