#include "Utility.h"
#include <windows.h>

void GotoXY(int x, int y) // 커서 위치 이동 함수
{
    COORD Cur = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur); // 현재 좌표값 받아서 해당 좌표로 커서 이동
}
