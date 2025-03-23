#include <iostream>
#include <windows.h>
#include "../BestConsoleGame/Input_Sys.h"
#include "../BestConsoleGame/Utility.h"
#include "../BestConsoleGame/Battle.h"


bool IsGameRun();
void UpdatePlayerPosition();
void UpdatePlayer();
void Render();
void GotoXY(int x, int y);
void DrawPlayer(bool bClear);
void UpdateGoldMining();
bool IsInsideZone(COORD pos, SMALL_RECT zone);
void UpdateAttackUpgrade();
void UpdateHpUpgrade();

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

    const int playerMoveSpeed = 20; // 플레이어 이동 속도 : 작을수록 빠름

    // 골드 시스템 추가
    int gold = 0;
    int hp = 100;
    int max_hp = 100;
    int atk = 10;
    ULONGLONG goldTimer = 0; // 골드 증가 타이머
    static int purchaseCount = 0;  // 구매 횟수 (최대 3회)

    int goldCounter = 0;      // 골드 카운트 (0~10)
    bool isMining = false;    // 채굴 상태 여부
    bool isUpgrading = false; // 강화 진행 여부
    bool isReady = false;     // 배틀 시작 여부
    bool WasSpaceKeyPressed = false; // 스페이스바 눌렸는지 체크


    SMALL_RECT goldZone = { 45, 21, 79, 27 }; // 골드존 영역 (좌, 상, 우, 하)
    SMALL_RECT homeZone = { 2, 2, 29, 27 }; // 집 영역
    SMALL_RECT atkZone = { 45, 2, 61, 8 }; // 공격력 강화소 영역
    SMALL_RECT HpZone = { 67, 2, 83, 8 }; // 공격력 강화소 영역
    SMALL_RECT battleZone = { 97, 13, 111, 16 }; // 배틀 영역 30 20 39 27
    SMALL_RECT AutoMoneyBuyZone = { 30, 20, 39, 27 }; // 오토 머니 구매 영역

};

