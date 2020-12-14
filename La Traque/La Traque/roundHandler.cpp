#include "Header.h"

void roundHandler(pisteur* pisteurs, monstre* monstres, char screen[][W]) {
	for (int i = 0; i < 14; i++) {
		if (monstres[0].prevPoses[i].fresh != 0) {
			monstres[0].prevPoses[i].fresh--;
		}
	}
}
