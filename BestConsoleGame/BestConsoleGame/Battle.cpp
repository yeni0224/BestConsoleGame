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
        MONSTERC monsterC;
        bool flag = false;
        bool clearflag = false;
        bool WasLeftKeyPressed = false;
        bool WasRightKeyPressed = false;
        bool WasSpaceKeyPressed = false;
        bool WasEnterKeyPressed = false;

        void Reset()
        {
            system("cls");
            Player();
            MonsterA();
            MonsterB();
            MonsterC();
        }

        void Player()
        {
            player.heart = global::max_hp;
            player.currentHeart = global::hp;
            player.attack = global::atk;
            player.image = "Player";
        }

        void MonsterA()
        {
            monsterA.heart = 100;
            monsterA.currentHeart = monsterA.heart;
            monsterA.attack = 5;
            monsterA.image = "monsterA";
        }

        void MonsterB()
        {
            monsterB.heart = 100;
            monsterB.currentHeart = monsterB.heart;
            monsterB.attack = 10;
            monsterB.image = "monsterB";
        }

        void MonsterC()
        {
            monsterC.heart = 100;
            monsterC.currentHeart = monsterC.heart;
            monsterC.attack = 10;
            monsterC.image = "monsterC";
        }

        void BattleManager()
        {
            BattleText1();
            while (1)
            {
                if (player.currentHeart <= 0)
                {
                    system("cls");
                    startGame();
                    break;
                }
                Battle1();
                Battle2();
                BattleText2();
                if (flag)
                {
                    flag = false;
                    break;
                }
                if (clearflag)
                {
                    clearflag = false;
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
            global::input::UpdateInput();

            if (monsterA.currentHeart > 0)
            {
                GotoXY(80, 1);
                printf("[ %d / %d ] \n", monsterA.currentHeart, monsterA.heart);
                GotoXY(80, 2);
                printf(monsterA.image);
            }
            else if (monsterB.currentHeart > 0)
            {
                GotoXY(80, 1);
                printf("[ %d / %d ] \n", monsterB.currentHeart, monsterB.heart);
                GotoXY(80, 2);
                printf(monsterB.image);
            }
            else if (monsterC.currentHeart > 0)
            {
                GotoXY(80, 1);
                printf("[ %d / %d ] \n", monsterC.currentHeart, monsterC.heart);
                GotoXY(80, 2);
                printf(monsterC.image);
            }
            else
            {
                system("cls");
                GotoXY(1, 5);
                std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
                std::cout << "::::::--:::::::::::::--::::-::::::::::::-====--:::--------------::::::::-====-:::::::::::-------:::::::--::::::::::::-::\n";
                std::cout << ":::::-@@=:::::::::::*@%:::#@+::::::::+%@@%%%%@@#::%@@@@@@@@@@@@@=:::-*%@@%%%@@@#=:::::::*@@@@@@@@%*::::+@%-::::::::=@@-:\n";
                std::cout << "::::::*@%::::::::::-@@=:::%@+::::::+@@*=::::::--:::::::-@@=::::::::*@@*-:::::-+%@#-:::::*@#::::-=#@@-:::*@%:::::::-@@=::\n";
                std::cout << ":::::::%@*:::::::::%@*::::%@+:::::#@#-::::::::::::::::::@@=:::::::#@%-::::::::::*@%-::::*@#:::::::%@#::::#@#:::::-@@=:::\n";
                std::cout << ":::::::=@@-:::::::+@%:::::%@+::::*@%::::::::::::::::::::@@=::::::*@%:::::::::::::#@#::::*@#:::::::#@#:::::%@*:::-%@+::::\n";
                std::cout << "::::::::#@%::::::-@@=:::::%@+:::-@@=::::::::::::::::::::@@=::::::@@+:::::::::::::=@@-:::*@#::::::+@@-::::::%@+::%@+:::::\n";
                std::cout << ":::::::::@@+:::::#@*::::::%@+:::+@@:::::::::::::::::::::@@=:::::-@@=::::::::::::::@@=:::*@%*****%%*-:::::::-@@+#@*::::::\n";
                std::cout << ":::::::::+@@::::=@@:::::::%@+:::+@@:::::::::::::::::::::@@=:::::-@@=:::::::::::::-@@=:::*@@###%@%=::::::::::=@@@*:::::::\n";
                std::cout << "::::::::::#@*:::%@=:::::::%@+:::-@@=::::::::::::::::::::@@=::::::%@*:::::::::::::=@@::::*@#::::=@@+::::::::::+@%::::::::\n";
                std::cout << "::::::::::-@@=:*@#::::::::%@+::::#@%::::::::::::::::::::@@=::::::+@@-::::::::::::%@*::::*@#:::::-%@+:::::::::+@%::::::::\n";
                std::cout << ":::::::::::+@%=@@-::::::::%@+:::::%@%-::::::::::::::::::@@=:::::::*@@=:::::::::-%@#:::::*@#::::::-%@*::::::::+@%::::::::\n";
                std::cout << "::::::::::::%@@@+:::::::::%@+::::::*@@#+-----=+*::::::::@@=::::::::+%@%+-----+#@@+::::::*@#:::::::-%@*:::::::+@%::::::::\n";
                std::cout << "::::::::::::-%%#::::::::::#%+::::::::+#%@@@@%%#+::::::::#%=::::::::::=#%@@@@%%#=::::::::+%*::::::::-%%+::::::=%#::::::::\n";
                std::cout << ":::::::::::::::::::::::::::::::::::::::::--:::::::::::::::::::::::::::::::-:::::::::::::::::::::::::::::::::::::::::::::\n";
                std::cout << "                                                 엔터 입력 시 다시시작                                                 "; 
                clearflag = true;
             
                
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
                if (clearflag)
                {
                    if (global::input::IsEnterKeyOn())
                    {
                        if (!WasEnterKeyPressed)
                        {
                            GotoXY(7, 0);
                            printf("aaaaaa");
                            global::input::Set(global::input::Enter_KEY_INDEX, false);
                            WasEnterKeyPressed = true;
                            system("cls");
                            startGame();
                            break;
                        }
                    }
                    else
                    {
                        WasEnterKeyPressed = false;
                    }
                }
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
                            global::hp = player.currentHeart;
                            system("cls");
                            startGame();
                            flag = true;
                            break;
                        }
                        if (x == 79)
                        {
                            if (monsterA.currentHeart > 0)
                            {
                                monsterA.currentHeart -= player.attack;
                                Sleep(100);
                                player.currentHeart -= monsterA.attack;
                            }
                            else if (monsterB.currentHeart > 0)
                            {
                                monsterB.currentHeart -= player.attack;
                                Sleep(100);
                                player.currentHeart -= monsterB.attack;
                            }
                            else if (monsterC.currentHeart > 0)
                            {
                                monsterC.currentHeart -= player.attack;
                                Sleep(100);
                                player.currentHeart -= monsterC.attack;
                            }


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
