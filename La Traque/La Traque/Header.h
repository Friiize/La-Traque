#pragma once
#pragma warning (disable:4996);
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

const int W = 31;
const int H = 16;

typedef struct detect {
	int x = 0;
	int y = 0;
	int fresh = 0;
}detect;


typedef struct pisteur {
	int x = 0;
	int y = 0;
	detect detectedArea[8];

	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	int isDead = 0;
}pisteur;


typedef struct monstre {
	int x = 0;
	int y = 0;
	int hp = 4;

	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	int isHit = 0;
}monstre;

void initScreen(char cases[][W], int freshCases[][W]);
void drawScreen(char cases[][W]);
void firstScreen(char cases[][W]);
void posHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int input);
void roundHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W], int nbPisteur);
void winLoseHandler(pisteur* pisteurs, monstre* monstres, char cases[][W], int freshCases[][W]);