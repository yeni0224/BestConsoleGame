#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "../BestConsoleGame/Input_Sys.h"
#include "../BestConsoleGame/Utility.h"
#include "../BestConsoleGame/Battle.h"
#include "../BestConsoleGame/BestConsoleGame.h"



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
void DrawBed();
void DrawTitleRect();
void DrawQuestBoard();
void DrawQuestCheck();
void ShowQuestMessage(const std::string& msg);
void UpdateQuestProgress_atkupgrade();
void UpdateQuestProgress_hpupgrade();

struct zone_xy { // X,Y좌표 구조체
    int x;
    int y;
    zone_xy(int _x, int _y) : x(_x), y(_y) {}
};
struct zone_awds { // 좌 상 우 하 구조체
    int a;
    int w;
    int d;
    int s;
    zone_awds(int _a, int _w, int _d, int _s) : a(_a), w(_w), d(_d), s(_s) {}
};

struct Quest { // 퀘스트 구조체
    std::string name;
    std::string description;
    enum State { LOCKED, IN_PROGRESS, COMPLETE } state;
    int current;
    int goal;

    bool IsComplete() const {
        return current >= goal;
    }
};

namespace global
{
    zone_xy msg(7, 0);
    zone_xy auto_money_buy_zone(37, 20);
    zone_xy auto_money_word_zone(30, 20);
    zone_xy atk_word_zone(46, 2);
    zone_xy hp_word_zone(68, 2);
    zone_xy gold_word_zone(46, 27);

    zone_awds home_zone_up(30, 2, 40, 10);
    zone_awds home_zone_down(30, 19, 40, 27);
    zone_awds bed_zone(2, 22, 7, 27);
    zone_awds atk_zone(44, 2, 62, 8);
    zone_awds hp_zone(66, 2, 84, 8);
    zone_awds gold_zone(44, 21, 79, 27);



    std::vector<Quest> questList = {
    { "초보 광부", "골드 20원 수집", Quest::LOCKED, 0, 1 }, // 임시로 1 해둠 나중에 20으로 변경
    { "ATK 강화", "공격력 3회 강화", Quest::LOCKED, 0, 3 },
    { "HP 강화", "체력 3회 강화", Quest::LOCKED, 0, 3 }
    };
    std::string questMessage = "";

    int gold = 500;
    int hp = 10;
    int max_hp = 100;
    int atk = 10;

    int up_atk = 5;
    int up_hp = 50;
    int heal_hp = 10;

    void setatk(int value) { atk = value; }
    int getatk() { return atk; }

    short newY = 0;
    int x = 19;
    int y = 15;
    bool bUpKeyPressed = false;
    bool bDownKeyPressed = false;
    bool bSpaceKeyPressedInMenu = false;

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
    ULONGLONG questMessageStartTime = 0; // 퀘스트 메시지 출력 시간 타이머
    ULONGLONG goldTimer = 0; // 골드 증가 타이머
    static int purchaseCount = 0;  // 구매 횟수 (최대 3회)

    int goldCounter = 0;      // 골드 카운트 (0~10)
    int atkCounter = 0;       // 공격력 업그레이드 카운터 (0~10)
    int hpCounter = 0;        // 체력 업그레이드 카운터 (0~10)
    int selectedQuestIndex = 0; // 0번 퀘스트 수락 예정

    bool isMining = false;    // 채굴 상태 여부
    bool isUpgrading = false; // 강화 진행 여부
    bool isReady = false;     // 배틀 시작 여부
    bool isHealing = false;   // 체력 회복 여부
    bool WasSpaceKeyPressed = false; // 스페이스바 눌렸는지 체크
    bool WasYKeyPressed = false; // Y 눌렸는지 체크
    bool isQuestMessageShown = false; // 퀘스트 메시지 1번만 출력됐는지 확인
    bool isQuestMessageVisible = false; // 메시지 보이는지 체크
    bool gamestartflag = false;

