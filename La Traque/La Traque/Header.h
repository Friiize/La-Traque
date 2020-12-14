#pragma once
#pragma warning (disable:4996);
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int W = 31;
const int H = 16;

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

typedef struct prevPos {
	int fresh = 0;
	int prevX = 0;
	int prevY = 0;
};

typedef struct monstre {
	int x = 0;
	int y = 0;
	int hp = 4;

	prevPos prevPoses[15];

	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
}monstre;

void initScreen(char screen[][W]);
void drawScreen(char screen[][W], int H, int W);
void firstScreen(char screen[][W]);
void posHandler(pisteur* pisteurs, monstre* monstres, char screen[][W], int input, int W, int H);
void roundHandler(pisteur* pisteurs, monstre* monstres, char screen[][W]);