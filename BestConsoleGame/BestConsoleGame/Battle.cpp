#include "Battle.h"
#include "Utility.h"
#include "Input_Sys.h"
#include "BestConsoleGame.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace global {
    namespace battle {

        std::string battleMessage = "";
        PLAYER player{
        player.heart = global::max_hp ,
        player.currentHeart = global::hp ,
        player.attack = global::atk ,
        player.image = "\033[10;1H                    :@@@@*+                    \033[11;1H            ---%%#-====+%%*-            \033[12;1H          :***###+==+=======+@            \033[13;1H         +%###******=*+=======+-          \033[14;1H       :@#***********==*======@*          \033[15;1H       :@%**********+**+**++=-****+=      \033[16;1H        -+**%@@@%********+:::..=##+-      \033[17;1H         *@**********@@@@%**#@@*::        \033[18;1H         *@@@@@@@@@@@@@@:-@-+@@+          \033[19;1H         -*@@@@@@@@@@@@@=+@.:+-:          \033[20;1H          :#%@@@@@@@@@@#%#+...%+          \033[21;1H            =#@@@@@@*=====--+@           \033[22;1H     ::-*#%%%%%#####@@%####+=            \033[23;1H   :=+*#-======+**%@%*#@++*=-            \033[24;1H   +%*+=*==*==*==@@@#@%=..:.=%            \033[25;1H :@%**%@@#*=+*=%@****@%-...@#.@*..+@@%*   \033[26;1H :=*#%%*==#@####%%****@%-+*#....=@%=....@=  \033[27;1H+@##***#####%@@#****@++=@%=-:..:-+++...-=+ \033[28;1H+@@%*********#@#****@@@@+===--...@+.+-..*%  \033[29;1H :@%*********#@#**@@**#@=========@+..*@=#%  \033[30;1H :+*%%#*******%%%%%%%#**+**====+*@#+++++-  \033[31;1H    :::*@@@@@@@@##@#*#%#:..-%%%%@@-::      "
        };
        
        MONSTER monsterA{
            monsterA.heart = 200,
            monsterA.currentHeart = monsterA.heart,
            monsterA.attack = 10,
            monsterA.hpFlag = false,

            monsterA.image1 = "\033[4;65H          @@@@@@@@@@@@                     \n\033[5;65H      @@%%------------%%@                  \n\033[6;65H    @%=----::...::::-----#%                \n\033[7;65H   %+---===::....::::------*@              \n\033[8;65H  @=--======*##**=:::--------*@           \n\033[9;65H @@=%%%===%%%%######====------*@          \n\033[10;65H @-=#%%%:=+#%%%#=####+====------*@        \n\033[11;65H @--===-#=#*==+*####==++===-------+@      \n\033[12;65H@--====##-+%+==========-==----------*@    \n\033[13;65H@---===#%%+%+=#:=========-::::::------#   \n\033[14;65H@--=-===%%+%%=##========-::.::::-------@@ \n\033[15;65H@--=====#%#*%==*========-:..::----------@ \n\033[16;65H@--:::-------------::----:::..::---------@ \n\033[17;65H@-+++++++++++++++++++++++++::::::++++++--@ \n\033[18;65H  @+++++++++++++++++++++++++++++++++++++@ \n\033[19;65H     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   \n",
            monsterA.image2 = "\033[4;65H                  @@@@@@@@@@@@                     \n\033[5;65H             @@%%------------%%@                  \n\033[6;65H          @%=----::...::::-----#%                \n\033[7;65H        %+---===::....::::------*@              \n\033[8;65H       @=--======*##**=:::--------*@           \n\033[9;65H     @@=%%%===%%%%######====------*@          \n\033[10;65H    @-=#%%%:=+#%%%#=####+====------*@        \n\033[11;65H    @--===-#=#*==+*####==++===-------+@      \n\033[12;65H  @--====##-+%+==========-==----------*@    \n\033[13;65H @---===#%%+%+=#:=========-::::::------#   \n\033[14;65H@--=-===%%+%%=##========-::.::::-------@@ \n\033[15;65H@--=====#%#*%==*========-:..::----------@ \n\033[16;65H@--:::-------------::----:::..::---------@ \n\033[17;65H@-+++++++++++++++++++++++++::::::++++++--@ \n\033[18;65H  @+++++++++++++++++++++++++++++++++++++@ \n\033[19;65H     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   \n"
        };
        MONSTER monsterB{
            monsterB.heart = 300,
            monsterB.currentHeart = monsterB.heart,
            monsterB.attack = 35,
            monsterB.hpFlag = false,

            monsterB.image1 = "\033[4;70H        -*+#*#@@#%##+==+==:       \n\033[5;70H    -=+=*#%%#%####%%%%@@#*#**=    \n\033[6;70H  -==%%=:                +*%%@+=  \n\033[7;70H:-@@%                      =@@*##:\n\033[8;70H==+=:=--:-:--::...:.-=---::.:-*###\n\033[9;70H=*+=...::-==:..=--...----:..-=+#%= \n\033[10;70H-=** %@@@@@@%+= **++@@@@@#%#:= :%=\n\033[11;70H:**=-%%@@@@@@@%  -=@@@@@@@@@*- -#:\n\033[12;70H:*+: %@@@@@@@%---+=@@@@@@@@@:: *= \n\033[13;70H.+:   #%@@@#-==@%%%-+@@@%#+-: =+  \n\033[14;70H:==-: --::==: @@#@@*= :-    :-=+  \n\033[15;70H  =+--= =:    @@@@@+++*===-::*+:  \n\033[16;70H   :#@%+ :    #@@@*+=--- *=#%:    \n\033[17;70H    :+ @@+=  :@@@*.++*+%@==       \n\033[18;70H     ==-*%*+-===--=++##*@+-=       \n\033[19;70H      += =#%*#-=-=*+**+@+:-=       \n\033[20;70H      :=-==#%%=#=+-*@@#:  +       \n\033[21;70H       :=-==-:::-+:     :+        \n\033[22;70H         =:--    :-:   ==         \n\033[23;70H          :+*=+++==+*#-           \n",
            monsterB.image2 = "\033[4;70H        -*+#*#@@#%##+==+==:       \n\033[5;70H    -=+=*#%%#%####%%%%@@#*#**=    \n\033[6;70H  -==%%=:                +*%%@+=  \n\033[7;70H:-@@%                      =@@*##:\n\033[8;70H==+=:=--:-:--::...:.-=---::.:-*###\n\033[9;70H=*+=...::-==:..=--...----:..-=+#%= \n\033[10;70H-=** %@@@@@@%+= **++@@@@@#%#:= :%=\n\033[11;70H:**=-%%@     @%  -=@      @@*- -#:\n\033[12;70H:*+: %@     @%---+=@@     @@:: *= \n\033[13;70H.+:   #%@@@#-==@%%%-+@@@%#+-: =+  \n\033[14;70H:==-: --::==: @@#@@*= :-    :-=+  \n\033[15;70H  =+--= =:    @@@@@+++*===-::*+:  \n\033[16;70H   :#@%+ :    #@@@*+=--- *=#%:    \n\033[17;70H    :+ @@+=  :@@@*.++*+%@==       \n\033[18;70H     ==-*%*+-===--=++##*@+-=       \n\033[19;70H      += =#%*#-=-=*+**+@+:-=       \n\033[20;70H      :=-==#%%=#=+-*@@#:  +       \n\033[21;70H       :=-==-:::-+:     :+        \n\033[22;70H         =:--    :-:   ==         \n\033[23;70H          :+*=+++==+*#-           \n"
        };
        MONSTER monsterC{
            monsterC.heart = 500,
            monsterC.currentHeart = monsterC.heart,
            monsterC.attack = 50,
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
            monsterC.image2 = 
                "\033[12;45H     %%%%##%@@\n"
                "\033[13;45H    @@#+++++@@\n"
                "\033[14;45H    @@%%%%%%@@\n"
                "\033[15;45H     @@   @@\n"
                "\033[16;45H    @@@    @@@ *****\n"
                "\033[17;45H  @@@@      @@@@   **\n"
                "\033[18;45H @@@@         @@@@\n"
                "\033[19;45H@@  @            @@@  *\n"
                "\033[20;45H@@            @ @@@  **\n"
                "\033[21;45H@@             @@@ ***\n"
                "\033[22;45H @@@@@@@@@@@@@@\n"

        };
        bool flag = false;
        bool clearflag = false;
        bool WasLeftKeyPressed = false;
        bool WasRightKeyPressed = false;
        bool WasSpaceKeyPressed = false;
        bool WasEnterKeyPressed = false;
        bool poisonFlag = false;
        int count = 0;
        int x = 80;
        int y = 27;
        int pHp = 0;
        int mHp = 0;
        int charging = 1;


        void Reset()
        {
            count = 0;
            x = 80;
            y = 27;
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
            ///////////////////////////////////////
            for (int x = 80; x < 96; x++) {
                GotoXY(x, 26);
                printf("-");
            }
            for (int x = 79; x < 97; x+=17) {
                GotoXY(x, 27);
                printf("|");
            }
            for (int x = 80; x < 96; x ++) {
                GotoXY(x, 28);
                printf("-");
            }
            for (int y = 26; y <= 28; y +=2)
            {
                for (int x = 79; x < 97; x += 17)
                {
                    GotoXY(x, y);
                    printf("+");
                }
            }
            BattleText1();
            while (1)
            {
                if (monsterA.currentHeart <= 0 && player.currentHeart > 0) {
                    GotoXY(1, 1);
                    for (int i = 0; i < 49; i++) printf(" ");
                    GotoXY(1, 2);
                    for (int i = 0; i < 49; i++) printf(" ");
                    monsterA.hpFlag = true;
                    charging = 1;
                }
                
                if (monsterB.currentHeart <= 0 && player.currentHeart > 0) {
                    GotoXY(1, 1);
                    for (int i = 0; i < 49; i++) printf(" ");
                    GotoXY(1, 2);
                    for (int i = 0; i < 49; i++) printf(" ");
                    monsterB.hpFlag = true;
                    charging = 1;
                }
                
                    
                if (monsterC.currentHeart <= 0 && player.currentHeart > 0){
                    monsterC.hpFlag = true;
                    global::gamestartflag = false;
                    charging = 1;
                }
            
                    

                if (player.currentHeart <= 0)
                {
                    system("cls");
                    global::hp = 10;
                    ShowQuestMessage("플레이어가 사망했습니다."); // 메시지 출력 시간 조절 함수
                    global::GameSound::StopBGM();
                    startGame();//로비화면 출력
                    global::GameSound::PlayBGM(0);
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
            GotoXY(81, 27);
            printf("공격");
            printf(" 회복");
            printf(" 도망");
        }

        void Battle1()// 플레이어 이미지 출력
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

            
            pHp = player.currentHeart;

            if (count == 0)    poisonFlag = false;
            
            if (poisonFlag)
            {
                setColor(5); std::cout << player.image; setColor(15);
            }
            else std::cout << player.image;

        }
        void Battle2() // 몬스터 이미지 출력
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
                setColor(13); std::cout << monsterC.image1; setColor(15);
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

                monsterA.hpFlag = false;
                monsterB.hpFlag = false;
                monsterC.hpFlag = false;
                monsterA.currentHeart = monsterA.heart;
                monsterB.currentHeart = monsterB.heart;
                monsterC.currentHeart = monsterC.heart;
                global::gold = 0;
                global::atk = 10;
                global::hp = 100;
                global::max_hp = 100;
                
            }

        }
        void patternAttack(int playerRand, int monsterRand, int bossRand, int& charging);
        void patternRecovery(int playerRand, int monsterRand, int bossRand, int& charging);
        
        void imageClear()
        {
            for (int y = 4; y <= 25; ++y) {
                // 시작 좌표 (65, y)
                std::cout << "\033[" << y << ";" << 65 << "H"; // 이동할 위치로 커서 설정

                // 65부터 120까지 공백 출력
                for (int x = 65; x <= 120; ++x) {
                    std::cout << " ";
                }
            }
        }
        void imageClear2()
        {
            for (int y = 12; y <= 22; ++y) {
                std::cout << "\033[" << y << ";" << 45 << "H"; // 이동할 위치로 커서 설정

                for (int x = 45; x <= 66; ++x) {
                    std::cout << " ";
                }
            }
        }
        

        void BattleText2()
        {
            ULONGLONG nowTick = GetTickCount64();
            ULONGLONG prevTick = nowTick;
            char symbols[] = { '>', ' ' }; // 번갈아 출력할 문자
            int index = 0;

            while (1)
            {
                int playerRand = rand() % 4; // (0 ~ 3)
                int monsterRand = rand() % 7; // (0 ~ 6)
                int bossRand = rand() % 10; // (0 ~ 9)
                GotoXY(x, y);
                global::input::UpdateInput();
                nowTick = GetTickCount64();
                ULONGLONG elapsedTick = nowTick - prevTick;
                
                if (clearflag)
                {
                    x = 45;
                    y = 20;
                    if (global::input::IsEnterKeyOn())
                    {
                        if (!WasEnterKeyPressed)
                        {
                            global::input::Set(global::input::Enter_KEY_INDEX, false);
                            WasEnterKeyPressed = true;
                            system("cls");
                            resetCounter();
                            OpeningTitle();
                            while(true)
                            {
                                ProcessInput();
                                MoveSelectMenu();
                                FixedUpdate();
                                RenderOpening();
                                global::GameSound::SoundUpdate();
                                if (global::gamestartflag == true)
                                {
                                    break;
                                }
                            }
                            system("cls");
                            global::GameSound::StopBGM();
                            startGame();//로비화면 출력
                            global::GameSound::PlayBGM(0);
                            break;
                        }
                    }
                    else
                    {
                        WasEnterKeyPressed = false;
                    }
                }

                if (elapsedTick >= 500 && elapsedTick <= 999)
                {
                    GotoXY(x, y);
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
                        GotoXY(x, y);
                        std::cout << symbols[1];

                        if (x > 80) x -= 5;
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
                        GotoXY(x, y);
                        std::cout << symbols[1];

                        if (x < 90) x += 5;
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
                        if (x == 90) // 도망
                        {
                            global::hp = player.currentHeart;//도망 시 현재hp가져가도록
                            system("cls");//화면 초기화
                            global::GameSound::StopBGM();
                            startGame();//로비화면 출력
                            global::GameSound::PlayBGM(0);

                            flag = true;//전체 반복문 나가는 flag
                            UpdateQuestProgress_monsterAclear();
                            UpdateQuestProgress_monsterBclear();
                            
                            break;
                        }
                        if (x == 80)
                        {
                            patternAttack(playerRand, monsterRand, bossRand, charging); // 공격
                            GotoXY(5, 5);
                            break;
                        }
                        global::input::Set(global::input::Space_KEY_INDEX, false);
                        WasSpaceKeyPressed = true;
                        if (x == 85) // 회복
                        {
                            patternRecovery(playerRand, monsterRand, bossRand, charging);
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
        void patternAttack(int playerRand, int monsterRand, int bossRand, int& charging)
        {
            ULONGLONG nowTick = GetTickCount64();

            if (!monsterA.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterA.currentHeart;
                if (playerRand == 0) {//플레이어 크리티컬
                    global::GameSound::PlaySFX(4);
                    monsterA.currentHeart -= player.attack * 2; // 몬스터 hp 감소
                    GotoXY(1,  1);
                    printf("치명적인 공격! 몬스터에게 %d 피해를 주었습니다!", player.attack * 2);
                    if (monsterA.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }
                else {
                    monsterA.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("공격! 몬스터에게 %d 피해를 주었습니다!", player.attack);
                    if (monsterA.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }

                if (monsterRand < 1) {//몬스터 크리티컬
                    player.currentHeart -= monsterA.attack * 2 * charging;//차징 수 만큼 곱
                    GotoXY(1, 2);
                    printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2 * charging);
                    charging = 1;

                }
                else if (monsterRand < 6) {
                    player.currentHeart -= monsterA.attack * charging;
                    GotoXY(1, 2);
                    printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * charging);
                    charging = 1;
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }
            }

            else if (!monsterB.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterB.currentHeart;
                if (playerRand == 0) {//플레이어 크리티컬
                    global::GameSound::PlaySFX(4);
                    monsterB.currentHeart -= player.attack * 2; // 몬스터 hp 감소
                    GotoXY(1, 1);
                    printf("치명적인 공격! 몬스터에게 %d 피해를 주었습니다!", player.attack * 2);
                    if (monsterB.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }
                else {
                    monsterB.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("공격! 몬스터에게 %d 피해를 주었습니다!", player.attack);
                    if (monsterB.currentHeart <= 0)
                    {
                        imageClear();
                    }

                }

                if (monsterRand < 1) {//몬스터 크리티컬
                    player.currentHeart -= monsterB.attack * 2 * charging;//차징 수 만큼 곱
                    GotoXY(1, 2);
                    printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterB.attack * 2 * charging);
                    charging = 1;

                }
                else if (monsterRand < 6) {
                    player.currentHeart -= monsterB.attack * charging;
                    GotoXY(1, 2);
                    printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterB.attack * charging);
                    charging = 1;
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }
            }

            else if (!monsterC.hpFlag)
            {
                count--;
                if (count > 0)
                {
                    GotoXY(1, 3);
                    printf("독이 묻어 %d턴 동안 %d 피해를 받습니다", count, player.heart / 25);
                }                
                if (poisonFlag)
                {
                    player.currentHeart -= player.heart / 25;
                }
                pHp = player.currentHeart;
                mHp = monsterC.currentHeart;
                if (playerRand == 0) {//플레이어 크리티컬
                    global::GameSound::PlaySFX(4);
                    monsterC.currentHeart -= player.attack * 2; // 몬스터 hp 감소
                    GotoXY(1, 1);
                    printf("치명적인 공격! 몬스터에게 %d 피해를 주었습니다!", player.attack * 2);
                    if (monsterC.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }
                else {
                    monsterC.currentHeart -= player.attack;
                    GotoXY(1, 1);
                    printf("공격! 몬스터에게 %d 피해를 주었습니다!", player.attack);
                    if (monsterC.currentHeart <= 0)
                    {
                        imageClear();
                    }
                }

                if (bossRand < 2) {//몬스터 크리티컬
                    player.currentHeart -= monsterC.attack * 2 * charging;//차징 수 만큼 곱
                    GotoXY(1, 2);
                    printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterC.attack * 2 * charging);
                    charging = 1;

                }
                else if (bossRand < 6) {
                    player.currentHeart -= monsterC.attack * charging;
                    GotoXY(1, 2);
                    printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterC.attack* charging);
                    charging = 1;
                }
                else if(bossRand < 7){
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 두배입니다!");
                }
                else if (bossRand < 8) {
                    player.currentHeart -= monsterC.attack / 2 * charging;
                    GotoXY(1, 2);
                    printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterC.attack / 2 * charging);
                    GotoXY(1, 3);
                    printf("독이 묻어 매턴 %d 피해를 받습니다", player.heart / 25);
                    setColor(13);
                    std::cout << monsterC.image2;
                    setColor(15);
                    while (GetTickCount64() - nowTick < 500) {}
                    imageClear2();
                    poisonFlag = true;
                    count = 3;
                    charging = 1;
                }
                else {
                    player.currentHeart -= monsterC.attack * 3 * charging;
                    GotoXY(1, 2);
                    printf("속성피해! 플레이어가 %d 피해를 받았습니다!", monsterC.attack * 3 * charging);
                    charging = 1;
                    for (int i = 1; i < 16; i++)
                    {
                        while (true) {
                            if (GetTickCount64() - nowTick > 50) {
                                setColor(i);
                                std::cout << monsterC.image1;
                                nowTick = GetTickCount64();
                                break;
                            }
                        }
                    }
                }
            }
            //startTick = GetTickCount();
            //while (GetTickCount() - startTick < 500) {
            //    // 게임 루프가 멈추지 않도록 적절한 작업 수행 가능
            //}
        }
        void patternRecovery(int playerRand, int monsterRand, int bossRand, int& charging)
        {
            ULONGLONG nowTick = GetTickCount64();
            if (!monsterA.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterA.currentHeart;
                if ((player.currentHeart + player.heart / 5) > player.heart) player.currentHeart = player.heart;
                else player.currentHeart += player.heart / 5;//체력회복량을 최대체력으로 제한
                
                GotoXY(1, 1);
                printf("회복! 플레이어가 체력%d 회복했습니다!", player.heart / 5);
                
                if (monsterRand < 1) {//몬스터 크리티컬
                    player.currentHeart -= monsterA.attack * 2 * charging;//차징 수 만큼 곱
                    GotoXY(1, 2);
                    printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * 2 * charging);
                    charging = 1;
                }
                else if (monsterRand < 5) {
                    player.currentHeart -= monsterA.attack * charging;
                    GotoXY(1, 2);
                    printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterA.attack * charging);
                    charging = 1;
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 %d배입니다!", charging);
                }
            }
            else if (!monsterB.hpFlag)
            {
                pHp = player.currentHeart;
                mHp = monsterB.currentHeart;
                if ((player.currentHeart + player.heart / 5) > player.heart) player.currentHeart = player.heart;
                else player.currentHeart += player.heart / 5;//체력회복량을 최대체력으로 제한
                GotoXY(1, 1);
                printf("회복! 플레이어가 체력%d 회복했습니다!", player.heart / 5);
                
                if (monsterRand < 1) {//몬스터 크리티컬
                    player.currentHeart -= monsterB.attack * 2 * charging;//차징 수 만큼 곱
                    GotoXY(1, 2);
                    printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterB.attack * 2 * charging);
                    charging = 1;
                }
                else if (monsterRand < 5) {
                    player.currentHeart -= monsterB.attack * charging;
                    GotoXY(1, 2);
                    printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterB.attack * charging);
                    charging = 1;
                }
                else {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 %d배입니다!", charging);
                }
            }
            else if (!monsterC.hpFlag)
            {
                count--;
                if (count > 0)
                {
                    GotoXY(1, 3);
                    printf("독이 묻어 %d턴 동안 %d 피해를 받습니다", count, player.heart / 25);
                }
                if (poisonFlag)
                {
                    player.currentHeart -= player.heart / 25;
                }
                pHp = player.currentHeart;
                mHp = monsterC.currentHeart;
                if ((player.currentHeart + player.heart / 5) > player.heart) player.currentHeart = player.heart;
                else player.currentHeart += player.heart / 5;//체력회복량을 최대체력으로 제한
                GotoXY(1, 1);
                printf("회복! 플레이어가 체력%d 회복했습니다!", player.heart / 5);

                
                if (bossRand < 2) {//몬스터 크리티컬
                    player.currentHeart -= monsterC.attack * 2 * charging;//차징 수 만큼 곱
                    GotoXY(1, 2);
                    printf("치명적인 피해! 플레이어가 %d 피해를 받았습니다!", monsterC.attack * 2 * charging);
                    charging = 1;
                }
                else if (bossRand < 6) {
                    player.currentHeart -= monsterC.attack * charging;
                    GotoXY(1, 2);
                    printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterC.attack* charging);
                    charging = 1;
                }
                else if (bossRand < 7) {
                    charging += 1;
                    GotoXY(1, 2);
                    printf("몬스터가 기를 모았습니다. 다음 피해는 %d배입니다!", charging);
                }
                else if (bossRand < 8) {
                    player.currentHeart -= monsterC.attack / 2 * charging;
                    count = 3;
                    GotoXY(1, 2);
                    printf("피해! 플레이어가 %d 피해를 받았습니다!", monsterC.attack / 2 * charging);
                    GotoXY(1, 3);
                    printf("독이 묻어 %d턴 %d 피해를 받습니다", count, player.heart / 25);
                    setColor(13);
                    std::cout << monsterC.image2;
                    setColor(15);
                    while (GetTickCount64() - nowTick < 500) {}
                    imageClear2();
                    poisonFlag = true;
                    charging = 1;
                }
                else {
                    player.currentHeart -= monsterC.attack * 3 * charging;
                    GotoXY(1, 2);
                    printf("속성피해! 플레이어가 %d 피해를 받았습니다!", monsterC.attack * 3 * charging);
                    charging = 1;
                    for (int i = 1; i < 16; i++)
                    {
                        while (true) {
                            if (GetTickCount64() - nowTick > 50) {
                                setColor(i);
                                std::cout << monsterC.image1;
                                nowTick = GetTickCount64();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

}