    SMALL_RECT goldZone = { 45, 21, 79, 27 }; // 골드존 영역 (좌, 상, 우, 하)
    SMALL_RECT homeZone = { 2, 2, 29, 27 }; // 집 영역
    SMALL_RECT atkZone = { 45, 2, 61, 8 }; // 공격력 강화소 영역
    SMALL_RECT HpZone = { 67, 2, 83, 8 }; // 공격력 강화소 영역
    SMALL_RECT battleZone = { 97, 13, 111, 16 }; // 배틀 영역 30 20 39 27
    SMALL_RECT AutoMoneyBuyZone = { 30, 20, 39, 27 }; // 오토 머니 구매 영역
    SMALL_RECT HealingZone = { 2, 20, 20, 27 }; // 침대 근처 체력 회복 존
    SMALL_RECT QuestZone = { 2, 2, 20, 5 }; // 퀘스트 수락 존
    SMALL_RECT QuestCheckZone = { 30, 2, 39, 9 }; // 퀘스트 수락 존
    SMALL_RECT GameStartZone = { 20, 20, 15, 15 }; // 게임시작 커서 위치
    SMALL_RECT TutorialZone = { 20, 20, 16, 16 }; // 게임 설명 커서 위치
    SMALL_RECT GameQuitZone = { 20, 20, 17, 17 }; // 게임 종료 설명 위치

};

void ShowQuestMessage(const std::string& msg) // 메시지 출력 시간 조절 함수
{
    global::questMessage = msg;
    global::isQuestMessageVisible = true;
    global::questMessageStartTime = GetTickCount64();
}

void UpdateQuestMessage() // 퀘스트 메시지 삭제 함수
{
    if (!global::isQuestMessageVisible) return;

    ULONGLONG now = GetTickCount64();
    if (now - global::questMessageStartTime >= 3000) {
        // 메시지 삭제
        GotoXY(50, 14);
        for (int i = 0; i < global::questMessage.length(); ++i) putchar(' ');
        global::isQuestMessageVisible = false;
        global::questMessage = "";
    }
    else {
        // 메시지 출력 (계속 덮어쓰기)
        GotoXY(50, 14);
        printf("%s", global::questMessage.c_str());
    }
}

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

        if (global::atkCounter > 9) {
            GotoXY(7, 0);
            printf("MAX 강화 상태입니다.");
        }
        else {
            // 스페이스바를 처음 눌렀을 때만 실행 (한 번 실행 후 기다림)
            if (global::gold >= 10 && global::input::IsSpaceKeyOn() && !global::WasSpaceKeyPressed) {
                global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록

                // 강화 진행
                global::gold -= 10; // 골드 10 감소

                int chance = rand() % 2; // 50% 확률 (0 또는 1)
                if (chance == 0) {
                    global::atk += global::up_atk; // 공격력 증가
                    GotoXY(global::msg.x, global::msg.y);

                    global::atkCounter++;
                    UpdateQuestProgress_atkupgrade();
                    printf("공격력 +%d      ", global::up_atk); // 기존 메시지를 덮어쓰기 위해 공백 포함
                }
                else {
                    GotoXY(global::msg.x, global::msg.y);
                    printf("강화 실패...    ");
                }


                // 키 입력 초기화 (강화 실행 후 다시 키 입력 받을 수 있도록 설정)
                global::input::Set(global::input::IsSpaceKeyOn(), false);
            }
        }


    }

    // 키를 떼었을 때 다시 강화 가능하게 만듦
    if (!global::input::IsSpaceKeyOn()) {
        global::WasSpaceKeyPressed = false; // 키를 떼었을 때 다시 강화 가능
    }
}

