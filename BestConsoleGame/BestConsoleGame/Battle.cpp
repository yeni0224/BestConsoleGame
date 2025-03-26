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
        int num = 0;


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
            player.image = "\033[10;1H                    :@@@@*+                    \033[11;1H            ---%%#-====+%%*-            \033[12;1H          :***###+==+=======+@            \033[13;1H         +%###******=*+=======+-          \033[14;1H       :@#***********==*======@*          \033[15;1H       :@%**********+**+**++=-****+=      \033[16;1H        -+**%@@@%********+:::..=##+-      \033[17;1H         *@**********@@@@%**#@@*::        \033[18;1H         *@@@@@@@@@@@@@@:-@-+@@+          \033[19;1H         -*@@@@@@@@@@@@@=+@.:+-:          \033[20;1H          :#%@@@@@@@@@@#%#+...%+          \033[21;1H            =#@@@@@@*=====--+@           \033[22;1H     ::-*#%%%%%#####@@%####+=            \033[23;1H   :=+*#-======+**%@%*#@++*=-            \033[24;1H   +%*+=*==*==*==@@@#@%=..:.=%            \033[25;1H :@%**%@@#*=+*=%@****@%-...@#.@*..+@@%*   \033[26;1H :=*#%%*==#@####%%****@%-+*#....=@%=....@=  \033[27;1H+@##***#####%@@#****@++=@%=-:..:-+++...-=+ \033[28;1H+@@%*********#@#****@@@@+===--...@+.+-..*%  \033[29;1H :@%*********#@#**@@**#@=========@+..*@=#%  \033[30;1H :+*%%#*******%%%%%%%#**+**====+*@#+++++-  \033[31;1H    :::*@@@@@@@@##@#*#%#:..-%%%%@@-::      ";
        }

        void MonsterA()
        {
            monsterA.heart = 100;
            monsterA.currentHeart = monsterA.heart;
            monsterA.attack = 10;

            monsterA.image1 = "\033[4;65H          @@@@@@@@@@@@                     \n\033[5;65H      @@%%------------%%@                  \n\033[6;65H    @%=----::...::::-----#%                \n\033[7;65H   %+---===::....::::------*@              \n\033[8;65H  @=--======*##**=:::--------*@           \n\033[9;65H @@=%%%===%%%%######====------*@          \n\033[10;65H @-=#%%%:=+#%%%#=####+====------*@        \n\033[11;65H @--===-#=#*==+*####==++===-------+@      \n\033[12;65H@--====##-+%+==========-==----------*@    \n\033[13;65H@---===#%%+%+=#:=========-::::::------#   \n\033[14;65H@--=-===%%+%%=##========-::.::::-------@@ \n\033[15;65H@--=====#%#*%==*========-:..::----------@ \n\033[16;65H@--:::-------------::----:::..::---------@ \n\033[17;65H@-+++++++++++++++++++++++++::::::++++++--@ \n\033[18;65H  @+++++++++++++++++++++++++++++++++++++@ \n\033[19;65H     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   \n";
            monsterA.image2 = "\033[4;65H                  @@@@@@@@@@@@                     \n\033[5;65H             @@%%------------%%@                  \n\033[6;65H          @%=----::...::::-----#%                \n\033[7;65H        %+---===::....::::------*@              \n\033[8;65H       @=--======*##**=:::--------*@           \n\033[9;65H     @@=%%%===%%%%######====------*@          \n\033[10;65H    @-=#%%%:=+#%%%#=####+====------*@        \n\033[11;65H    @--===-#=#*==+*####==++===-------+@      \n\033[12;65H  @--====##-+%+==========-==----------*@    \n\033[13;65H @---===#%%+%+=#:=========-::::::------#   \n\033[14;65H@--=-===%%+%%=##========-::.::::-------@@ \n\033[15;65H@--=====#%#*%==*========-:..::----------@ \n\033[16;65H@--:::-------------::----:::..::---------@ \n\033[17;65H@-+++++++++++++++++++++++++::::::++++++--@ \n\033[18;65H  @+++++++++++++++++++++++++++++++++++++@ \n\033[19;65H     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   \n";
        }

        void MonsterB()
        {
            monsterB.heart = 100;
            monsterB.currentHeart = monsterB.heart;
            monsterB.attack = 10;
            monsterB.image1 = "\033[4;70H        -*+#*#@@#%##+==+==:       \n\033[5;70H    -=+=*#%%#%####%%%%@@#*#**=    \n\033[6;70H  -==%%=:                +*%%@+=  \n\033[7;70H:-@@%                      =@@*##:\n\033[8;70H==+=:=--:-:--::...:.-=---::.:-*###\n\033[9;70H=*+=...::-==:..=--...----:..-=+#%= \n\033[10;70H-=** %@@@@@@%+= **++@@@@@#%#:= :%=\n\033[11;70H:**=-%%@@@@@@@%  -=@@@@@@@@@*- -#:\n\033[12;70H:*+: %@@@@@@@%---+=@@@@@@@@@:: *= \n\033[13;70H.+:   #%@@@#-==@%%%-+@@@%#+-: =+  \n\033[14;70H:==-: --::==: @@#@@*= :-    :-=+  \n\033[15;70H  =+--= =:    @@@@@+++*===-::*+:  \n\033[16;70H   :#@%+ :    #@@@*+=--- *=#%:    \n\033[17;70H    :+ @@+=  :@@@*.++*+%@==       \n\033[18;70H     ==-*%*+-===--=++##*@+-=       \n\033[19;70H      += =#%*#-=-=*+**+@+:-=       \n\033[20;70H      :=-==#%%=#=+-*@@#:  +       \n\033[21;70H       :=-==-:::-+:     :+        \n\033[22;70H         =:--    :-:   ==         \n\033[23;70H          :+*=+++==+*#-           \n";
            monsterB.image2 = "\033[4;70H        -*+#*#@@#%##+==+==:       \n\033[5;70H    -=+=*#%%#%####%%%%@@#*#**=    \n\033[6;70H  -==%%=:                +*%%@+=  \n\033[7;70H:-@@%                      =@@*##:\n\033[8;70H==+=:=--:-:--::...:.-=---::.:-*###\n\033[9;70H=*+=...::-==:..=--...----:..-=+#%= \n\033[10;70H-=** %@@@@@@%+= **++@@@@@#%#:= :%=\n\033[11;70H:**=-%%@@@@@@@%  -=@@@@@@@@@*- -#:\n\033[12;70H:*+: %@@@@@@@%---+=@@@@@@@@@:: *= \n\033[13;70H.+:   #%@@@#-==@%%%-+@@@%#+-: =+  \n\033[14;70H:==-: --::==: @@#@@*= :-    :-=+  \n\033[15;70H  =+--= =:    @@@@@+++*===-::*+:  \n\033[16;70H   :#@%+ :    #@@@*+=--- *=#%:    \n\033[17;70H    :+ @@+=  :@@@*.++*+%@==       \n\033[18;70H     ==-*%*+-===--=++##*@+-=       \n\033[19;70H      += =#%*#-=-=*+**+@+:-=       \n\033[20;70H      :=-==#%%=#=+-*@@#:  +       \n\033[21;70H       :=-==-:::-+:     :+        \n\033[22;70H         =:--    :-:   ==         \n\033[23;70H          :+*=+++==+*#-           \n";
        }

        void MonsterC()
        {
            monsterC.heart = 100;
            monsterC.currentHeart = monsterC.heart;
            monsterC.attack = 10;
            monsterC.image1 = 
                "\033[4;67H   -%%-::-#@=.    .*:.        @@+++++*@@%=.\n"
                "\033[5;67H .=@*-:::::*@+.             .@@+++++*+++*%@@+\n"
                "\033[6;67H.+@*::::::::+@%.           .%@++++++%@#@@%*:.\n"
                "\033[7;67H-@*::::::::::+@#          .#@++++++++@@=.\n"
                "\033[8;67H%%::::::::::::@@.      ..=@#+%@@@@@@#+*@*.... ..*%:. \n"
                "\033[9;67H*@=::::::::::-@%.     #@@@@@@@@:..+@@@@@@@@*..-@@@@*\n"
                "\033[10;67H.%%=::::::::-%@.      #@*****@@-..+@%****#@*.  .+#:\n"
                "\033[11;67H.%@%%%%%%%%%%@@.   .-@@*++++++++++++++++++*@@+..\n"
                "\033[12;67H.%#..........%@.  .#@@@@@@@@@@@@@@@@@@@@@@@@@@%-\n"
                "\033[13;67H.%@@@@@@@@@@@@@.   .*@=....................-@%.\n"
                "\033[14;67H.+@+::::::::=@% .+@@%:.........:#@%+=---=%#:.#%- ==.\n"
                "\033[15;67H.#@%%%%%%%%%%@@...-%=......:+#@@*-------=%#:.+@=-%*.\n"
                "\033[16;67H...:::=**@#::..   -%-..@@@@@#=-----*@+--=%#:.+@@%-..\n"
                "\033[17;67H     +@+*@*.   ..:+@-..-@#-----=--=-----+@+..+@=.\n"
                "\033[18;67H     +@+*@*.   .=##@-..:#@+---+%%%%+---+@#:..+@@#:\n"
                "\033[19;67H     +@+*@*.      -%-...:*@#+=-------+#@*:...+@=..\n"
                "\033[20;67H     +@+*@*.      -%=::+#%@@@@%####%@@@@%#+-:-=: \n"
                "\033[21;67H     +@+*@*.     .=@@@@%*++*@%=++++=%@*++*%@@%*-. \n"
                "\033[22;67H     +@+*@*.   .-@@#++++++++#@%=--=%@#++++++++#@@*.\n"
                "\033[23;67H     +@+*@*.  .#@*++++++++++++#@@@@#++++++++++++*@%:\n"
                "\033[24;67H     +@+*@*.  =@#+++++++++++++%@=+@#+++++++++++++*@*\n";;
            monsterC.image2 = "monsterC";
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
            GotoXY(80, 28);
            printf("공격");
            printf(" 회복");
            printf(" 도망");
        }

        void Battle1()
        {
            GotoXY(10, 7);
            printf("[ %d / %d ] \n", player.currentHeart, player.heart);

            std::cout << player.image;

        }
        void Battle2()
        {
            global::input::UpdateInput();

            if (monsterA.currentHeart > 0)
            {
                GotoXY(75, 0);
                printf("[ %d / %d ] \n", monsterA.currentHeart, monsterA.heart);
                setColor(10);
                std::cout << monsterA.image1;
                setColor(15);
            }
            else if (monsterB.currentHeart > 0)
            {
                std::cout << "\033[4;65H                                                                \033[5;65H                                                                \033[6;65H                                                                \033[7;65H                                                                \033[8;65H                                                                \033[9;65H                                                                \033[10;65H                                                               \033[11;65H                                                                \033[12;65H                                                               \033[13;65H                                                                \033[14;65H                                                                \033[15;65H                                                         \033[16;65H                                          \033[17;65H                                              \033[18;65H                                                  \033[19;65H                                                      \033[20;65H                                                                \033[21;65H                                                                \033[22;65H                                                                \033[23;65H                                                                ";
                GotoXY(75, 0);
                printf("[ %d / %d ] \n", monsterB.currentHeart, monsterB.heart);
                setColor(8);
                std::cout << monsterB.image1;
                setColor(15);
            }
            else if (monsterC.currentHeart > 0)
            {
                //std::cout << "\033[4;65H                                                                \033[5;65H                                                                \033[6;65H                                                                \033[7;65H                                                                \033[8;65H                                                                \033[9;65H                                                                \033[10;65H                                                               \033[11;65H                                                                \033[12;65H                                                               \033[13;65H                                                                \033[14;65H                                                                \033[15;65H                                                         \033[16;65H                                          \033[17;65H                                              \033[18;65H                                                  \033[19;65H                                                      \033[20;65H                                                                \033[21;65H                                                                \033[22;65H                                                                \033[23;65H                                                                ";
                GotoXY(75, 0);
                printf("[ %d / %d ] \n", monsterC.currentHeart, monsterC.heart);
                std::cout << monsterC.image1;
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
                for (int x = 1; x < 49; x += 2) {
                    GotoXY(x, 0);
                    printf(" -");
                }
                for (int y = 1; y < 4; y++)
                {
                    for (int x = 0; x < 51; x += 50)
                    {
                        GotoXY(x, y);
                        printf("|");
                    }
                }
                for (int x = 1; x < 49; x += 2) {
                    GotoXY(x, 4);
                    printf(" -");
                }
                for (int y = 0; y < 5; y += 4)
                {
                    for (int x = 0; x < 51; x += 50)
                    {
                        GotoXY(x, y);
                        printf("+");
                    }
                }
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
                GotoXY(x, 28);


                if (elapsedTick >= 500 && elapsedTick <= 999)
                {
                    GotoXY(x, 28);
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
                        GotoXY(x, 28);
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
                        GotoXY(x, 28);
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
                        for (int y = 1; y < 4; y++)
                        {
                            for (int x = 1; x < 50; x++) {
                                GotoXY(x, y);
                                printf(" ");
                            }
                        }
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
                setColor(12);
                std::cout << monsterA.image2;
                setColor(15);
                if (playerRand == 0) {//플레이어 크리티컬
                    monsterA.currentHeart -= player.attack * 2; // 몬스터 hp 감소
                    GotoXY(1,  1);
                    printf("치명적인 공격! 몬스터에게 %d 피해를 주었습니다!", player.attack * 2);

                }
                else {
                    monsterA.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("공격! 몬스터에게 %d 피해를 주었습니다!", player.attack);
                }
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!" , monsterA.attack * 2 * charging);
                    }
                    else {
                        player.currentHeart -= monsterA.attack * 2;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * charging;
                        charging = 1;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * charging);
                    }
                    else {
                        player.currentHeart -= monsterA.attack;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }

            }

            else if (monsterB.currentHeart > 0)
            {
                setColor(12);
                std::cout << "\033[4;70H        -*+#*#@@#%##+==+==:       \n\033[5;70H    -=+=*#%%#%####%%%%@@#*#**=    \n\033[6;70H  -==%%=:                +*%%@+=  \n\033[7;70H:-@@%                      =@@*##:\n\033[8;70H==+=:=--:-:--::...:.-=---::.:-*###\n\033[9;70H=*+=...::-==:..=--...----:..-=+#%= \n\033[10;70H-=** %@@@@@@%+= **++@@@@@#%#:= :%=\n\033[11;70H:**=-%%@     @%  -=@      @@*- -#:\n\033[12;70H:*+: %@     @%---+=@@     @@:: *= \n\033[13;70H.+:   #%@@@#-==@%%%-+@@@%#+-: =+  \n\033[14;70H:==-: --::==: @@#@@*= :-    :-=+  \n\033[15;70H  =+--= =:    @@@@@+++*===-::*+:  \n\033[16;70H   :#@%+ :    #@@@*+=--- *=#%:    \n\033[17;70H    :+ @@+=  :@@@*.++*+%@==       \n\033[18;70H     ==-*%*+-===--=++##*@+-=       \n\033[19;70H      += =#%*#-=-=*+**+@+:-=       \n\033[20;70H      :=-==#%%=#=+-*@@#:  +       \n\033[21;70H       :=-==-:::-+:     :+        \n\033[22;70H         =:--    :-:   ==         \n\033[23;70H          :+*=+++==+*#-           \n";
                setColor(15);
                if (playerRand == 0) {//플레이어 크리티컬
                    monsterB.currentHeart -= player.attack * 2; // 몬스터 hp 감소
                    GotoXY(1, 1);
                    printf("치명적인 공격! 몬스터에게 %d 피해를 주었습니다!", player.attack * 2);
                }
                else {
                    monsterB.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("공격! 몬스터에게 %d 피해를 주었습니다!", player.attack);

                }
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2 * charging);
                    }
                    else {
                        player.currentHeart -= monsterB.attack * 2;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * charging;
                        charging = 1;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * charging);
                    }
                    else {
                        player.currentHeart -= monsterB.attack;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }
            }

            else if (monsterC.currentHeart > 0)
            {
                if (playerRand == 0) {//플레이어 크리티컬
                    monsterC.currentHeart -= player.attack * 2; // 몬스터 hp 감소

                    GotoXY(1, 1);
                    printf("치명적인 공격! 몬스터에게 %d 피해를 주었습니다!", player.attack * 2);
                }
                else {
                    monsterC.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("공격! 몬스터에게 %d 피해를 주었습니다!", player.attack);
                }
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2 * charging);
                    }
                    else {
                        player.currentHeart -= monsterC.attack * 2;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * charging;
                        charging = 1;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack* charging);
                    }
                    else {
                        player.currentHeart -= monsterC.attack;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(60, 1);;
                    printf("~기를 모으는 중~");
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }
            }
            //startTick = GetTickCount();
            //while (GetTickCount() - startTick < 500) {
            //    // 게임 루프가 멈추지 않도록 적절한 작업 수행 가능
            //}
        }
        void patternRecovery(int playerRand, int monsterRand, int& charging)
        {
            DWORD startTick = GetTickCount();

            if (monsterA.currentHeart > 0)
            {
                player.currentHeart += player.heart/5;
                GotoXY(1, 1);
                printf("회복! 플레이어가 체력%d 회복했습니다!", player.heart / 5);
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2 * charging);
                    }
                    else {
                        player.currentHeart -= monsterA.attack * 2;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * charging;
                        charging = 1;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * charging);
                    }
                    else {
                        player.currentHeart -= monsterA.attack;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }
            }
            else if (monsterB.currentHeart > 0)
            {
                player.currentHeart +=  player.heart / 5;
                GotoXY(1, 1);
                printf("회복! 플레이어가 체력%d 회복했습니다!", player.heart / 5);
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2 * charging);
                    }
                    else {
                        player.currentHeart -= monsterB.attack * 2;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * charging;
                        charging = 1;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * charging);
                    }
                    else {
                        player.currentHeart -= monsterB.attack;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }
            }
            else if (monsterC.currentHeart > 0)
            {
                player.currentHeart += player.heart / 5;
                GotoXY(1, 1);
                printf("회복! 플레이어가 체력%d 회복했습니다!", player.heart / 5);

                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//몬스터 크리티컬
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * 2 * charging;//차징 수 만큼 곱
                        charging = 1;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2 * charging);
                    }
                    else {
                        player.currentHeart -= monsterC.attack * 2;
                        GotoXY(1, 2);
                        printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * charging;
                        charging = 1;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack* charging);
                    }
                    else {
                        player.currentHeart -= monsterC.attack;
                        GotoXY(1, 2);
                        printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }
            }
        }
    }

}




