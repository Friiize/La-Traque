#include "Header.h"

void main() {
	char screen[H][W] = { NULL };
	int quit = 1;
	int input = -1;
	pisteur* pisteurs = { NULL };
	monstre* monstres = (monstre*)calloc(1, sizeof(monstre));

	initScreen(screen); //Initialise le tableau
	firstScreen(screen); //Premire affichage du jeu

	do {
		drawScreen(screen, H, W);//Affiche un visuel du tableau avec les pos des pisteurs
		printf("Combien de pisteur ? (entre 3 et 10)\n");
		scanf("%d", &input);
	} while (input < 3 || input > 10);

    pisteurs = (pisteur*)calloc(input, sizeof(pisteur)); //Initialise le nombre de pisteur

	posHandler(pisteurs, monstres, screen, input, W, H);

	while (quit) {
		drawScreen(screen, H, W);
		system("pause");//Temporaire
		roundHandler(pisteurs, monstres, screen);//Gére les tours

		for (int i = 0; i < input; i++) {
			quit = 0;
			if (pisteurs[i].isDead == 0) {
				quit = 1;
			}
		}//check si tout les pisteurs sont mort, si oui, le jeu s'arrêtes
	}
}
