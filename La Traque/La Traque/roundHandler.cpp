#include "Header.h"

void deplacementMonstreHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int x, int y, int input, int* isValid, int* isPriority) {
	x = monstres[0].x + x;
	y = monstres[0].y + y;

	*isValid = 0;
	if (*isPriority == 1 || *isPriority == 0) {
		cases[monstres[0].y][monstres[0].x] = ' ';

		if (input == 1 || input == 3) {
			monstres[0].x = x;
		}
		else if (input == 0 || input == 2) {
			monstres[0].y = y;
		}//V�rifie les cas de sc�nario si c'est X qui est modifi� ou Y

		freshCases[monstres[0].y][monstres[0].x] = 16;
		*isValid = 1;


	}//Se valide apr�s une 2e boucle & Si la priorit� lui est donn�e avec un return 0 pour finir la fonction ici
	
	if ((cases[monstres[0].y][x] == ' ' || cases[y][monstres[0].x] == ' ') && *isPriority == -1) {
		*isPriority = 0;
	}//Si la case est bien dans le cadre, niveau 2 en priorit�
	else if ((cases[monstres[0].y][x] == 'P' || cases[y][monstres[0].x] == 'P') && (monstres[0].isHit == 0)) {
		*isPriority = 1;
	}//Si la case contient un pisteur, le monstre prioritise cette case
}

void deplacementHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nb){
	int input = 0;
	int isValid = 0;
	int isPriority = -1;
	int isChecked = 0;

	for (int i = 0; i < nb; i++) {
		cases[pisteurs[i].y][pisteurs[i].x] = '?';//Mets le status en attente apr�s que le pisteur a fini son rapport

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
			}//S�curit� pour pas placer n'importe comment le pisteur
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
		isChecked = 0;
		if ((monstres[0].top == 1 && monstres[0].bot == 1 && monstres[0].left == 1 && monstres[0].right == 1) || isPriority == 1) {
			isChecked = 1;
		}//V�rifie que toutes les cases soit checked OU si un joueur a �t� rep�r� dans une case

		if (isChecked == 0) {
			input = rand() % 4;
		}//V�rifie si aucune priorit� n'a �t� signal�, si non, on randomise la case o� se d�placera le monstre

		switch (input) {
		case 0:			
			monstres[0].top = 1;
			deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 0, 1, input, &isValid, &isPriority);
			break;
		case 1:			
			monstres[0].right = 1;
			deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 1, 0, input, &isValid, &isPriority);
			break;
		case 2:
			monstres[0].bot = 1;
			deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, 0, -1, input, &isValid, &isPriority);
			break;
		case 3:
			monstres[0].left = 1;
			deplacementMonstreHandler(pisteurs, monstres, cases, freshCases, -1, 0, input, &isValid, &isPriority);
			break;
		}
	} while (isValid == 0);//Boucle jusqu'� ce que le monstre se d�place

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

	if (luck <= 4) {//V�rifie si le nombre est plus petit que 4 pour la jauge de "chance"
		monstres[0].hp = monstres[0].hp - 1;
		monstres[0].isHit = 1;
		printf("Vous l'avez touche ! ");
		if (monstres[0].hp == 0) {//Si le la vie du monstre tombe � 0 sur ce coup, on d�clare vainqueur le joueur
			printf("Il est mort, bien joue !");
		}
		else {
			printf("Encore %d coup\n\n", monstres[0].hp);
		}
		system("pause");//Temporaire
	}
	else {
		printf("Manquez...Sauvez-vous vite !\n");//On sait tous qu'il est mort � ce moment
		system("pause");//Temporaire
	}
}

void pisteurActionHandler(pisteur* pisteurs, monstre* monstres, char cases[][W]) {
	char c = { NULL };
	int isActionDone = 0;

	cases[monstres[0].y][monstres[0].x] = 'M';//On affiche le monstre pour plus de visibilit� 

	drawScreen(cases);
	printf("Vous pouvez tirer avec la touche T.\n");
	printf("Ou sur la touche R pour ne rien faire.\n");

	do {
		c = getch();//R�cup�res l'input utilisateur 
		switch (toupper(c)) {//On mets le char en MAJ pour �viter tout probl�me
		case 'T':
			tirer(pisteurs, monstres, cases);//G�re le tire
			isActionDone = 1;//S�curit� pour quitter une fois l'action faites
			break;
		case 'R':
			printf("Vous ne tirez pas.\n\n");
			isActionDone = 1;//S�curit� pour quitter une fois l'action faites
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

		pisteurActionHandler(pisteurs, monstres, cases);//G�re les actions du pisteur
		
		//On r�cup�res les infos de la case et ses coordonn�es
		pisteurs[nb].detectedArea[i].y = y;
		pisteurs[nb].detectedArea[i].x = x;
		pisteurs[nb].detectedArea[i].fresh = freshCases[y][x];
		*count = 1;
	}
	else if (freshCases[y][x] >= 2) {//R�cup�re les infos de la case seulement si c'est frait de plus de 2
		Sleep(500);
		printf("\nTrace fraiche valant %d en X : %d, Y : %d.\n", freshCases[y][x], x, y);

		//On r�cup�res les infos de la case et ses coordonn�es
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
			Sleep(1000);
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
			printf("Rapport du pisteur %d en cours...\n", i+1);
			Sleep(1000);
			if (pisteurs[i].x == monstres[0].x && pisteurs[i].y == monstres[0].y) {
				printf("Le monstre viens de le tuer en (%d, %d)\n", monstres[0].x, monstres[i].y);
				cases[pisteurs[i].y][pisteurs[i].x] = ' ';
				pisteurs[i].isDead = 1;
				system("pause");
				//Cas si le monstre, � la fin du tour, est sur la case du pisteur, et donc le tue
			}
			else if (pisteurs[i].x != monstres[0].x && pisteurs[i].y != monstres[0].y) {
				rapport(pisteurs, monstres, cases, freshCases, i);//G�re le rapport du pisteur en cours
			}
		}
		else if (pisteurs[i].isDead == 1) {
			drawScreen(cases);
			printf("Le pisteur %d est mort en (%d, %d)\n", i+1, pisteurs[i].x, pisteurs[i].y);
			system("pause");
			//Cas pour juste rappel� que le pisteur x est mort 
		}
	}
}

void roundHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (freshCases[i][j] != 0) {
				freshCases[i][j] = freshCases[i][j] - 1;
			}//G�re l'usure des empreintes
		}
	}

	pisteurStatus(pisteurs, monstres, cases, freshCases, nbPisteur);//G�re le status du pisteur
	if (monstres[0].hp != 0) {
		deplacementHandler(pisteurs, monstres, cases, freshCases, nbPisteur);//G�re les d�placement du tour
	}
}
