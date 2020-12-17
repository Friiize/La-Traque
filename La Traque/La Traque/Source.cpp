#include "Header.h"

void main() {
	srand(time(NULL));//Pour éviter le même séquence de random 
	int quit = 0;
	int input = -1;
	char cases[H][W];
	int freshCases[H][W] = { NULL };
	pisteur* pisteurs = { NULL };
	monstre* monstres = (monstre*)calloc(1, sizeof(monstre));


	initScreen(cases, freshCases); //Initialise le tableau
	firstScreen(cases); //Premire affichage du jeu

	do {
		drawScreen(cases);//Affiche un visuel du tableau avec les pos des pisteurs
		printf("Combien de pisteur ? (entre 3 et 10)\n");
		scanf("%d", &input);
	} while (input < 3 || input > 10);

    pisteurs = (pisteur*)calloc(input, sizeof(pisteur)); //Initialise le nombre de pisteur

	posHandler(pisteurs, monstres, cases, freshCases, input);

	while (quit == 0) {
		drawScreen(cases);
		roundHandler(pisteurs, monstres, cases, freshCases, input);//Gére le tour en cours
		quit = winLoseHandler(pisteurs, monstres, cases, freshCases, input);
	}
}