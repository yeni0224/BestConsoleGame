#include <iostream>
#include <windows.h>
#include "InputSystem.h"

bool IsGameRun();
void UpdatePlayerPosition();
void UpdatePlayer();
void Render();
void GotoXY(int x, int y);
void DrawPlayer(bool bClear);

namespace global
{
    namespace time
    {
        ULONGLONG previousTime; //이전 시간
		ULONGLONG currentTime; //현재 시간
		ULONGLONG deltaTime; //시간차이

        int updateCount;
        int fixedUpdateCount;

        void InitTime() // 시간 초기화
        {
            currentTime = previousTime = GetTickCount64(); // 틱카운트 받아오기
        }

        void UpdateTime() // 
        {
            previousTime = currentTime; 
            currentTime = GetTickCount64();

            deltaTime = currentTime - previousTime; // 델타 타임 구하기
            //std::cout << deltaTime << std::endl;
        }

        ULONGLONG GetDeltaTime()
        {
     
            return deltaTime;
        }
    };

    COORD prePlayerPos;
    COORD curPlayerPos;

	SMALL_RECT consoleScreenSize; // 콘솔 화면 크기
    SMALL_RECT playerMovableRect = { 5, 5, 30, 30 }; // 플레이어 이동 가능 영역

    const int playerMoveSpeed = 50; // 플레이어 이동 속도 : 작을수록 빠름

    // 골드 시스템 추가
    int gold = 0;
    int hp = 100;
    int max_hp = 100;
    int atk = 10;
    ULONGLONG goldTimer = 0; // 골드 증가 타이머
};

void Render()
{
    GotoXY(72, 0);

    printf("현재 골드: %d  체력 : %d / %d  공격력 : %d", global::gold, global::hp, global::max_hp, global::atk);

    GotoXY(45, 0);
    printf("Player Position (%d, %d)", global::curPlayerPos.X, global::curPlayerPos.Y);

    if ((global::prePlayerPos.X != global::curPlayerPos.X) || (global::prePlayerPos.Y != global::curPlayerPos.Y))
    {
        DrawPlayer(true);
    }
}

void FixedUpdate()
{
    static ULONGLONG elapsedTime;
    elapsedTime += global::time::GetDeltaTime();

    while (elapsedTime >= 20)
    {
        global::time::fixedUpdateCount += 1;
        elapsedTime -= 20;
    }
}

void Update()
{
    global::time::updateCount += 1;
    UpdatePlayer();
}

// 플레이어 갱신
void UpdatePlayer()
{
    static ULONGLONG elapsedTime;
    elapsedTime += global::time::GetDeltaTime(); // 델타타임을 계속 더하기

    while (elapsedTime >= global::playerMoveSpeed) // elapsedTime이 플레이어 이동속도보다 빠르면 위치 업데이트  
    {                                              // playerMoveSpeed 숫자가 작을수록 빨리 업데이트 = 이동속도 증가
        UpdatePlayerPosition(); // 플레이어 위치를 커서 위치로 변경
        elapsedTime -= global::playerMoveSpeed; // 수치 초기화로 와일문 함수 종료
    }
}

void Clamp(short& n, short min, short max) // 이동 범위 제한
{
    if (n < min) n = min;
    if (n > max) n = max;
}

void UpdatePlayerPosition()
{
    global::prePlayerPos = global::curPlayerPos;

    if (global::input::IsUpKeyOn()) // 위키 누르면 진입
    {
        global::input::Set(global::input::UP_KEY_INDEX, false); // 위키 누름 상태를 false로 변경 = 이거 안하면 무한입력처리
        global::curPlayerPos.Y--; // y값 감소 = 위로 이동
        
        Clamp(global::curPlayerPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom); //벽 통과 못하게 하는거 이 함수 이용해서 처리
        
    }

    if (global::input::IsDownKeyOn())
    {
        global::input::Set(global::input::DOWN_KEY_INDEX, false);
        global::curPlayerPos.Y++;
        Clamp(global::curPlayerPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom);//벽 통과 못하게 하는거 이 함수 이용해서 처리
        
    }

    if (global::input::IsLeftKeyOn())
    {
        global::input::Set(global::input::LEFT_KEY_INDEX, false);
        global::curPlayerPos.X--;
        Clamp(global::curPlayerPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right);//벽 통과 못하게 하는거 이 함수 이용해서 처리
        
    }

    if (global::input::IsRightKeyOn())
    {
        global::input::Set(global::input::RIGHT_KEY_INDEX, false);
        global::curPlayerPos.X++;  
        Clamp(global::curPlayerPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right);//벽 통과 못하게 하는거 이 함수 이용해서 처리
        
    }

    
}

void ProcessInput() // InputSystem.cpp 코드 가져와서 사용
{
    global::input::UpdateInput(); // ESC,상,하,좌,우,스페이스바 입력 받기
    
}

