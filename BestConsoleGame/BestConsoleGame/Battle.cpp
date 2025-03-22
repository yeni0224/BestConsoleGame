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
    //플레이어 출력 좌표
    

    //텍스트
    player.image = "Player";
}

void MonsterA()
{
    //플레이어 출력 좌표
    

    //텍스트
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
    printf("공격");
    printf(" 방어");
    printf(" 도망");
}