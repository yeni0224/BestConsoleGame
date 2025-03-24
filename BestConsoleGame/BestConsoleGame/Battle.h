#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>

namespace global {
	namespace battle {
		typedef struct
		{
			int heart;
			int currentHeart;
			int attack;

			const char* image;

		}PLAYER;

		typedef struct
		{
			int heart;
			int currentHeart;
			int attack;
			const char* image;

		}MONSTERA;

		typedef struct
		{
			int heart;
			int currentHeart;
			int attack;
			const char* image;

		}MONSTERB;


		void Reset();
		void BattleManager();

		void Player();
		void MonsterA();
		void MonsterB();
		void Battle1();
		void Battle2();
		void BattleText1();
		void BattleText2();
	}
	
}
