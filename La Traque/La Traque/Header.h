#pragma once
#pragma warning (disable:4996);
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct pisteur {
	int x = 0;
	int y = 0;
	int detectArea[8][2] = {
		{x--, y--},
		{x, y--},
		{x++, y--},
		{x--, y},
		{x++, y},
		{x--, y++},
		{x, y++},
		{x++, y++},
	};

	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	int isDead = 1;
}pisteur;

typedef struct monstre {
	int x = 0;
	int y = 0;
	int hp = 4;

	int prevPos[15][3] = { NULL };

	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
}monstre;
