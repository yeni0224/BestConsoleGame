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
            monsterC.image1 = "monsterC";
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
            GotoXY(80, 25);
            printf("����");
            printf(" ȸ��");
            printf(" ����");
        }

        void Battle1()
        {
            GotoXY(1, 7);
            printf("[ %d / %d ] \n", player.currentHeart, player.heart);
            GotoXY(1, 16);
            printf(player.image);

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
                std::cout << "                                                 ���� �Է� �� �ٽý���                                                 ";
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
            char symbols[] = { '>', ' ' }; // ������ ����� ����
            int index = 0;

            while (1)
            {
                int playerRand = rand() % 4; // 50% Ȯ�� (0 ~ 3)
                int monsterRand = rand() % 7; // 50% Ȯ�� (0 ~ 6)
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
                    std::cout << symbols[index] << std::flush; // ȭ�� �����
                    index = 1 - index; // 0�� 1�� �����ư��� ����
                    prevTick = nowTick;
                }

                if (global::input::IsLeftKeyOn())
                {
                    if (!WasLeftKeyPressed) // Ű�� ó�� ������ ���� ����
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
                    if (!WasRightKeyPressed) // Ű�� ó�� ������ ���� ����
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
                            global::hp = player.currentHeart;//���� �� ����hp����������
                            system("cls");//ȭ�� �ʱ�ȭ
                            startGame();//�κ�ȭ�� ���
                            flag = true;//��ü �ݺ��� ������ flag
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
                if (playerRand == 0) {//�÷��̾� ũ��Ƽ��
                    monsterA.currentHeart -= player.attack * 2; // ���� hp ����
                    GotoXY(5, 14);
                    printf("Critical hit!!");
                    startTick = GetTickCount();
                    while (GetTickCount() - startTick < 500) {
                        // ���� ������ ������ �ʵ��� ������ �۾� ���� ����
                    }
                    GotoXY(5, 14);
                    printf("              ");
                }
                else {
                    monsterA.currentHeart -= player.attack;
                }
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * 2 * charging;//��¡ �� ��ŭ ��
                        charging = 1;
                        GotoXY(60, 2);
                        printf("��¡Critical hit");
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
                        printf("��¡��             ");
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
                    printf("~�⸦ ������ ��~");
                }

            }

            else if (monsterB.currentHeart > 0)
            {
                setColor(12);
                std::cout << "\033[4;70H        -*+#*#@@#%##+==+==:       \n\033[5;70H    -=+=*#%%#%####%%%%@@#*#**=    \n\033[6;70H  -==%%=:                +*%%@+=  \n\033[7;70H:-@@%                      =@@*##:\n\033[8;70H==+=:=--:-:--::...:.-=---::.:-*###\n\033[9;70H=*+=...::-==:..=--...----:..-=+#%= \n\033[10;70H-=** %@@@@@@%+= **++@@@@@#%#:= :%=\n\033[11;70H:**=-%%@     @%  -=@      @@*- -#:\n\033[12;70H:*+: %@     @%---+=@@     @@:: *= \n\033[13;70H.+:   #%@@@#-==@%%%-+@@@%#+-: =+  \n\033[14;70H:==-: --::==: @@#@@*= :-    :-=+  \n\033[15;70H  =+--= =:    @@@@@+++*===-::*+:  \n\033[16;70H   :#@%+ :    #@@@*+=--- *=#%:    \n\033[17;70H    :+ @@+=  :@@@*.++*+%@==       \n\033[18;70H     ==-*%*+-===--=++##*@+-=       \n\033[19;70H      += =#%*#-=-=*+**+@+:-=       \n\033[20;70H      :=-==#%%=#=+-*@@#:  +       \n\033[21;70H       :=-==-:::-+:     :+        \n\033[22;70H         =:--    :-:   ==         \n\033[23;70H          :+*=+++==+*#-           \n";
                setColor(15);
                if (playerRand == 0) {//�÷��̾� ũ��Ƽ��
                    monsterB.currentHeart -= player.attack * 2; // ���� hp ����
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
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * 2 * charging;//��¡ �� ��ŭ ��
                        charging = 1;
                        printf("��¡Critical hit");
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
                        printf("��¡��             ");
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
                    printf("~�⸦ ������ ��~");
                }
            }

            else if (monsterC.currentHeart > 0)
            {
                if (playerRand == 0) {//�÷��̾� ũ��Ƽ��
                    monsterC.currentHeart -= player.attack * 2; // ���� hp ����
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
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * 2 * charging;//��¡ �� ��ŭ ��
                        charging = 1;
                        GotoXY(60, 2);
                        printf("��¡Critical hit");
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
                        printf("��¡��             ");
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
                    printf("~�⸦ ������ ��~");
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
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * 2 * charging;//��¡ �� ��ŭ ��
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
                    printf("~�⸦ ������ ��~");
                }
            }
            else if (monsterB.currentHeart > 0)
            {
                player.currentHeart += 10;
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * 2 * charging;//��¡ �� ��ŭ ��
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
                    printf("~�⸦ ������ ��~");
                }
            }
            else if (monsterC.currentHeart > 0)
            {
                player.currentHeart += 10;
                startTick = GetTickCount();
                while (GetTickCount() - startTick < 500) {}
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * 2 * charging;//��¡ �� ��ŭ ��
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
                    printf("~�⸦ ������ ��~");
                }
            }
        }
    }

}




