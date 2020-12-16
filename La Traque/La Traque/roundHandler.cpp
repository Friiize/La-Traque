#include "Header.h"

void deplacementHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur){

}

void pisteurActionHandler(pisteur* pisteurs, monstre* monstres, char cases[][W]) {
	char c = getchar();
	drawScreen(cases);
	printf("Vous pouvez tirer avec la touche T.\n");
	printf("Ou sur la touche R pour ne rien faire.\n");

	switch (c) {
	case 'T':
		int luck = rand() % 10;
		drawScreen(cases);
		printf("Vous préparez le tire et...");
		Sleep(1000);
		if (luck <= 4) {
			monstres[0].hp = monstres[0].hp-1;
			printf("Vous l'avez touché ! Encore %d coup", monstres[0].hp);
		}
		else {
			printf("Manquez...Sauvez-vous vite !");
		}
		break;
	case 'R':
		break;
	}
}

void casesHandler(pisteur* pisteurs, monstre* monstres,char cases[][W], int freshCases[][W], int x, int y, int* count, int i, int nb) {
	x = pisteurs[nb].x + x;
	y = pisteurs[nb].y + y;

	if (x == monstres[0].x && y == monstres[0].y) {
		printf("Je le vois.\n\n");
		system("pause");

		pisteurActionHandler(pisteurs, monstres, cases);
	}
	else if (freshCases[y][x] != 0) {
		printf("Trace fraiche valant %d en X : %d, Y : %d\n\n", freshCases[y][x], x, y);
		pisteurs[nb].detectedArea[i].y = y;
		pisteurs[nb].detectedArea[i].x = x;
		pisteurs[nb].detectedArea[i].fresh = freshCases[y][x];
		*count = 1;
		system("pause");//Temporaire
	}
}

void rapport(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nb) {
	int count = 0;

	for (int i = 0; i < 8; i++) {
		switch (i) {
		case 0:
			casesHandler(pisteurs, monstres, cases, freshCases, -1, -1, &count, i, nb);//Case haut gauche
			break;
		case 1:
			casesHandler(pisteurs, monstres, cases, freshCases, 0, -1, &count, i, nb);//Case haut centre
			break;
		case 2: 
			casesHandler(pisteurs, monstres, cases, freshCases, 1, -1, &count, i, nb);//Case haut droit
			break;
		case 3: 
			casesHandler(pisteurs, monstres, cases, freshCases, -1, 0, &count, i, nb);//Case gauche
			break;
		case 4:
			casesHandler(pisteurs, monstres, cases, freshCases, 1, 0, &count, i, nb);//Case droit
			break;
		case 5:
			casesHandler(pisteurs, monstres, cases, freshCases, -1, 1, &count, i, nb);//Case bas gauche
			break;
		case 6:
			casesHandler(pisteurs, monstres, cases, freshCases, 0, 1, &count, i, nb);//Case bas centre
			break;
		case 7:
			casesHandler(pisteurs, monstres, cases, freshCases, 1, 1, &count, i, nb);//Case bas droit
			break;
		}
	}

	if (count == 0) {
		printf("Rien autour de moi.\n\n");
		system("pause");//Temporaire
	}
	else {
		drawScreen(cases);
		for (int i = 0; i < 9; i++) {
			if (pisteurs[nb].detectedArea[i].fresh != NULL) {
				printf("Trace en %d de valeur %d. ", i+1, pisteurs[nb].detectedArea[i].fresh);
				system("pause");//Temporaire

			}
		}
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
