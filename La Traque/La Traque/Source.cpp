#include "Header.h"

void main() {
	int quit = 1;
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

	posHandler(pisteurs, monstres, cases, freshCases, input, W, H);

	while (quit) {
		drawScreen(cases);
		system("pause");//Temporaire
		roundHandler(pisteurs, monstres, cases, freshCases, input);//Gére le tour en cours

		for (int i = 0; i < input; i++) {
			quit = 0;
			if (pisteurs[i].isDead == 0) {
				quit = 1;
			}
		}//check si tout les pisteurs sont mort, si oui, le jeu s'arrêtes
	}
}