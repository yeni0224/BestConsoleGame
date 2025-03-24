#include "Battle.h"
#include "Utility.h"
#include "Input_Sys.h"
#include "BestConsoleGame.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <chrono>

namespace global {
    namespace battle {
        PLAYER player;
        MONSTERA monsterA;

        void Reset()
        {
            system("cls");
            Player();
            MonsterA();
            MonsterB();
        }

        void Player()
        {


            player.image = "Player";
        }

        void MonsterA()
        {

            //텍스트
            monsterA.image = "monsterA";

        }

        void MonsterB()
        {

            //텍스트
            monsterA.image = "monsterA";

        }

        void BattleManager()
        {
            Battle1();
            Battle2();
            BattleText1();
            BattleText2();
        }

        void Battle1()
        {
            GotoXY(1, 15);

            int heart = global::hp;
            int currentHeart = heart;
            int attack = global::atk;
            printf("[ %d / %d ] \n", currentHeart, heart);
            printf(player.image);

        }
        void Battle2()
        {
            GotoXY(80, 1);
            printf(monsterA.image);
        }
        void BattleText1()
        {
            GotoXY(80, 25);
            printf("공격");
            printf(" 방어");
            printf(" 도망");
        }



        void BattleText2()
        {
            bool WasLeftKeyPressed = false;
            bool WasRightKeyPressed = false;
            bool WasSpaceKeyPressed = false;
            int x = 79;
            ULONGLONG nowTick = GetTickCount64();
            ULONGLONG prevTick = nowTick;
            char symbols[] = { '>', ' ' }; // 번갈아 출력할 문자
            int index = 0;

            while (1)
            {
                global::input::UpdateInput();
                nowTick = GetTickCount64();
                ULONGLONG elapsedTick = nowTick - prevTick;



                if (elapsedTick >= 500 && elapsedTick <= 999)
                {
                    GotoXY(x, 25);
                    std::cout << symbols[index] << std::flush; // 화면 덮어쓰기
                    index = 1 - index; // 0과 1을 번갈아가며 변경
                    prevTick = nowTick;
                }

                if (global::input::IsLeftKeyOn())
                {
                    if (!WasLeftKeyPressed) // 키를 처음 눌렀을 때만 실행
                    {
                        global::input::Set(global::input::LEFT_KEY_INDEX, false);
                        WasLeftKeyPressed = true;
                        GotoXY(x, 25);
                        std::cout << symbols[1];

                        if (x > 79) x -= 5;
                    }
                }
                else
                {
                    WasLeftKeyPressed = false;
                }

                if (global::input::IsRightKeyOn())
                {
                    if (!WasRightKeyPressed) // 키를 처음 눌렀을 때만 실행
                    {
                        global::input::Set(global::input::RIGHT_KEY_INDEX, false);
                        WasRightKeyPressed = true;
                        GotoXY(x, 25);
                        std::cout << symbols[1];

                        if (x < 89) x += 5;
                    }
                }
                else
                {
                    WasRightKeyPressed = false;
                }


                if (global::input::IsSpaceKeyOn())
                {
                    if (!WasSpaceKeyPressed)
                    {
                        global::input::Set(global::input::Space_KEY_INDEX, false);
                        WasSpaceKeyPressed = true;
                        if (x == 89)
                        {
                            system("cls");
                            startGame();
                            break;
                        }
                    }
                }
                else
                {
                    WasSpaceKeyPressed = false;
                }
            }
        }
    }

}
