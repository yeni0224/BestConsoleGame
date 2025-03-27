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
			bool hpFlag; // 죽으면 F 살아 있으면 T

			const char* image1;
			const char* image2;

		}MONSTER;
		extern PLAYER player;
		extern MONSTER monsterA;
		extern MONSTER monsterB;
		extern MONSTER monsterC;



		void Reset();
		void BattleManager();

		void Battle1();
		void Battle2();
		void BattleText1();
		void BattleText2();
	}

}
