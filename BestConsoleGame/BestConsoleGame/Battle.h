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
			bool hpFlag;

			const char* image1;
			const char* image2;

		}MONSTER;

		


		void Reset();
		void BattleManager();

		/*void Player();
		void MonsterA();
		void MonsterB();
		void MonsterC();*/
		void Battle1();
		void Battle2();
		void BattleText1();
		void BattleText2();
	}
	
}