void UpdateHpUpgrade() {
    if (IsInsideZone(global::curPlayerPos, global::HpZone)) { // 체력 강화소 안에 있는지 확인
        if (global::hpCounter > 9) {
            GotoXY(7, 0);
            printf("MAX 상태입니다.");
        }
        else {
            // 스페이스바를 처음 눌렀을 때만 실행 (한 번 실행 후 기다림)
            if (global::gold >= 10 && global::input::IsSpaceKeyOn() && !global::WasSpaceKeyPressed) {
                global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록

                // 강화 진행
                global::gold -= 10; // 골드 10 감소

                int chance = rand() % 2; // 50% 확률 (0 또는 1)
                if (chance == 0) {
                    global::max_hp += global::up_hp; // 체력 증가
                    global::hp += global::up_hp;
                    GotoXY(global::msg.x, global::msg.y);
                    global::hpCounter++;
                    UpdateQuestProgress_hpupgrade();
                    printf("체력 +%d      ", global::up_hp); // 기존 메시지를 덮어쓰기 위해 공백 포함
                }
                else {
                    GotoXY(global::msg.x, global::msg.y);
                    printf("강화 실패...       ");
                }


                // 키 입력 초기화 (강화 실행 후 다시 키 입력 받을 수 있도록 설정)
                global::input::Set(global::input::IsSpaceKeyOn(), false);
            }
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
            GotoXY(global::msg.x, global::msg.y);
            printf("구매하시겠습니까?     ");
        }
        // 스페이스바를 처음 눌렀을 때만 실행 & 구매 횟수 체크
        if (global::gold >= 50 && global::input::IsSpaceKeyOn() && !global::WasSpaceKeyPressed && global::purchaseCount < maxPurchases) {
            global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록

            // 골드 차감
            global::gold -= 50;
            global::purchaseCount++;  // 구매 횟수 증가   
            GotoXY(global::auto_money_buy_zone.x, global::auto_money_buy_zone.y);
            setColor(6); //노란색
            printf("(%d)", global::purchaseCount);
            setColor(15); // 기본색


        }

        // 모든 구매를 완료하면 메시지 표시
        if (global::purchaseCount >= maxPurchases) {
            GotoXY(global::msg.x, global::msg.y);
            printf("구매 한도 도달!      ");
        }
    }

    // 키를 떼었을 때 다시 구매 가능하게 설정
    if (!global::input::IsSpaceKeyOn()) {
        global::WasSpaceKeyPressed = false;
    }
}

void AutoMoney() {
    static ULONGLONG autoGoldTime = GetTickCount64();

    if (GetTickCount64() - autoGoldTime >= 2000) { // 2초(2000ms)마다 증가
        global::gold += global::purchaseCount * 1;
        autoGoldTime = GetTickCount64(); // 타이머 초기화
    }
}


void BattleStart() {
    if (IsInsideZone(global::curPlayerPos, global::battleZone)) { // 배틀존 안에 있는지 확인
        GotoXY(global::msg.x, global::msg.y);
        printf("전투 시작 : Y       ");

        // Y를 처음 눌렀을 때만 실행 (한 번 실행 후 기다림)
        if (global::input::IsYKeyOn() && !global::WasYKeyPressed) {
            global::WasYKeyPressed = true; // 키가 눌렸음을 기록


            //  여기에 배틀 시작 관련 함수 넣으면 됨!
            global::battle::Reset();
            global::battle::BattleManager();
            //
            // 키 입력 초기화 
            global::input::Set(global::input::IsYKeyOn(), false);
        }
    }


    if (!global::input::IsYKeyOn()) {
        global::WasYKeyPressed = false;
    }


}

void QuestAccept() {
    if (IsInsideZone(global::curPlayerPos, global::QuestZone)) {
        if (!global::isQuestMessageShown) {
            GotoXY(global::msg.x, global::msg.y);
            printf("퀘스트 수락 = Y   ");
            global::isQuestMessageShown = true;
        }

        if (global::input::IsYKeyOn() && !global::WasYKeyPressed) {
            global::WasYKeyPressed = true;

            // ✅ 유효한 인덱스인지 먼저 체크
            if (global::selectedQuestIndex >= global::questList.size()) {
                ShowQuestMessage("더 이상 수락할 퀘스트가 없습니다.");
            }
            else {
                Quest& q = global::questList[global::selectedQuestIndex];

                if (q.state == Quest::LOCKED) {
                    q.state = Quest::IN_PROGRESS;
                    ShowQuestMessage("'" + q.name + "' 퀘스트를 수락했습니다.    ");
                }
                else {
                    ShowQuestMessage("이미 수락한 퀘스트입니다.         ");
                }
            }

            global::input::Set(global::input::IsYKeyOn(), false);
        }
    }
    else {
        global::isQuestMessageShown = false;
    }

    if (!global::input::IsYKeyOn()) {
        global::WasYKeyPressed = false;
    }
}


