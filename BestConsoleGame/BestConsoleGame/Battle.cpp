#include "Battle.h"
#include "Utility.h"
#include "InputSystem.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>


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
    //int attack = global::atk;
    //텍스트
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
    GotoXY(1, 20);
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
    short newX = 79;
    short prevX = newX;
    ULONGLONG nowTick = GetTickCount64();
    ULONGLONG prevTick = nowTick;

    bool isLeftPressed = false;  // 왼쪽 키가 눌렸는지 여부
    bool isRightPressed = false; // 오른쪽 키가 눌렸는지 여부

    while (1)
    {
        nowTick = GetTickCount64();
        ULONGLONG elapsedTick = nowTick - prevTick;

        GotoXY(prevX, 25);
        printf(" ");

       /* GotoXY(newX, 25);
        printf(">");*/

        prevX = newX;

        if (elapsedTick >= 500 && elapsedTick <= 999)
        {
            GotoXY(newX, 25);
            printf(">");
        }
        if (elapsedTick >= 1000)
        {
            GotoXY(newX, 25);
            printf(" ");
            prevTick = nowTick;
        }

        // 왼쪽 이동 (한 번만 감지)
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            if (!isLeftPressed) // 이전 프레임에서 누른 적 없을 때만 실행
            {
                isLeftPressed = true;
                if (newX > 79) newX -= 5;
            }
        }
        else
        {
            isLeftPressed = false; // 키를 떼면 다시 감지 가능하도록 초기화
        }

        // 오른쪽 이동 (한 번만 감지)
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            if (!isRightPressed)
            {
                isRightPressed = true;
                if (newX < 89) newX += 5;
            }
        }
        else
        {
            isRightPressed = false;
        }
        
        Sleep(50); // 너무 빠른 루프 실행 방지
    }
}

