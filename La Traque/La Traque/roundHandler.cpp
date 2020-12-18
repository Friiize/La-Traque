#include "Header.h"

int deplacementMonstreHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int x, int y, int input, int* isValid, int* isPriority) {
	x = monstres[0].x + x;
	y = monstres[0].y + y;

	if (*isPriority == 1 || *isPriority == 0) {
		cases[monstres[0].y][monstres[0].x] = ' ';

		if (input == 1 || input == 3) {
			monstres[0].x = x;
		}
		else if (input == 0 || input == 2) {
			monstres[0].y = y;
		}

		freshCases[monstres[0].y][monstres[0].x] = 16;
		*isValid = 1;

		return 0;
	}//Se valide après une 2e boucle & Si la priorité lui est donnée avec un return 0 pour finir la fonction ici

	if ((cases[monstres[0].y][x] == ' ' || cases[y][monstres[0].x] == ' ') && *isPriority == -1) {
		*isPriority = 0;
	}//Si la case est bien dans le cadre, niveau 2 en priorité
	else if ((cases[monstres[0].y][x] == 'P' || cases[y][monstres[0].x] == 'P') && (monstres[0].isHit == 0)) {
		*isPriority = 1;
		return input;
	}//Si la case contient un pisteur, le monstre prioritise cette case
	else {
		*isValid = 0;
	}
}

void deplacementHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nb){
	int input = 0;
	int isValid = 0;
	int isPriority = -1;

	for (int i = 0; i < nb; i++) {
		cases[pisteurs[i].y][pisteurs[i].x] = '?';//Mets le status en attente après que le pisteur a fini son rapport

		do {
			drawScreen(cases);
			printf("Veuillez donner une direction de une case au pisteur %d\n", i + 1);
			printf("1 pour HAUT\t");
			printf("2 pour DROIT.\n");
			printf("3 pour BAS\t");
			printf("4 pour GAUCHE.\n");
			scanf("%d", &input);
		} while (input < 1 && input > 4);

		switch (input) {
		case 1:
			cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			pisteurs[i].y = pisteurs[i].y - 1;
			if (cases[pisteurs[i].y][pisteurs[i].x] == '*' || cases[pisteurs[i].y][pisteurs[i].x] == 'P') {
				drawScreen(cases);
				printf("Vous ne pouvez pas sortir du cadre !\n");
				printf("Ou allez sur un autre pisteur !\n");
				pisteurs[i].y = pisteurs[i].y + 1;
				i--;
				system("pause");
				break;
			}//Sécurité pour pas placer n'importe comment le pisteur
			else {
				cases[pisteurs[i].y][pisteurs[i].x] = 'P';
			}
			break;
		case 2:
			cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			pisteurs[i].x = pisteurs[i].x + 1;
			if (cases[pisteurs[i].y][pisteurs[i].x] == '*' || cases[pisteurs[i].y][pisteurs[i].x] == 'P') {
				drawScreen(cases);
				printf("Vous ne pouvez pas sortir du cadre !\n\n");
				pisteurs[i].x = pisteurs[i].x - 1;
				i--;
				system("pause");
				break;
			}
			else {
				cases[pisteurs[i].y][pisteurs[i].x] = 'P';
			}
			break;
		case 3:
			cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			pisteurs[i].y = pisteurs[i].y + 1;
			if (cases[pisteurs[i].y][pisteurs[i].x] == '*' || cases[pisteurs[i].y][pisteurs[i].x] == 'P') {
				drawScreen(cases);
				printf("Vous ne pouvez pas sortir du cadre !\n\n");			
				pisteurs[i].y = pisteurs[i].y - 1;
				i--;
				system("pause");
				break;
			}
			else {
				cases[pisteurs[i].y][pisteurs[i].x] = 'P';
			}
			break;
		case 4:
			cases[pisteurs[i].y][pisteurs[i].x] = ' ';
			pisteurs[i].x = pisteurs[i].x - 1;
			if (cases[pisteurs[i].y][pisteurs[i].x] == '*' || cases[pisteurs[i].y][pisteurs[i].x] == 'P') {
				drawScreen(cases);
				printf("Vous ne pouvez pas sortir du cadre !\n\n");
				pisteurs[i].x = pisteurs[i].x + 1;
				cases[pisteurs[i].y][pisteurs[i].x] = 'P';
				i--;
				system("pause");
				break;
			}
			else {
				cases[pisteurs[i].y][pisteurs[i].x] = 'P';
			}
			break;
		}

		drawScreen(cases);
		printf("La position du pisteur a ete change.\n");
		system("pause");//Temporaire
	}
	
	do {
		if (isPriority == -1) {
			input = rand() % 4;
		}//Vérifie si aucune priorité n'a été signalé, si non, on randomise la case où se déplacera le monstre

		switch (input) {
		case 0:			
			input = deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 0, 1, input, &isValid, &isPriority);
			break;
		case 1:			
			input = deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 1, 0, input, &isValid, &isPriority);
			break;
		case 2:
			input = deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 0, -1, input, &isValid, &isPriority);
			break;
		case 3:
			input = deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, -1, 0, input, &isValid, &isPriority);
			break;
		}
	} while (isValid == 0);//Boucle jusqu'à ce que le monstre se déplace

	drawScreen(cases);
	monstres[0].isHit == 0;
	printf("Prochain tour...\n\n");
	system("pause");
}

