#include "Battle.h"
#include "Utility.h"
#include "InputSystem.h"
#include <iostream>
#include <cstdlib>

PLAYER player;
MONSTERA monsterA;

void Reset()
{
    system("cls");
    Player();
    MonsterA();
}

void Player()
{
    //�÷��̾� ��� ��ǥ
    

    //�ؽ�Ʈ
    player.image = "Player";
}

void MonsterA()
{
    //�÷��̾� ��� ��ǥ
    

    //�ؽ�Ʈ
    monsterA.image = "monsterA";

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
void BattleText()
{
    GotoXY(80, 25);
    printf("����");
    printf(" ���");
    printf(" ����");
}