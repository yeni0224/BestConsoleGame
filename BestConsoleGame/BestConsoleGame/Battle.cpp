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
    //�ؽ�Ʈ
    player.image = "Player";
}

void MonsterA()
{

    //�ؽ�Ʈ
    monsterA.image = "monsterA";

}

void MonsterB()
{

    //�ؽ�Ʈ
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
    printf("����");
    printf(" ���");
    printf(" ����");
}
void BattleText2()
{
    short newX = 79;
    short prevX = newX;
    ULONGLONG nowTick = GetTickCount64();
    ULONGLONG prevTick = nowTick;

    bool isLeftPressed = false;  // ���� Ű�� ���ȴ��� ����
    bool isRightPressed = false; // ������ Ű�� ���ȴ��� ����

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

        // ���� �̵� (�� ���� ����)
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            if (!isLeftPressed) // ���� �����ӿ��� ���� �� ���� ���� ����
            {
                isLeftPressed = true;
                if (newX > 79) newX -= 5;
            }
        }
        else
        {
            isLeftPressed = false; // Ű�� ���� �ٽ� ���� �����ϵ��� �ʱ�ȭ
        }

        // ������ �̵� (�� ���� ����)
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
        
        Sleep(50); // �ʹ� ���� ���� ���� ����
    }
}