void GotoXY(int x, int y) // 커서 위치 이동 함수
{
    COORD Cur = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur); // 현재 좌표값 받아서 해당 좌표로 커서 이동
}

void DrawPlayer(bool bClear) // 플레이어 출력 함수 매개변수로 
{
    if (bClear)
    {
        GotoXY(global::prePlayerPos.X, global::prePlayerPos.Y); // 이동 전 위치
        putchar(' '); // 이동했으니 공백 출력
    }

    GotoXY(global::curPlayerPos.X, global::curPlayerPos.Y); // 이동 후 위치
    putchar('#'); // 플레이어 위치이므로 #  >> 추후 다른 문자로 바꿀 예정
}

void DrawMovableRect() // 이동불가 영역 표시 = 벽
{
    for (int x = global::playerMovableRect.Left - 1; x < global::playerMovableRect.Right + 1; x++) // 이동 불가지점보다 1칸씩 밖에 @ 그리기 
    {
        GotoXY(x, global::playerMovableRect.Top - 1);
        putchar('@');
    }

    for (int x = global::playerMovableRect.Left - 1; x < global::playerMovableRect.Right + 1; x++) // 이동 불가지점보다 1칸씩 밖에 @ 그리기 
    {
        GotoXY(x, global::playerMovableRect.Bottom + 1);
        putchar('@');
    }

    for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom + 1; y++) // 이동 불가지점보다 1칸씩 밖에 @ 그리기 
    {
        GotoXY(global::playerMovableRect.Left - 1, y);
        putchar('@');
    }

    for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom + 1; y++) // 이동 불가지점보다 1칸씩 밖에 @ 그리기 
    {
        GotoXY(global::playerMovableRect.Right + 1, y);
        putchar('@');
    }
}

void startGame() {
    CONSOLE_CURSOR_INFO cursorInfo = { 0, }; // 커서 관련 정보 구조체
    cursorInfo.bVisible = 0; // 0 이면 커서 숨김, 1이면 커서 보임
    cursorInfo.dwSize = 1; // 커서 크기 1~100
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // 핸들 불러서 커서 

	CONSOLE_SCREEN_BUFFER_INFO csbi; // 콘솔 화면 버퍼 정보 구조체
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    /*COORD dwSize;                // 콘솔 버퍼의 크기 (가로, 세로)
    COORD dwCursorPosition;     // 현재 커서 위치 (X, Y)
    WORD  wAttributes;           // 현재 문자 색상 속성
    SMALL_RECT srWindow;        // 콘솔 창의 크기 (왼쪽, 위, 오른쪽, 아래)
    COORD dwMaximumWindowSize;  // 콘솔 창의 최대 크기 (가로, 세로)  << 구조체 멤버들임*/
    global::consoleScreenSize.Left = csbi.srWindow.Left; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 0
    global::consoleScreenSize.Right = csbi.srWindow.Right; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 0
    global::consoleScreenSize.Bottom = csbi.srWindow.Bottom; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 169
    global::consoleScreenSize.Top = csbi.srWindow.Top; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 50
    /*printf("콘솔 창의 위치:\n");
    printf("왼쪽: %d\n", csbi.srWindow.Left);
    printf("위쪽: %d\n", csbi.srWindow.Top);
    printf("오른쪽: %d\n", csbi.srWindow.Right);
    printf("아래쪽: %d\n", csbi.srWindow.Bottom);  // 콘솔창 및 버퍼 크기 확인 둘이 동일함  */
    global::playerMovableRect.Left = global::consoleScreenSize.Left + 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Right = global::consoleScreenSize.Right - 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Bottom = global::consoleScreenSize.Bottom - 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Top = global::consoleScreenSize.Top + 2; // 플레이어 이동 범위 제한
    /*printf("왼쪽: %d\n", global::playerMovableRect.Left);
    printf("위쪽: %d\n", global::playerMovableRect.Top);
    printf("오른쪽: %d\n", global::playerMovableRect.Right);
    printf("아래쪽: %d\n", global::playerMovableRect.Bottom);*/

    

    DrawMovableRect(); // 테두리 벽 생성

    global::prePlayerPos.X = 10;
    global::prePlayerPos.Y = 10;
    global::curPlayerPos.X = 10;
    global::curPlayerPos.Y = 10; // 플레이어 시작 위치

    DrawPlayer(false); // 플레이어 생성
}
int main()
{
    global::time::InitTime(); // 시간 초기화
    startGame(); //게임 시작, 기본 화면 구성
    
    
    while (IsGameRun()) // 게임 루프
    {
        global::time::UpdateTime();
        
        ProcessInput();
        FixedUpdate();
        Update();
        Render();
    }

   
    return 0;
}

bool IsGameRun() // 게임 루프
{
    return true;
}
