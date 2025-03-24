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
        MONSTERB monsterB;
        bool flag = false;
        bool WasLeftKeyPressed = false;
        bool WasRightKeyPressed = false;
        bool WasSpaceKeyPressed = false;

        void Reset()
        {
            system("cls");
            Player();
            MonsterA();
            MonsterB();
        }

        void Player()
        {
            player.heart = global::hp;
            player.currentHeart = player.heart;
            player.attack = global::atk;
            player.image = "Player";
        }

        void MonsterA()
        {
            monsterA.heart = 100;
            monsterA.currentHeart = monsterA.heart;
            monsterA.attack = 10;
            monsterA.image = "monsterA";
        }

        void MonsterB()
        {
            monsterB.heart = 10;
            monsterB.currentHeart = monsterB.heart;
            monsterB.attack = 10;
            monsterB.image = "monsterB";
        }

        void BattleManager()
        {
            BattleText1();
            while (1)
            {
                Battle1();
                Battle2();
                BattleText2();
                if (flag)
                {
                    flag = false;
                    break;
                }
                
            }
            
        }
        void BattleText1()
        {
            GotoXY(80, 25);
            printf("공격");
            printf(" 방어");
            printf(" 도망");
        }

        void Battle1()
        {
            GotoXY(1, 15);
            printf("[ %d / %d ] \n", player.currentHeart, player.heart);
            GotoXY(1, 16);
            printf(player.image);

        }
        void Battle2()
        {
            if (monsterA.currentHeart != 0)
            {
                GotoXY(80, 1);
                printf("[ %d / %d ] \n", monsterA.currentHeart, monsterA.heart);
                GotoXY(80, 2);
                printf(monsterA.image);
            }
            else if (monsterB.currentHeart != 0)
            {
                GotoXY(80, 1);
                printf("[ %d / %d ] \n", monsterB.currentHeart, monsterB.heart);
                GotoXY(80, 2);
                printf(monsterB.image);
            }

        }
        void BattleText2()
        {
            
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
                GotoXY(x, 25);


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
                            flag = true;
                            break;
                        }
                        if (x == 79)
                        {

                            monsterA.currentHeart -= player.attack;

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
