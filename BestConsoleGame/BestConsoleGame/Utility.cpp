#include "Utility.h"
#include <windows.h>

void GotoXY(int x, int y) // Ŀ�� ��ġ �̵� �Լ�
{
    COORD Cur = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur); // ���� ��ǥ�� �޾Ƽ� �ش� ��ǥ�� Ŀ�� �̵�
}