void CheckAcceptedQuest() {
    if (IsInsideZone(global::curPlayerPos, global::QuestCheckZone)) {
        GotoXY(global::msg.x, global::msg.y);
        printf("퀘스트 확인 = Y");
        if (global::input::IsYKeyOn() && !global::WasYKeyPressed) {
            global::WasYKeyPressed = true;

            // 진행 중인 퀘스트 찾기
            bool found = false;
            for (const auto& q : global::questList) {
                if (q.state == Quest::IN_PROGRESS) {
                    std::string msg = "퀘스트: " + q.name + " (" + std::to_string(q.current) + "/" + std::to_string(q.goal) + ")             ";
                    ShowQuestMessage(msg); // 3초간 중앙 출력
                    found = true;
                    break;
                }
            }

            if (!found) {
                ShowQuestMessage("진행 중인 퀘스트가 없습니다.         ");
            }

            global::input::Set(global::input::IsYKeyOn(), false);
        }
    }

    if (!global::input::IsYKeyOn()) {
        global::WasYKeyPressed = false;
    }
}

void UpdateQuestProgress_GoldMined() // 골드20원 수집 퀘스트
{
    for (auto& q : global::questList)
    {
        if (q.name == "초보 광부" && q.state == Quest::IN_PROGRESS)
        {
            // 골드 채굴 1회 = 진행도 1 증가
            q.current += global::goldCounter;
            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 30G)");

                global::gold += 30;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_atkupgrade() // 공격력 강화 성공 시 진행
{
    for (auto& q : global::questList)
    {
        if (q.name == "ATK 강화" && q.state == Quest::IN_PROGRESS)
        {
            q.current += 1; // 공격력 강화 1회 성공 → 진행도 1 증가

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_hpupgrade() // 공격력 강화 성공 시 진행
{
    for (auto& q : global::questList)
    {
        if (q.name == "HP 강화" && q.state == Quest::IN_PROGRESS)
        {
            q.current += 1; // 공격력 강화 1회 성공 → 진행도 1 증가

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
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

void HealingHP() {
    if (IsInsideZone(global::curPlayerPos, global::HealingZone)) { // 힐링존 내부 확인
        global::isHealing = true; // 힐링 상태 활성화
    }
    else {
        global::isHealing = false; // 힐링존 벗어나면 힐 중지

    }

    if (global::isHealing) { // 힐링존 내부에서만 실행
        static ULONGLONG healingTime = GetTickCount64();

        if (GetTickCount64() - healingTime >= 1000) { // 0.5초(500ms)마다 증가
            if (global::hp < global::max_hp) { // 현재 hp가 최대 hp보다 낮을 시
                global::hp += global::heal_hp;
                if (global::hp > global::max_hp) {
                    global::hp = global::max_hp;
                }
                GotoXY(global::msg.x, global::msg.y);
                printf("체력 회복중 ^~^  ");
            }
            else {
                GotoXY(global::msg.x, global::msg.y);
                printf("체력 회복 완료!!  ");
            }
            healingTime = GetTickCount64(); // 타이머 초기화
        }

    }
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

        if (GetTickCount64() - miningTime >= 1000) { // 0.5초(500ms)마다 증가
            if (global::goldCounter < 10) { // 최대 10까지 증가
                global::goldCounter++;
                GotoXY(global::msg.x, global::msg.y);
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
            UpdateQuestProgress_GoldMined();
            global::goldCounter = 0; // 카운트 초기화


            GotoXY(global::msg.x, global::msg.y);
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
    HealingHP();
    

    QuestAccept();
    CheckAcceptedQuest();
    UpdateQuestMessage();
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
            global::battle::Reset();
            global::battle::BattleManager();
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
            global::battle::Reset();
            global::battle::BattleManager();
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
            global::battle::Reset();
            global::battle::BattleManager();
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
            global::battle::Reset();
            global::battle::BattleManager();
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

void DrawTitleRect() 
{
    for (int i = 18; i <= 29;i++) {
        GotoXY(i, 14);
        printf("@");
    }
    for (int i = 15;i < 18;i++) {
        GotoXY(18, i);
        printf("@");
    }
    for (int i = 18; i <= 29;i++) {
        GotoXY(i, 18);
        printf("@");
    }
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
    for (int i = global::home_zone_up.w; i <= global::home_zone_up.s; i++) {
        GotoXY(global::home_zone_up.d, i);
        printf("■");
        //putchar('@');
    }
    for (int i = global::home_zone_down.w; i <= global::home_zone_down.s; i++) {
        GotoXY(global::home_zone_up.d, i);
        printf("■");
        //putchar('@');
    }
    for (int i = global::home_zone_up.a; i < global::home_zone_up.d; i++) {
        GotoXY(i, global::home_zone_up.s);
        printf("■");
        // putchar('@');
    }
    for (int i = global::home_zone_down.a; i < global::home_zone_down.d; i++) {
        GotoXY(i, global::home_zone_down.w);
        printf("■");
        // putchar('@');
    }
    setColor(15); // 기존색으로 복귀
}

void DrawQuestBoard() {
    GotoXY(2, 2);
    printf("▩ QUEST BOARD▩");
    GotoXY(2, 3);
    printf("▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
}

void DrawQuestCheck() {
    GotoXY(30, 2);
    printf("QUEST LIST");
}

void DrawBed() {
    for (int i = global::bed_zone.w; i <= global::bed_zone.s; i++) {
        for (int j = global::bed_zone.a; j <= global::bed_zone.d; j++) {
            if (i == global::bed_zone.s || i == global::bed_zone.s - 1) {
                GotoXY(j, i);
                setColor(12);
                printf("■");
                setColor(15);
            }
            else {
                GotoXY(j, i);
                setColor(7);
                printf("■");
                setColor(15);
            }
        }
    }
}


void DrawAutoMoney() {
    GotoXY(global::auto_money_word_zone.x, global::auto_money_word_zone.y);
    setColor(6); //노란색
    printf("BUY 50G");
    setColor(15); // 기존색으로 복귀
}

void DrawAtkRect() {
    setColor(12); //빨간색
    GotoXY(global::atk_word_zone.x, global::atk_word_zone.y);
    printf("ATK UPGRADE 10G");
    for (int i = global::atk_zone.w; i <= global::atk_zone.s; i++) {
        GotoXY(global::atk_zone.a, i);
        printf("■");
        //putchar('@');
    }
    for (int i = 2; i <= 8; i++) {
        GotoXY(global::atk_zone.d, i);
        printf("■");
        //putchar('@');
    }
    setColor(15); // 기존색으로 복귀
}

void DrawHpRect() {
    setColor(10); //초록색
    GotoXY(global::hp_word_zone.x, global::hp_word_zone.y);
    printf("HP UPGRADE 10G");
    for (int i = global::hp_zone.w; i <= global::hp_zone.s; i++) {
        GotoXY(global::hp_zone.a, i);
        printf("■");
        //putchar('@');
    }
    for (int i = 2; i <= 8; i++) {
        GotoXY(global::hp_zone.d, i);
        printf("■");
        //putchar('@');
    }
    setColor(15); // 기존색으로 복귀
}

void DrawGoldRect() {
    setColor(6); //노란색
    GotoXY(global::gold_word_zone.x, global::gold_word_zone.y);
    printf("MINE 1G/S");
    for (int i = global::gold_zone.w; i <= global::gold_zone.s; i++) {
        GotoXY(global::gold_zone.a, i);
        printf("■");
        //putchar('@');
    }
    for (int i = 21; i <= 27; i++) {
        GotoXY(global::gold_zone.d, i);
        printf("■");
        //putchar('@');
    }
    setColor(15); // 기존색으로 복귀
}


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

/// <summary>
/// 게임 설명 창
/// </summary>
void TutorialPage() //타이틀 이중배열 들고오기
{
    
    //system("cls");

    int x = 10;
    int y = 10;
    GotoXY(x, y + 10);
    std::cout << "<< 조작 방법 >>" << std::endl;
    GotoXY(x, y + 11);
    std::cout << "<< >>" << std::endl;
    GotoXY(x, y + 12);
    std::cout << "<<  >>" << std::endl;
}

/// <summary>
/// 콘솔창 종료
/// </summary>
void QuitGame()
{
    system("cls");
    exit(EXIT_FAILURE);
}

/// <summary>
/// 메뉴 선택 키 위치 초기화
/// </summary>
void InitSelectMenu()
{
    GotoXY(19, 15);
    std::cout << ">";
}

/// <summary>
/// 방향키 움직이기, 화살표 출력, clamp 함수 넣어 테스트 해보아야함
/// </summary>
void MoveSelectMenu()
{
    static bool bSpaceKeyPressedInMenu = false;
    static bool bUpKeyPressedInMenu = false;
    static bool bDownKeyPressedInMenu = false;

    static ULONGLONG lastMoveTime = 0;
    ULONGLONG now = GetTickCount64();

    const int moveCooldown = 150;

    // ↓ 방향키 입력
    if (global::input::IsDownKeyOn())
    {
        if (!bDownKeyPressedInMenu && now - lastMoveTime >= moveCooldown)
        {
            bDownKeyPressedInMenu = true;
            global::input::Set(global::input::DOWN_KEY_INDEX, false); // ✅ 추가됨!

            if (global::curPlayerPos.Y < 17)
            {
                global::prePlayerPos = global::curPlayerPos;
                global::curPlayerPos.Y++;
                lastMoveTime = now;

                DrawPlayer(true);  // ✅ 이동 후 화면 갱신
            }
        }
    }
    else
    {
        bDownKeyPressedInMenu = false;
    }

    // ↑ 방향키 입력
    if (global::input::IsUpKeyOn())
    {
        if (!bUpKeyPressedInMenu && now - lastMoveTime >= moveCooldown)
        {
            bUpKeyPressedInMenu = true;
            global::input::Set(global::input::UP_KEY_INDEX, false); // ✅ 추가됨!

            if (global::curPlayerPos.Y > 15)
            {
                global::prePlayerPos = global::curPlayerPos;
                global::curPlayerPos.Y--;
                lastMoveTime = now;

                DrawPlayer(true);  // ✅ 위로 이동 출력
            }
        }
    }
    else
    {
        bUpKeyPressedInMenu = false;
    }

    // Space 키 처리
    if (global::input::IsSpaceKeyOn())
    {
        if (!bSpaceKeyPressedInMenu)
        {
            bSpaceKeyPressedInMenu = true;

            if (global::curPlayerPos.Y == 15) {
                global::gamestartflag = true;

            }
            else if (global::curPlayerPos.Y == 16) {
                TutorialPage();
            }
            else if (global::curPlayerPos.Y == 17) {
                QuitGame();
            }
        }
    }
    else
    {
        bSpaceKeyPressedInMenu = false;
    }
}

/// <summary>
/// 오프닝 메세지, 메뉴
/// </summary>
void RenderOpening()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!handle) return;

    int x = 20;
    int y = 5;
    GotoXY(global::msg.x, global::msg.y);
    printf("x: %d, y: %d", global::curPlayerPos.X, global::curPlayerPos.Y);
    GotoXY(x, y);
    std::cout << "...@@@@@@@@..@@......@@........@@........@@.......@@......@@.......@@....." << std::endl;
    GotoXY(x, y + 1);
    std::cout << "...@@....@@..@@......@@......@@@@.......@@@@......@@......@@.......@@@@..." << std::endl;
    GotoXY(x, y + 2);
    std::cout << "...@@....@@..@@......@@........@@......@@..@@.....@@@@....@@.......@@....." << std::endl;
    GotoXY(x, y + 3);
    std::cout << "...@@....@@..@@@@....@@......@@@@.....@@....@@....@@@@....@@@@@@@..@@@@..." << std::endl;
    GotoXY(x, y + 4);
    std::cout << "...@@....@@..@@......@@........@@....@@......@@...@@...............@@....." << std::endl;
    GotoXY(x, y + 5);
    std::cout << "...@@@@@@@@..@@......@@@@@@@@..@@...@@........@@..@@............@@........" << std::endl;
    GotoXY(x, y + 6);
    std::cout << ".............@@................@@.................@@..........@@..@@......" << std::endl;
    GotoXY(x, y + 7);
    std::cout << ".............@@................@@.................@@............@@........" << std::endl;

    GotoXY(x, y + 10);
    std::cout << "게임 시작" << std::endl;
    GotoXY(x, y + 11);
    std::cout << "게임 설명" << std::endl;
    GotoXY(x, y + 12);
    std::cout << "게임 종료" << std::endl;
}

/// <summary>
/// </summary>게임 플레이 전 오프닝 화면
/// <returns></returns>
void OpeningTitle()
{
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

    global::prePlayerPos.X = 19;
    global::prePlayerPos.Y = 15;
    global::curPlayerPos.X = 19;
    global::curPlayerPos.Y = 15;
}
void setConsoleSize(int width, int height)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 콘솔 창 크기 조정
    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // 콘솔 버퍼 크기 조정
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hConsole, bufferSize);
}

void startGame() 
{
    // 콘솔 크기를 120x30으로 설정
    setConsoleSize(120, 30);

    CONSOLE_CURSOR_INFO cursorInfo = { 0, }; // 커서 관련 정보 구조체
    cursorInfo.bVisible = 0; // 0 이면 커서 숨김, 1이면 커서 보임
    cursorInfo.dwSize = 1; // 커서 크기 1~100
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // 커서 설정

    CONSOLE_SCREEN_BUFFER_INFO csbi; // 콘솔 화면 버퍼 정보 구조체
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    global::consoleScreenSize.Left = csbi.srWindow.Left;
    global::consoleScreenSize.Right = csbi.srWindow.Right;
    global::consoleScreenSize.Bottom = csbi.srWindow.Bottom;
    global::consoleScreenSize.Top = csbi.srWindow.Top;

    global::playerMovableRect.Left = global::consoleScreenSize.Left + 2;
    global::playerMovableRect.Right = global::consoleScreenSize.Right - 2;
    global::playerMovableRect.Bottom = global::consoleScreenSize.Bottom - 2;
    global::playerMovableRect.Top = global::consoleScreenSize.Top + 2;

    DrawMovableRect(); // 테두리 벽 생성
    DrawHomeRect(); // 집 벽 생성
    DrawAtkRect(); // 공격력 강화소 벽 생성
    DrawHpRect(); // 체력 강화소 벽 생성
    DrawGoldRect(); // 광산 벽 생성 
    DrawDungeonRect(); // 던전 입구 벽 생성
    DrawAutoMoney(); // 자동 골드 구매 표시
    DrawBed(); // 침대 그리기
    DrawQuestBoard(); // 퀘스트 보드 그리기
    DrawQuestCheck(); // 퀘스트 리스트 그리기

    global::prePlayerPos.X = 10;
    global::prePlayerPos.Y = 20;
    global::curPlayerPos.X = 10;
    global::curPlayerPos.Y = 20; // 플레이어 시작 위치

    DrawPlayer(false); // 플레이어 생성
}

int main()
{

    global::time::InitTime(); // 시간 초기화

    OpeningTitle();//오프닝 화면
    //오프닝 루프
    while (IsGameRun())
    {
        global::time::UpdateTime();
        ProcessInput();
        FixedUpdate();
        //Title_Update();
        MoveSelectMenu();
        RenderOpening();
        if (global::gamestartflag == true) 
        {
            break;
        }
    }
    system("cls");
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