void setColor(int color) { // 컬러 변경
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Render()
{
    GotoXY(0, 0);
    printf("MSG : ");

    GotoXY(57, 0);

    printf("주머니 : %d  현재 골드: %d  체력 : %d / %d  공격력 : %d ", global::goldCounter, global::gold, global::hp, global::max_hp, global::atk);

    GotoXY(30, 0);
    printf("Player Position (%d, %d)", global::curPlayerPos.X, global::curPlayerPos.Y);

    //GotoXY(101, 14);
    //printf("Battle!");


    if ((global::prePlayerPos.X != global::curPlayerPos.X) || (global::prePlayerPos.Y != global::curPlayerPos.Y))
    {
        DrawPlayer(true);
    }
}

void UpdateAttackUpgrade() {
    if (IsInsideZone(global::curPlayerPos, global::atkZone)) { // 공격력 강화소 안에 있는지 확인


        // 스페이스바를 처음 눌렀을 때만 실행 (한 번 실행 후 기다림)
        if (global::gold >= 1 && global::input::IsSpaceKeyOn() && !global::WasSpaceKeyPressed) {
            global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록

            // 강화 진행
            global::gold -= 1; // 골드 1 감소

            int chance = rand() % 2; // 50% 확률 (0 또는 1)
            if (chance == 0) {
                global::atk += 10; // 공격력 증가
                GotoXY(7, 0);
                printf("공격력 +10      "); // 기존 메시지를 덮어쓰기 위해 공백 포함
            }
            else {
                GotoXY(7, 0);
                printf("강화 실패...    ");
            }


            // 키 입력 초기화 (강화 실행 후 다시 키 입력 받을 수 있도록 설정)
            global::input::Set(global::input::IsSpaceKeyOn(), false);
        }
    }

    // 키를 떼었을 때 다시 강화 가능하게 만듦
    if (!global::input::IsSpaceKeyOn()) {
        global::WasSpaceKeyPressed = false; // 키를 떼었을 때 다시 강화 가능
    }
}

void UpdateHpUpgrade() {
    if (IsInsideZone(global::curPlayerPos, global::HpZone)) { // 체력 강화소 안에 있는지 확인


        // 스페이스바를 처음 눌렀을 때만 실행 (한 번 실행 후 기다림)
        if (global::gold >= 1 && global::input::IsSpaceKeyOn() && !global::WasSpaceKeyPressed) {
            global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록

            // 강화 진행
            global::gold -= 1; // 골드 1 감소

            int chance = rand() % 2; // 50% 확률 (0 또는 1)
            if (chance == 0) {
                global::max_hp += 100; // 체력 증가
                global::hp += 100;
                GotoXY(7, 0);
                printf("체력 +100     "); // 기존 메시지를 덮어쓰기 위해 공백 포함
            }
            else {
                GotoXY(7, 0);
                printf("강화 실패...      ");
            }


            // 키 입력 초기화 (강화 실행 후 다시 키 입력 받을 수 있도록 설정)
            global::input::Set(global::input::IsSpaceKeyOn(), false);
        }
    }

    // 키를 떼었을 때 다시 강화 가능하게 만듦
    if (!global::input::IsSpaceKeyOn()) {
        global::WasSpaceKeyPressed = false; // 키를 떼었을 때 다시 강화 가능
    }
}

void AutoMoneyBuy() {
    
    const int maxPurchases = 3;    // 최대 구매 가능 횟수

    if (IsInsideZone(global::curPlayerPos, global::AutoMoneyBuyZone)) { // 구매 존 안에 있는지 확인
        
        if (global::purchaseCount < maxPurchases) {
            GotoXY(7, 0);
            printf("구매하시겠습니까?    ");
        }
        // 스페이스바를 처음 눌렀을 때만 실행 & 구매 횟수 체크
        if (global::gold >= 1 && global::input::IsSpaceKeyOn() && !global::WasSpaceKeyPressed && global::purchaseCount < maxPurchases) {
            global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록

            // 골드 차감
            global::gold -= 1; 
            global::purchaseCount++;  // 구매 횟수 증가
            GotoXY(37, 20);
            setColor(6); //노란색
            printf("(%d)",global::purchaseCount);
            setColor(15); // 기본색

            
        }

        // 모든 구매를 완료하면 메시지 표시
        if (global::purchaseCount >= maxPurchases) {
            GotoXY(7, 0);
            printf("구매 한도 도달!     ");
        }
    }

    // 키를 떼었을 때 다시 구매 가능하게 설정
    if (!global::input::IsSpaceKeyOn()) {
        global::WasSpaceKeyPressed = false;
    }
}

void AutoMoney() {
    static ULONGLONG autoGoldTime = GetTickCount64();

    if (GetTickCount64() - autoGoldTime >= 1000) { // 0.5초(500ms)마다 증가
        global::gold += global::purchaseCount * 1;
        autoGoldTime = GetTickCount64(); // 타이머 초기화
    }
}


void BattleStart() {
    if (IsInsideZone(global::curPlayerPos, global::battleZone)) { // 배틀존 안에 있는지 확인


        // 스페이스바를 처음 눌렀을 때만 실행 (한 번 실행 후 기다림)
        if (global::input::IsSpaceKeyOn() && !global::WasSpaceKeyPressed) {
            global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록

            GotoXY(7, 0);
            printf("배틀시작");


            //  여기에 배틀 시작 관련 함수 넣으면 됨!
            Reset();
            BattleManager();
            //
            // 키 입력 초기화 (강화 실행 후 다시 키 입력 받을 수 있도록 설정)
            global::input::Set(global::input::IsSpaceKeyOn(), false);
        }
    }

    // 키를 떼었을 때 다시 강화 가능하게 만듦
    if (!global::input::IsSpaceKeyOn()) {
        global::WasSpaceKeyPressed = false; // 키를 떼었을 때 다시 강화 가능
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

bool IsInsideZone(COORD pos, SMALL_RECT zone) {
    return (pos.X >= zone.Left && pos.X <= zone.Right &&
        pos.Y >= zone.Top && pos.Y <= zone.Bottom);
}

void UpdateGoldMining() {
    if (IsInsideZone(global::curPlayerPos, global::goldZone)) { // 골드존 내부 확인
        global::isMining = true; // 채굴 상태 활성화
    }
    else {
        global::isMining = false; // 골드존 벗어나면 채굴 중지
    }

    if (global::isMining) { // 골드존 내부에서만 실행
        static ULONGLONG miningTime = GetTickCount64();

        if (GetTickCount64() - miningTime >= 500) { // 0.5초(500ms)마다 증가
            if (global::goldCounter < 10) { // 최대 10까지 증가
                global::goldCounter++;
                GotoXY(7, 0);
                printf("골드 채굴 중: %d/10 ", global::goldCounter);
            }
            miningTime = GetTickCount64(); // 타이머 초기화
        }
    }
}

void UpdateGoldStorage() {
    if (IsInsideZone(global::curPlayerPos, global::homeZone)) { // 집 영역 확인
        if (global::goldCounter > 0) { // 채굴한 골드가 있을 때 저장
            global::gold += global::goldCounter;
            global::goldCounter = 0; // 카운트 초기화


            GotoXY(7, 0);
            printf("골드 저장 완료!   ");
        }
    }
}



void Update()
{
    global::time::updateCount += 1;
    UpdatePlayer();
    UpdateGoldMining();
    UpdateGoldStorage();
    UpdateAttackUpgrade();
    UpdateHpUpgrade();
    BattleStart();
    AutoMoneyBuy();
    AutoMoney();

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

char getCharAtPosition(int x, int y) {
    CHAR_INFO ci;
    COORD coord = { (SHORT)x, (SHORT)y };
    SMALL_RECT rect = { x, y, x, y };
    COORD bufferSize = { 1, 1 };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutput(hConsole, &ci, bufferSize, { 0, 0 }, &rect);

    return ci.Char.AsciiChar; // 해당 위치 문자 반환
}


void UpdatePlayerPosition()
{
    global::prePlayerPos = global::curPlayerPos;

    if (global::input::IsUpKeyOn()) // 위쪽 이동
    {
        global::input::Set(global::input::UP_KEY_INDEX, false);
        short newY = global::curPlayerPos.Y - 1;

        // 이동하려는 위치의 문자가 ' ' 이면 이동 // getCharAtPosition(global::curPlayerPos.X, newY) != '@'
        if (getCharAtPosition(global::curPlayerPos.X, newY) == ' ') {
            global::curPlayerPos.Y = newY;
        }
        if (getCharAtPosition(global::curPlayerPos.X, newY) == '%') {
            Reset();
            BattleManager();
        }
    }

    if (global::input::IsDownKeyOn()) // 아래쪽 이동
    {
        global::input::Set(global::input::DOWN_KEY_INDEX, false);
        short newY = global::curPlayerPos.Y + 1;
        //getCharAtPosition(global::curPlayerPos.X, newY) != '@'
        if (getCharAtPosition(global::curPlayerPos.X, newY) == ' ') {
            global::curPlayerPos.Y = newY;
        }
        if (getCharAtPosition(global::curPlayerPos.X, newY) == '%') {
            Reset();
            BattleManager();
        }
    }

    if (global::input::IsLeftKeyOn()) // 왼쪽 이동
    {
        global::input::Set(global::input::LEFT_KEY_INDEX, false);
        short newX = global::curPlayerPos.X - 1;

        //getCharAtPosition(newX, global::curPlayerPos.Y) != '@'
        if (getCharAtPosition(newX, global::curPlayerPos.Y) == ' ') {
            global::curPlayerPos.X = newX;
        }
        if (getCharAtPosition(newX, global::curPlayerPos.Y) == '%') {
            Reset();
            BattleManager();
        }

    }

    if (global::input::IsRightKeyOn()) // 오른쪽 이동
    {
        global::input::Set(global::input::RIGHT_KEY_INDEX, false);
        short newX = global::curPlayerPos.X + 1;

        // getCharAtPosition(newX, global::curPlayerPos.Y) != '@'
        if (getCharAtPosition(newX, global::curPlayerPos.Y) == ' ') {
            global::curPlayerPos.X = newX;
        }
        if (getCharAtPosition(newX, global::curPlayerPos.Y) == '%') {
            Reset();
            BattleManager();
        }
    }
}

void ProcessInput() // InputSystem.cpp 코드 가져와서 사용
{
    global::input::UpdateInput(); // ESC,상,하,좌,우,스페이스바 입력 받기

}




void DrawPlayer(bool bClear) // 플레이어 출력 함수 매개변수로 
{
    if (bClear)
    {
        GotoXY(global::prePlayerPos.X, global::prePlayerPos.Y); // 이동 전 위치
        putchar(' '); // 이동했으니 공백 출력
    }

    GotoXY(global::curPlayerPos.X, global::curPlayerPos.Y); // 이동 후 위치
    printf("&"); // 플레이어 위치이므로 #  >> 추후 다른 문자로 바꿀 예정
}

void DrawMovableRect() // 이동불가 영역 표시 = 벽
{
    setColor(8);
    for (int x = global::playerMovableRect.Left - 1; x < global::playerMovableRect.Right + 1; x++) // 이동 불가지점보다 1칸씩 밖에 @ 그리기 
    {
        GotoXY(x, global::playerMovableRect.Top - 1);
        printf("■");
        //putchar('@');
    }

    for (int x = global::playerMovableRect.Left - 1; x < global::playerMovableRect.Right + 1; x++) // 이동 불가지점보다 1칸씩 밖에 @ 그리기 
    {
        GotoXY(x, global::playerMovableRect.Bottom + 1);
        printf("■");
        //putchar('@');
    }

    for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom + 1; y++) // 이동 불가지점보다 1칸씩 밖에 @ 그리기 
    {
        GotoXY(global::playerMovableRect.Left - 1, y);
        printf("■");
        //putchar('@');
    }

    for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom + 1; y++) // 이동 불가지점보다 1칸씩 밖에 @ 그리기 
    {
        GotoXY(global::playerMovableRect.Right + 1, y);
        printf("■");
        //putchar('@');
    }
    setColor(15);
}
void DrawHomeRect()
{
    setColor(8); //회색
    for (int i = 2; i <= 10; i++) {
        GotoXY(40, i);
        printf("■");
        //putchar('@');
    }
    for (int i = 19; i <= 27; i++) {
        GotoXY(40, i);
        printf("■");
        //putchar('@');
    }
    for (int i = 30; i < 40; i++) {
        GotoXY(i, 10);
        printf("■");
        // putchar('@');
    }
    for (int i = 30; i < 40; i++) {
        GotoXY(i, 19);
        printf("■");
        // putchar('@');
    }
    setColor(15); // 기존색으로 복귀
}

void DrawAutoMoney() {
    GotoXY(30,20);
    setColor(6); //노란색
    printf("BUY 50G");
    setColor(15); // 기존색으로 복귀
}

void DrawAtkRect() {
    setColor(12); //빨간색
    for (int i = 2; i <= 8; i++) {
        GotoXY(44, i);
        printf("■");
        //putchar('@');
    }
    for (int i = 2; i <= 8; i++) {
        GotoXY(62, i);
        printf("■");
        //putchar('@');
    }
    setColor(15); // 기존색으로 복귀
}

void DrawHpRect() {
    setColor(10); //초록색
    for (int i = 2; i <= 8; i++) {
        GotoXY(66, i);
        printf("■");
        //putchar('@');
    }
    for (int i = 2; i <= 8; i++) {
        GotoXY(84, i);
        printf("■");
        //putchar('@');
    }
    setColor(15); // 기존색으로 복귀
}

void DrawGoldRect() {
    setColor(6); //노란색
    for (int i = 21; i <= 27; i++) {
        GotoXY(44, i);
        printf("■");
        //putchar('@');
    }
    for (int i = 21; i <= 27; i++) {
        GotoXY(79, i);
        printf("■");
        //putchar('@');
    }
    setColor(15); // 기존색으로 복귀
}

//void DrawpoltalRect() {
//    for (int i = 21; i <= 27; i++) {
//        GotoXY(71, i);
//        putchar('@');
//    }
//    for (int i = 21; i <= 27; i++) {
//        GotoXY(84, i);
//        putchar('@');
//    }
//}

void DrawDungeonRect() {
    setColor(8);
    for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom - 4; y++) {
        GotoXY(90, y);
        printf("■");
        //putchar('@');
    }
    for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom - 4; y++) {
        GotoXY(89, y);
        printf("■");
        //putchar('@');
    }
    for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom - 4; y++) {
        GotoXY(88, y);
        printf("■");
        //putchar('@');
    }
    for (int i = 91; i < 118; i++) {
        GotoXY(i, 12);
        printf("■");
        //putchar('@');
    }
    for (int i = 13; i < 17; i++) {
        GotoXY(96, i);
        printf("■");
        //putchar('@');
        GotoXY(112, i);
        printf("■");
        //putchar('@');
    }
    setColor(15);
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
    DrawHomeRect(); // 집 벽 생성
    DrawAtkRect(); //  공격력 강화소 벽 생성
    DrawHpRect(); // 체력 강화소 벽 생성
    DrawGoldRect(); //광산 벽 생성 
    //DrawpoltalRect(); // 던전 입구 벽 생성
    DrawDungeonRect();
    DrawAutoMoney();

    global::prePlayerPos.X = 10;
    global::prePlayerPos.Y = 10;
    global::curPlayerPos.X = 10;
    global::curPlayerPos.Y = 10; // 플레이어 시작 위치

    DrawPlayer(false); // 플레이어 생성
}
int main()
{
    GotoXY(15, 10);
    putchar('%');
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
