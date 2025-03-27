#include "Battle.h"
#include "Utility.h"
#include "Input_Sys.h"
#include "BestConsoleGame.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace global {
    namespace battle {
        PLAYER player{
        player.heart = global::max_hp ,
        player.currentHeart = global::hp ,
        player.attack = global::atk ,
        player.image = "\033[10;1H                    :@@@@*+                    \033[11;1H            ---%%#-====+%%*-            \033[12;1H          :***###+==+=======+@            \033[13;1H         +%###******=*+=======+-          \033[14;1H       :@#***********==*======@*          \033[15;1H       :@%**********+**+**++=-****+=      \033[16;1H        -+**%@@@%********+:::..=##+-      \033[17;1H         *@**********@@@@%**#@@*::        \033[18;1H         *@@@@@@@@@@@@@@:-@-+@@+          \033[19;1H         -*@@@@@@@@@@@@@=+@.:+-:          \033[20;1H          :#%@@@@@@@@@@#%#+...%+          \033[21;1H            =#@@@@@@*=====--+@           \033[22;1H     ::-*#%%%%%#####@@%####+=            \033[23;1H   :=+*#-======+**%@%*#@++*=-            \033[24;1H   +%*+=*==*==*==@@@#@%=..:.=%            \033[25;1H :@%**%@@#*=+*=%@****@%-...@#.@*..+@@%*   \033[26;1H :=*#%%*==#@####%%****@%-+*#....=@%=....@=  \033[27;1H+@##***#####%@@#****@++=@%=-:..:-+++...-=+ \033[28;1H+@@%*********#@#****@@@@+===--...@+.+-..*%  \033[29;1H :@%*********#@#**@@**#@=========@+..*@=#%  \033[30;1H :+*%%#*******%%%%%%%#**+**====+*@#+++++-  \033[31;1H    :::*@@@@@@@@##@#*#%#:..-%%%%@@-::      "
        };
        
        MONSTER monsterA{
            monsterA.heart = 100,
            monsterA.currentHeart = monsterA.heart,
            monsterA.attack = 10,
            monsterA.hpFlag = false,

            monsterA.image1 = "\033[4;65H          @@@@@@@@@@@@                     \n\033[5;65H      @@%%------------%%@                  \n\033[6;65H    @%=----::...::::-----#%                \n\033[7;65H   %+---===::....::::------*@              \n\033[8;65H  @=--======*##**=:::--------*@           \n\033[9;65H @@=%%%===%%%%######====------*@          \n\033[10;65H @-=#%%%:=+#%%%#=####+====------*@        \n\033[11;65H @--===-#=#*==+*####==++===-------+@      \n\033[12;65H@--====##-+%+==========-==----------*@    \n\033[13;65H@---===#%%+%+=#:=========-::::::------#   \n\033[14;65H@--=-===%%+%%=##========-::.::::-------@@ \n\033[15;65H@--=====#%#*%==*========-:..::----------@ \n\033[16;65H@--:::-------------::----:::..::---------@ \n\033[17;65H@-+++++++++++++++++++++++++::::::++++++--@ \n\033[18;65H  @+++++++++++++++++++++++++++++++++++++@ \n\033[19;65H     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   \n",
            monsterA.image2 = "\033[4;65H                  @@@@@@@@@@@@                     \n\033[5;65H             @@%%------------%%@                  \n\033[6;65H          @%=----::...::::-----#%                \n\033[7;65H        %+---===::....::::------*@              \n\033[8;65H       @=--======*##**=:::--------*@           \n\033[9;65H     @@=%%%===%%%%######====------*@          \n\033[10;65H    @-=#%%%:=+#%%%#=####+====------*@        \n\033[11;65H    @--===-#=#*==+*####==++===-------+@      \n\033[12;65H  @--====##-+%+==========-==----------*@    \n\033[13;65H @---===#%%+%+=#:=========-::::::------#   \n\033[14;65H@--=-===%%+%%=##========-::.::::-------@@ \n\033[15;65H@--=====#%#*%==*========-:..::----------@ \n\033[16;65H@--:::-------------::----:::..::---------@ \n\033[17;65H@-+++++++++++++++++++++++++::::::++++++--@ \n\033[18;65H  @+++++++++++++++++++++++++++++++++++++@ \n\033[19;65H     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   \n"
        };
        MONSTER monsterB{
            monsterB.heart = 200,
            monsterB.currentHeart = monsterB.heart,
            monsterB.attack = 20,
            monsterB.hpFlag = false,

            monsterB.image1 = "\033[4;70H        -*+#*#@@#%##+==+==:       \n\033[5;70H    -=+=*#%%#%####%%%%@@#*#**=    \n\033[6;70H  -==%%=:                +*%%@+=  \n\033[7;70H:-@@%                      =@@*##:\n\033[8;70H==+=:=--:-:--::...:.-=---::.:-*###\n\033[9;70H=*+=...::-==:..=--...----:..-=+#%= \n\033[10;70H-=** %@@@@@@%+= **++@@@@@#%#:= :%=\n\033[11;70H:**=-%%@@@@@@@%  -=@@@@@@@@@*- -#:\n\033[12;70H:*+: %@@@@@@@%---+=@@@@@@@@@:: *= \n\033[13;70H.+:   #%@@@#-==@%%%-+@@@%#+-: =+  \n\033[14;70H:==-: --::==: @@#@@*= :-    :-=+  \n\033[15;70H  =+--= =:    @@@@@+++*===-::*+:  \n\033[16;70H   :#@%+ :    #@@@*+=--- *=#%:    \n\033[17;70H    :+ @@+=  :@@@*.++*+%@==       \n\033[18;70H     ==-*%*+-===--=++##*@+-=       \n\033[19;70H      += =#%*#-=-=*+**+@+:-=       \n\033[20;70H      :=-==#%%=#=+-*@@#:  +       \n\033[21;70H       :=-==-:::-+:     :+        \n\033[22;70H         =:--    :-:   ==         \n\033[23;70H          :+*=+++==+*#-           \n",
            monsterB.image2 = "\033[4;70H        -*+#*#@@#%##+==+==:       \n\033[5;70H    -=+=*#%%#%####%%%%@@#*#**=    \n\033[6;70H  -==%%=:                +*%%@+=  \n\033[7;70H:-@@%                      =@@*##:\n\033[8;70H==+=:=--:-:--::...:.-=---::.:-*###\n\033[9;70H=*+=...::-==:..=--...----:..-=+#%= \n\033[10;70H-=** %@@@@@@%+= **++@@@@@#%#:= :%=\n\033[11;70H:**=-%%@     @%  -=@      @@*- -#:\n\033[12;70H:*+: %@     @%---+=@@     @@:: *= \n\033[13;70H.+:   #%@@@#-==@%%%-+@@@%#+-: =+  \n\033[14;70H:==-: --::==: @@#@@*= :-    :-=+  \n\033[15;70H  =+--= =:    @@@@@+++*===-::*+:  \n\033[16;70H   :#@%+ :    #@@@*+=--- *=#%:    \n\033[17;70H    :+ @@+=  :@@@*.++*+%@==       \n\033[18;70H     ==-*%*+-===--=++##*@+-=       \n\033[19;70H      += =#%*#-=-=*+**+@+:-=       \n\033[20;70H      :=-==#%%=#=+-*@@#:  +       \n\033[21;70H       :=-==-:::-+:     :+        \n\033[22;70H         =:--    :-:   ==         \n\033[23;70H          :+*=+++==+*#-           \n"
        };
        MONSTER monsterC{
            monsterC.heart = 300,
            monsterC.currentHeart = monsterC.heart,
            monsterC.attack = 30,
            monsterC.hpFlag = false,

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
                "\033[24;67H     +@+*@*.  =@#+++++++++++++%@=+@#+++++++++++++*@*\n",
            monsterC.image2 = "monsterC"
        };
        bool flag = false;
        bool clearflag = false;
        bool WasLeftKeyPressed = false;
        bool WasRightKeyPressed = false;
        bool WasSpaceKeyPressed = false;
        bool WasEnterKeyPressed = false;
        int x = 79;
        int pHp = 0;
        int mHp = 0;


        void Reset()
        {
            system("cls");
        }

        void BattleManager()
        {
            //DWORD startTick = GetTickCount();
            player.heart = global::max_hp;
            player.currentHeart = global::hp;
            player.attack = global::atk;
            monsterA.currentHeart = monsterA.heart;
            monsterB.currentHeart = monsterB.heart;
            monsterC.currentHeart = monsterC.heart;
            pHp = player.currentHeart;
            mHp = monsterA.currentHeart;

            BattleText1();
            while (1)
            {
                if (monsterA.currentHeart <= 0 && player.currentHeart > 0) {
                    monsterA.hpFlag = true;
                    UpdateQuestProgress_monsterAclear();
                }
                
                if (monsterB.currentHeart <= 0 && player.currentHeart > 0) {
                    monsterB.hpFlag = true;
                }
                
                    
                if (monsterC.currentHeart <= 0 && player.currentHeart > 0){
                        monsterC.hpFlag = true;
                }
            
                    

                if (player.currentHeart <= 0)
                {
                    system("cls");
                    ShowQuestMessage("�÷��̾ ����߽��ϴ�."); // �޽��� ��� �ð� ���� �Լ�
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
            printf("����");
            printf(" ȸ��");
            printf(" ����");
        }

        void Battle1()// �÷��̾� �̹��� ���
        {
            DWORD startTick = GetTickCount();

            GotoXY(10, 7);
            printf("[ %d / %d ] \n", player.currentHeart, player.heart);

            if (pHp > player.currentHeart)
            {
                setColor(12); std::cout << player.image; setColor(15);
            }
            if (pHp < player.currentHeart)
            {
                setColor(11); std::cout << player.image; setColor(15);
            }
            while (GetTickCount() - startTick < 500) {}
            std::cout << player.image;
            pHp = player.currentHeart;


        }
        void Battle2() // ���� �̹��� ���
        {
            global::input::UpdateInput();
            DWORD startTick = GetTickCount();

            if (!monsterA.hpFlag)
            {
                GotoXY(75, 0);
                printf("[ %d / %d ] \n", monsterA.currentHeart, monsterA.heart);
                if (mHp > monsterA.currentHeart)
                {
                    setColor(12); std::cout << monsterA.image2; setColor(15);
                }
                while (GetTickCount() - startTick < 500) {}
                setColor(10); std::cout << monsterA.image1; setColor(15);

            }
            else if (!monsterB.hpFlag)
            {
                GotoXY(75, 0);
                printf("[ %d / %d ] \n", monsterB.currentHeart, monsterB.heart);
                if (mHp > monsterB.currentHeart)
                {
                    setColor(12); std::cout << monsterB.image2; setColor(15);
                }
                while (GetTickCount() - startTick < 500) {}
                setColor(8); std::cout << monsterB.image1; setColor(15);
            }
            else if (!monsterC.hpFlag)
            {
                GotoXY(75, 0);
                printf("[ %d / %d ] \n", monsterC.currentHeart, monsterC.heart);
                if (mHp > monsterC.currentHeart)
                {
                    setColor(12); std::cout << monsterC.image1; setColor(15);
                }
                while (GetTickCount() - startTick < 500) {}
                setColor(10); std::cout << monsterC.image1; setColor(15);
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
                monsterA.hpFlag = true;
                monsterB.hpFlag = true;
                monsterC.hpFlag = true;
            }

        }
        void patternAttack(int playerRand, int monsterRand, int& charging);
        void patternRecovery(int playerRand, int monsterRand, int& charging);
        int charging = 1;
        void imageClear()
        {
            for (int y = 4; y <= 19; ++y) {
                // ���� ��ǥ (65, y)
                std::cout << "\033[" << y << ";" << 65 << "H"; // �̵��� ��ġ�� Ŀ�� ����

                // 65���� 100���� ���� ��� (�� 36���� ����)
                for (int x = 65; x <= 120; ++x) {
                    std::cout << " ";
                }
            }
        }
        

        void BattleText2()
        {
            ULONGLONG nowTick = GetTickCount64();
            ULONGLONG prevTick = nowTick;
            char symbols[] = { '>', ' ' }; // ������ ����� ����
            int index = 0;

            while (1)
            {
                int playerRand = rand() % 4; // 50% Ȯ�� (0 ~ 3)
                int monsterRand = rand() % 7; // 50% Ȯ�� (0 ~ 6)
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
                    if (!WasRightKeyPressed) // Ű�� ó�� ������ ���� ����
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

            if (!monsterA.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterA.currentHeart;
                if (playerRand == 0) {//�÷��̾� ũ��Ƽ��
                    monsterA.currentHeart -= player.attack * 2; // ���� hp ����
                    GotoXY(1,  1);
                    printf("ġ������ ����! ���Ϳ��� %d ���ظ� �־����ϴ�!", player.attack * 2);
                    if (monsterA.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }
                else {
                    monsterA.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("����! ���Ϳ��� %d ���ظ� �־����ϴ�!", player.attack);
                    if (monsterA.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }

                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * 2 * charging;//��¡ �� ��ŭ ��
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!" , monsterA.attack * 2 * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterA.attack * 2;
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * charging;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterA.attack;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("���Ͱ� �⸦ ��ҽ��ϴ�. ���� ���ش� �ι��Դϴ�!");
                }
            }

            else if (!monsterB.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterB.currentHeart;
                if (playerRand == 0) {//�÷��̾� ũ��Ƽ��
                    monsterB.currentHeart -= player.attack * 2; // ���� hp ����
                    GotoXY(1, 1);
                    printf("ġ������ ����! ���Ϳ��� %d ���ظ� �־����ϴ�!", player.attack * 2);
                    if (monsterB.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }
                else {
                    monsterB.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("����! ���Ϳ��� %d ���ظ� �־����ϴ�!", player.attack);
                    if (monsterB.currentHeart <= 0)
                    {
                        imageClear();
                    }

                }

                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * 2 * charging;//��¡ �� ��ŭ ��
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2 * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterB.attack * 2;
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * charging;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterB.attack;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("���Ͱ� �⸦ ��ҽ��ϴ�. ���� ���ش� �ι��Դϴ�!");
                }
            }

            else if (!monsterC.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterC.currentHeart;
                if (playerRand == 0) {//�÷��̾� ũ��Ƽ��
                    monsterC.currentHeart -= player.attack * 2; // ���� hp ����
                    GotoXY(1, 1);
                    printf("ġ������ ����! ���Ϳ��� %d ���ظ� �־����ϴ�!", player.attack * 2);
                    if (monsterC.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }
                else {
                    monsterC.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("����! ���Ϳ��� %d ���ظ� �־����ϴ�!", player.attack);
                    if (monsterC.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }

                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * 2 * charging;//��¡ �� ��ŭ ��
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2 * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterC.attack * 2;
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * charging;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack* charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterC.attack;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(60, 1);;
                    printf("~�⸦ ������ ��~");
                    GotoXY(1, 2);
                    printf("���Ͱ� �⸦ ��ҽ��ϴ�. ���� ���ش� �ι��Դϴ�!");
                }
            }
            //startTick = GetTickCount();
            //while (GetTickCount() - startTick < 500) {
            //    // ���� ������ ������ �ʵ��� ������ �۾� ���� ����
            //}
        }
        void patternRecovery(int playerRand, int monsterRand, int& charging)
        {
            //DWORD startTick = GetTickCount();

            if (!monsterA.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterA.currentHeart;
                if ((player.currentHeart + player.heart / 5) > player.heart) player.currentHeart = player.heart;
                else player.currentHeart += player.heart / 5;//ü��ȸ������ �ִ�ü������ ����
                
                GotoXY(1, 1);
                printf("ȸ��! �÷��̾ ü��%d ȸ���߽��ϴ�!", player.heart / 5);
                
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * 2 * charging;//��¡ �� ��ŭ ��
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2 * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterA.attack * 2;
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterA.attack * charging;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterA.attack;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("���Ͱ� �⸦ ��ҽ��ϴ�. ���� ���ش� �ι��Դϴ�!");
                }
            }
            else if (!monsterB.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterB.currentHeart;
                if ((player.currentHeart + player.heart / 5) > player.heart) player.currentHeart = player.heart;
                else player.currentHeart += player.heart / 5;//ü��ȸ������ �ִ�ü������ ����
                GotoXY(1, 1);
                printf("ȸ��! �÷��̾ ü��%d ȸ���߽��ϴ�!", player.heart / 5);
                
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * 2 * charging;//��¡ �� ��ŭ ��
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2 * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterB.attack * 2;
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterB.attack * charging;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterB.attack;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("���Ͱ� �⸦ ��ҽ��ϴ�. ���� ���ش� �ι��Դϴ�!");
                }
            }
            else if (!monsterC.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterC.currentHeart;
                if ((player.currentHeart + player.heart / 5) > player.heart) player.currentHeart = player.heart;
                else player.currentHeart += player.heart / 5;//ü��ȸ������ �ִ�ü������ ����
                GotoXY(1, 1);
                printf("ȸ��! �÷��̾ ü��%d ȸ���߽��ϴ�!", player.heart / 5);

                
                if (monsterRand == 0) {//���� ũ��Ƽ��
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * 2 * charging;//��¡ �� ��ŭ ��
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2 * charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterC.attack * 2;
                        GotoXY(1, 2);
                        printf("ġ������ ����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack * 2);
                    }

                }
                else if (monsterRand < 5) {
                    if (charging > 1) {
                        player.currentHeart -= monsterC.attack * charging;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack* charging);
                        charging = 1;
                    }
                    else {
                        player.currentHeart -= monsterC.attack;
                        GotoXY(1, 2);
                        printf("����! �÷��̾ %d ���ظ� �޾ҽ��ϴ�!", monsterA.attack);
                    }
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("���Ͱ� �⸦ ��ҽ��ϴ�. ���� ���ش� �ι��Դϴ�!");
                }
            }
        }
    }

}