void tirer(pisteur* pisteurs, monstre* monstres, char cases[][W]) {
	int luck = rand() % 10;

	drawScreen(cases);
	printf("Vous preparez le tire et...");
	Sleep(1000);

	if (luck <= 4) {//Vérifie si le nombre est plus petit que 4 pour la jauge de "chance"
		monstres[0].hp = monstres[0].hp - 1;
		monstres[0].isHit = 1;
		printf("Vous l'avez touche ! ");
		if (monstres[0].hp == 0) {//Si le la vie du monstre tombe à 0 sur ce coup, on déclare vainqueur le joueur
			printf("Il est mort, bien joue !");
		}
		else {
			printf("Encore %d coup\n\n", monstres[0].hp);
		}
		system("pause");//Temporaire
	}
	else {
		printf("Manquez...Sauvez-vous vite !\n");//On sait tous qu'il est mort à ce moment
		system("pause");//Temporaire
	}
}

void pisteurActionHandler(pisteur* pisteurs, monstre* monstres, char cases[][W]) {
	char c = { NULL };
	int isActionDone = 0;

	cases[monstres[0].y][monstres[0].x] = 'M';//On affiche pour plus de visibilité le monstre

	drawScreen(cases);
	printf("Vous pouvez tirer avec la touche T.\n");
	printf("Ou sur la touche R pour ne rien faire.\n");

	do {
		c = getch();//Récupères l'input utilisateur 
		switch (toupper(c)) {//On mets le char en MAJ pour éviter tout problème
		case 'T':
			tirer(pisteurs, monstres, cases);//Gére le tire
			isActionDone = 1;//Sécurité pour quitter une fois l'action faites
			break;
		case 'R':
			printf("Vous ne tirez pas.\n\n");
			isActionDone = 1;//Sécurité pour quitter une fois l'action faites
			break;
		}
	} while (isActionDone == 0);
}
	
void casesHandler(pisteur* pisteurs, monstre* monstres,char cases[][W], int freshCases[][W], int x, int y, int* count, int i, int nb) {
	x = pisteurs[nb].x + x;
	y = pisteurs[nb].y + y;

	if (x == monstres[0].x && y == monstres[0].y) {
		printf("Je le vois.\n\n");
		system("pause");

		pisteurActionHandler(pisteurs, monstres, cases);//Gére les actions du pisteur
		
		//On récupères les infos de la case et ses coordonnées
		pisteurs[nb].detectedArea[i].y = y;
		pisteurs[nb].detectedArea[i].x = x;
		pisteurs[nb].detectedArea[i].fresh = freshCases[y][x];
		*count = 1;
	}
	else if (freshCases[y][x] >= 2) {//Récupère les infos de la case seulement si c'est frait de plus de 2
		printf("\nTrace fraiche valant %d en X : %d, Y : %d.\n", freshCases[y][x], x, y);

		//On récupères les infos de la case et ses coordonnées
		pisteurs[nb].detectedArea[i].y = y;
		pisteurs[nb].detectedArea[i].x = x;
		pisteurs[nb].detectedArea[i].fresh = freshCases[y][x];
		*count = 1;
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
			system("pause");
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
			printf("Rapport du pisteur %d en cours...", i+1);
			if (pisteurs[i].x == monstres[0].x && pisteurs[i].y == monstres[0].y) {
				printf("Le monstre viens de le tuer en (%d, %d)\n\n", monstres[0].x, monstres[i].y);
				cases[pisteurs[i].y][pisteurs[i].x] = ' ';
				system("pause");

			}
			else if (pisteurs[i].x != monstres[0].x && pisteurs[i].y != monstres[0].y) {
				rapport(pisteurs, monstres, cases, freshCases, i);//Gére le rapport du pisteur en cours
			}
		}
		else if (pisteurs[i].isDead == 1) {
			drawScreen(cases);
			printf("Le pisteur %d est mort en (%d, %d)\n\n", i+1, pisteurs[i].x, pisteurs[i].y);
			system("pause");

		}
	}
}

void roundHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (freshCases[i][j] != 0) {
				freshCases[i][j] = freshCases[i][j] - 1;
			}//Gére l'usure des empreintes
		}
	}

	pisteurStatus(pisteurs, monstres, cases, freshCases, nbPisteur);//Gére le status du pisteur
	if (monstres[0].hp <= 1) {
		deplacementHandler(pisteurs, monstres, cases, freshCases, nbPisteur);//Gére les déplacement du tour
	}
}
