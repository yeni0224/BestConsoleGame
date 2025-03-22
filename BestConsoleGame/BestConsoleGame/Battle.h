#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>

typedef struct
{
	int width;
	int height;

	int posX;
	int posY;

	const char* image;

}PLAYER;

typedef struct
{
	int width;
	int height;

	int posX;
	int posY;

	const char* image;

}MONSTERA;


void Reset();

void Player();
void MonsterA();
void Battle1();
void Battle2();
void BattleText();