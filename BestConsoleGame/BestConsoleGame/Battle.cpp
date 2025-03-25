#include "Battle.h"
#include "Utility.h"
#include "Input_Sys.h"
#include "BestConsoleGame.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

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
            monsterA.attack = 10;
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
            printf(" 회복");
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
        void patternAttack(int playerRand, int monsterRand, int& charging);
        void patternRecovery(int playerRand, int monsterRand, int& charging);
        int charging = 1;

        void BattleText2()
        {

            int x = 79;
            ULONGLONG nowTick = GetTickCount64();
            ULONGLONG prevTick = nowTick;
            char symbols[] = { '>', ' ' }; // 번갈아 출력할 문자
            int index = 0;

            while (1)
            {
                int playerRand = rand() % 4; // 50% 확률 (0 ~ 3)
                int monsterRand = rand() % 7; // 50% 확률 (0 ~ 6)
                if (clearflag)
                {
                    if (global::input::IsEnterKeyOn())
                    {
                        if (!WasEnterKeyPressed)
                        {
                            GotoXY(7, 0);
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
                            global::hp = player.currentHeart;//도망 시 현재hp가져가도록
                            system("cls");//화면 초기화
                            startGame();//로비화면 출력
                            flag = true;//전체 반복문 나가는 flag
                            break;
                        }
                        if (x == 79)
                        {
                            patternAttack(playerRand, monsterRand, charging);
                            GotoXY(5, 5);
                            break;
                        }
                        global::input::Set(global::input::Space_KEY_INDEX, false);
                        WasSpaceKeyPressed = true;
                        if (x == 84)
                        {
                            patternRecovery(playerRand, monsterRand, charging);
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
        void patternAttack(int playerRand, int monsterRand, int& charging)
        {
            DWORD startTick = GetTickCount();
            
            if (monsterA.currentHeart > 0)
            {
                if (playerRand == 0) {//플레이어 크리티컬
                    monsterA.currentHeart -= player.attack * 2; // 몬스터 hp 감소
                    GotoXY(5, 14);
                    printf("Critical hit!!");
                    startTick = GetTickCount();
                    while (GetTickCount() - startTick < 500) {
                        // 게임 루프가 멈추지 않도록 적절한 작업 수행 가능
                    }
                    GotoXY(5, 14);
                    printf("              ");
                }
                else {
                    monsterA.currentHeart -= player.attack;
                }
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(60, 2);
                        printf("차징Critical hit");
                    }
                    else {
                        player.currentHeart -= monsterA.attack * 2;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * charging;
                        charging = 1;
                        GotoXY(60, 2);
                        printf("차징샷             ");
                    }
                    else {
                        player.currentHeart -= monsterA.attack;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                }
                else {
                    charging += 1;
                    GotoXY(60, 2);;
                    printf("~기를 모으는 중~");
                }

            }

            else if (monsterB.currentHeart > 0)
            {
                if (playerRand == 0) {//플레이어 크리티컬
                    monsterB.currentHeart -= player.attack * 2; // 몬스터 hp 감소
                    GotoXY(5, 14);
                    printf("Critical hit!!");
                    startTick = GetTickCount();
                    while (GetTickCount() - startTick < 500) {}
                    GotoXY(5, 14);
                    printf("              ");
                }
                else {
                    monsterB.currentHeart -= player.attack;
                }
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        printf("차징Critical hit");
                    }
                    else {
                        player.currentHeart -= monsterB.attack * 2;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * charging;
                        charging = 1;
                        GotoXY(60, 2);
                        printf("차징샷             ");
                    }
                    else {
                        player.currentHeart -= monsterB.attack;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                }
                else {
                    charging += 1;
                    GotoXY(60, 2);;
                    printf("~기를 모으는 중~");
                }
            }

            else if (monsterC.currentHeart > 0)
            {
                if (playerRand == 0) {//플레이어 크리티컬
                    monsterC.currentHeart -= player.attack * 2; // 몬스터 hp 감소
                    GotoXY(5, 14);
                    printf("Critical hit!!");
                    startTick = GetTickCount();
                    while (GetTickCount() - startTick < 500) {}
                    GotoXY(5, 14);
                    printf("              ");
                }
                else {
                    monsterC.currentHeart -= player.attack;
                }
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(60, 2);
                        printf("차징Critical hit");
                    }
                    else {
                        player.currentHeart -= monsterC.attack * 2;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * charging;
                        charging = 1;
                        GotoXY(60, 2);
                        printf("차징샷             ");
                    }
                    else {
                        player.currentHeart -= monsterC.attack;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                }
                else {
                    charging += 1;
                    GotoXY(60, 2);;
                    printf("~기를 모으는 중~");
                }
            }
        }
        void patternRecovery(int playerRand, int monsterRand, int& charging)
        {
            DWORD startTick = GetTickCount();

            if (monsterA.currentHeart > 0)
            {
                player.currentHeart += 10;
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }
                    else {
                        player.currentHeart -= monsterA.attack * 2;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * charging;
                        charging = 1;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                    else {
                        player.currentHeart -= monsterA.attack;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                }
                else {
                    charging += 1;
                    GotoXY(60, 2);;
                    printf("~기를 모으는 중~");
                }
            }
            else if (monsterB.currentHeart > 0)
            {
                player.currentHeart += 10;
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }
                    else {
                        player.currentHeart -= monsterB.attack * 2;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * charging;
                        charging = 1;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                    else {
                        player.currentHeart -= monsterB.attack;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                }
                else {
                    charging += 1;
                    GotoXY(60, 2);;
                    printf("~기를 모으는 중~");
                }
            }
            else if (monsterC.currentHeart > 0)
            {
                player.currentHeart += 10;
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }
                    else {
                        player.currentHeart -= monsterC.attack * 2;
                        GotoXY(60, 2);
                        printf("Critical hit");
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * charging;
                        charging = 1;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                    else {
                        player.currentHeart -= monsterC.attack;
                        GotoXY(60, 2);
                        printf("                ");
                    }
                }
                else {
                    charging += 1;
                    GotoXY(60, 2);;
                    printf("~기를 모으는 중~");
                }
            }
        }
    }

}

