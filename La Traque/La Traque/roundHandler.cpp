#include "Header.h"

void roundHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (freshCases[i][j] != 0) {
				freshCases[i][j]--;
			}
		}
	}
}
