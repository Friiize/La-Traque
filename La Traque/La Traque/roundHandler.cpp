#include "Header.h"

void deplacementMonstreHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int x, int y, int input, int* isValid) {
	x = monstres[0].x + x;
	y = monstres[0].y + y;

	if (freshCases[monstres[0].y][x] == ' ' || freshCases[y][monstres[0].x] == ' ') {
		cases[monstres[0].y][monstres[0].x] = ' ';

		if (input == 2 || input == 4) {
			monstres[0].x = x;
		}
		else if (input == 1 || input == 3) {
			monstres[0].y = y;
		}

		cases[monstres[0].y][monstres[0].x] = 'M';
		freshCases[monstres[0].y][monstres[0].x] = 16;
		*isValid = 1;
	} 
	else {
		*isValid = 0;
	}
}

void deplacementHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nb){
	int input = 0;
	int isValid = 0;
	for (int i = 0; i < nb; i++) {
		cases[pisteurs[i].y][pisteurs[i].x] = '?';//Mets le status en attente après que le pisteur a fini son rapport

		do {
			drawScreen(cases);
			printf("Veuillez donner une direction au pisteur %d, il avancera de une case.\n", i+1);
			printf("1 pour HAUT\t");
			printf("2 pour DROIT.\n");
			printf("3 pour BAS\t");
			printf("4 pour GAUCHE.\n");
			scanf("%d", &input);
		} while (input < 1 && input > 4);

		switch (input) {
		case 1:
			cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			pisteurs[i].y = pisteurs[i].y + 1;
			cases[pisteurs[i].y][pisteurs[i].x] = 'P';
			break;
		case 2:
			cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			pisteurs[i].x = pisteurs[i].x + 1;
			cases[pisteurs[i].y][pisteurs[i].x] = 'P';
			break;
		case 3:
			cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			pisteurs[i].y = pisteurs[i].y - 1;
			cases[pisteurs[i].y][pisteurs[i].x] = 'P';
			break;
		case 4:
			cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			pisteurs[i].x = pisteurs[i].x - 1;
			cases[pisteurs[i].y][pisteurs[i].x] = 'P';
			break;
		}

		drawScreen(cases);
		printf("Pisteur deplace.\n");
		system("pause");//Temporaire
	}
	
	do {
		input = rand() % 4;

		switch (input) {
		case 1:			
			deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 0, 1, input, &isValid);
			break;
		case 2:			
			deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 1, 0, input, &isValid);
			break;
		case 3:
			deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 0, -1, input, &isValid);
			break;
		case 4:
			deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, -1, 0, input, &isValid);
			break;
		}
	} while (isValid == 0);
}

void tirer(pisteur* pisteurs, monstre* monstres, char cases[][W]) {
	int luck = rand() % 10;
	drawScreen(cases);
	printf("Vous préparez le tire et...");
	Sleep(1000);
	if (luck <= 4) {
		monstres[0].hp = monstres[0].hp - 1;
		printf("Vous l'avez touché ! ");
		if (monstres[0].hp == 0) {
			printf("Il est mort, bien joue !");
		}
		else {
			printf("Encore %d coup", monstres[0].hp);
		}
		system("pause");//Temporaire
	}
	else {
		printf("Manquez...Sauvez-vous vite !");
		system("pause");//Temporaire
	}
}

void pisteurActionHandler(pisteur* pisteurs, monstre* monstres, char cases[][W]) {
	char c = getchar();
	drawScreen(cases);
	printf("Vous pouvez tirer avec la touche T.\n");
	printf("Ou sur la touche R pour ne rien faire.\n");

	switch (c) {
	case 'T':
		tirer(pisteurs, monstres, cases);
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
	else if (freshCases[y][x] >= 2) {
		printf("\nTrace fraiche valant %d en X : %d, Y : %d\n\n", freshCases[y][x], x, y);
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
		}//Check toutes les cases autour du pisteur
	}

	if (count == 0) {
		printf("Rien autour de moi.\n\n");
		system("pause");//Temporaire
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
				rapport(pisteurs, monstres, cases, freshCases, i);//Gére le rapport du pisteur en cours
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

	pisteurStatus(pisteurs, monstres, cases, freshCases, nbPisteur);//Gére le status du pisteur
	deplacementHandler(pisteurs, monstres, cases, freshCases, nbPisteur);//Gére les déplacement du tour
}
