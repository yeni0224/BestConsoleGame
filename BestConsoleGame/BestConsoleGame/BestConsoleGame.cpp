#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "../BestConsoleGame/Input_Sys.h"
#include "../BestConsoleGame/Utility.h"
#include "../BestConsoleGame/Battle.h"
#include "../BestConsoleGame/BestConsoleGame.h"
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"


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
void UpdateQuestProgress_monsterAclear();
void UpdateQuestProgress_atkupgrade2();
void UpdateQuestProgress_hpupgrade2();
void UpdateQuestProgress_monsterBclear();
void UpdateQuestProgress_atkupgrade3();
void UpdateQuestProgress_hpupgrade3();
void setConsoleSize(int width, int height);
void DrawOptionRect();
void RunCursorSelectionMenu();
void DrawMonster_info();

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
    namespace GameSound
    {
        FMOD_SYSTEM* system;
        FMOD_SOUND* bgm[2];      // 배경음 2개
        FMOD_SOUND* sfx[7];      // 효과음 7개
        FMOD_CHANNEL* bgmChannel = nullptr;
        FMOD_CHANNEL* sfxChannel = nullptr;

        // FMOD 시스템 초기화
        void GameSoundInit()
        {
            FMOD_System_Create(&system, FMOD_VERSION);
            FMOD_System_Init(system, 512, FMOD_INIT_NORMAL, nullptr);

            // 배경음 로드 (반복 재생)
            FMOD_System_CreateSound(system, "MainBGM.wav", FMOD_LOOP_NORMAL, 0, &bgm[0]); // 메인브금 (타이틀,메인)
            FMOD_System_CreateSound(system, "FightBGM5.mp3", FMOD_LOOP_NORMAL, 0, &bgm[1]);



            // 효과음 로드 (한 번만 재생)
            FMOD_System_CreateSound(system, "Buy50G.wav", FMOD_DEFAULT, 0, &sfx[0]); // 오토 머니 구매시 효과음
            FMOD_System_CreateSound(system, "CoinGet.wav", FMOD_DEFAULT, 0, &sfx[1]); // 코인 모아서 집가면 나오는 효과음 
            FMOD_System_CreateSound(system, "HealOnBed2.wav", FMOD_DEFAULT, 0, &sfx[2]); // 침대 근처 체력회복 효과음 + 퀘스트 수락 및 확인 효과음
            FMOD_System_CreateSound(system, "Mining3.wav", FMOD_DEFAULT, 0, &sfx[3]); // 금광 효과음 << 너무길어서 소리가 겹침
            FMOD_System_CreateSound(system, "PlayerAttack.mp3", FMOD_DEFAULT, 0, &sfx[4]); // 배틀시 공격 효과음
            FMOD_System_CreateSound(system, "StrengthFailed.wav", FMOD_DEFAULT, 0, &sfx[5]); // 강화 실패 효과음
            FMOD_System_CreateSound(system, "StrengthSuccess.wav", FMOD_DEFAULT, 0, &sfx[6]); // 강화 성공 효과음
        }

        // 배경음 재생
        void PlayBGM(int index)
        {
            if (index < 0 || index >= 2) return;
            FMOD_System_PlaySound(system, bgm[index], 0, false, &bgmChannel);
        }

        // 효과음 재생
        void PlaySFX(int index)
        {
            if (index < 0 || index >= 7) return;    // 유효성 검사
            FMOD_System_PlaySound(system, sfx[index], 0, false, &sfxChannel);
        }

        // 배경음 정지
        void StopBGM()
        {
            if (bgmChannel)
            {
                FMOD_Channel_Stop(bgmChannel);
            }
        }

        // FMOD 업데이트 (매 프레임 호출해야 함)
        void SoundUpdate()
        {
            FMOD_System_Update(system);
        }

        // FMOD 정리 (게임 종료 시 호출)
        void Shutdown()
        {
            for (int i = 0; i < 9; i++)
            {
                FMOD_Sound_Release(bgm[i]);
                FMOD_Sound_Release(sfx[i]);
            }
            FMOD_System_Close(system);
            FMOD_System_Release(system);
        }
    }
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
    zone_awds option_zone(2, 11, 6, 18);
    zone_awds monster_info__zone(91, 2, 117, 11);



    std::vector<Quest> questList = {
   { "초보 광부", "골드 20원 수집", Quest::LOCKED, 0, 20 }, // 임시로 1 해둠 나중에 20으로 변경
   { "ATK 강화 1", "공격력 3회 강화성공", Quest::LOCKED, 0, 3 },
   { "몬스터A 처치", "몬스터A 처치", Quest::LOCKED, false,  true},
   { "HP 강화 1", "체력 3회 강화성공", Quest::LOCKED, 0, 3 },
   { "ATK 강화 2", "공격력 5회 강화성공", Quest::LOCKED, 3, 5 },
   { "HP 강화 2", "체력 5회 강화성공", Quest::LOCKED, 3, 5 },
   { "몬스터B 처치", "몬스터B 처치", Quest::LOCKED, false,  true},
   { "ATK 강화 3", "공격력 8회 강화성공", Quest::LOCKED, 5, 8 },
   { "HP 강화 3", "체력 8회 강화성공", Quest::LOCKED, 5, 8 }
    };
    std::string questMessage = "";

    const std::vector<std::string> playerIconOptions = { ">", "★", "☆", "♀", "∵", "■", "д" };
    std::string playerIcon = ">"; // 기본값도 string으로 바꿔줘야 함



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



    int goldCounter = 0;      // 골드 카운트 (0~10)
    int atkCounter = 0;       // 공격력 업그레이드 카운터 (0~10)
    int hpCounter = 0;        // 체력 업그레이드 카운터 (0~10)
    int selectedQuestIndex = 0; // 0번 퀘스트 수락 예정
    static int purchaseCount = 0;  // 구매 횟수 (최대 3회)

    void resetCounter() {
        goldCounter = 0;      // 골드 카운트 (0~10)
        atkCounter = 0;       // 공격력 업그레이드 카운터 (0~10)
        hpCounter = 0;        // 체력 업그레이드 카운터 (0~10)
        selectedQuestIndex = 0; // 0번 퀘스트 수락 예정
        purchaseCount = 0;  // 구매 횟수 (최대 3회)

        global::questList[0].state = Quest::LOCKED;
        global::questList[1].state = Quest::LOCKED;
        global::questList[2].state = Quest::LOCKED;
        global::questList[3].state = Quest::LOCKED;
        global::questList[4].state = Quest::LOCKED;
        global::questList[5].state = Quest::LOCKED;
        global::questList[6].state = Quest::LOCKED;
        global::questList[7].state = Quest::LOCKED;
        global::questList[8].state = Quest::LOCKED;

        global::questList[0].current = 0;
        global::questList[1].current = 0;
        global::questList[2].current = false;
        global::questList[3].current = 0;
        global::questList[4].current = 3;
        global::questList[5].current = 3;
        global::questList[6].current = false;
        global::questList[7].current = 5;
        global::questList[8].current = 5;

    }

    bool isMining = false;    // 채굴 상태 여부
    bool isUpgrading = false; // 강화 진행 여부
    bool isReady = false;     // 배틀 시작 여부
    bool isHealing = false;   // 체력 회복 여부
    bool WasSpaceKeyPressed = false; // 스페이스바 눌렸는지 체크
    bool WasYKeyPressed = false; // Y 눌렸는지 체크
    bool isQuestMessageShown = false; // 퀘스트 메시지 1번만 출력됐는지 확인
    bool isQuestMessageVisible = false; // 메시지 보이는지 체크
    bool gamestartflag = false;
    bool gametutorialflag = false;

    int gold = 0;
    int hp = 100;
    int max_hp = 100;
    int atk = 10;

    int up_atk = 5;
    int up_hp = 50;
    int heal_hp = 10;

    SMALL_RECT goldZone = { 45, 21, 79, 27 }; // 골드존 영역 (좌, 상, 우, 하)
    SMALL_RECT homeZone = { 2, 2, 29, 27 }; // 집 영역
    SMALL_RECT atkZone = { 45, 2, 61, 8 }; // 공격력 강화소 영역
    SMALL_RECT HpZone = { 67, 2, 83, 8 }; // 공격력 강화소 영역
    SMALL_RECT battleZone = { 97, 13, 111, 16 }; // 배틀 영역 30 20 39 27
    SMALL_RECT AutoMoneyBuyZone = { 30, 20, 39, 27 }; // 오토 머니 구매 영역
    SMALL_RECT HealingZone = { 2, 20, 20, 27 }; // 침대 근처 체력 회복 존
    SMALL_RECT QuestZone = { 2, 2, 20, 5 }; // 퀘스트 수락 존
    SMALL_RECT QuestCheckZone = { 30, 2, 39, 9 }; // 퀘스트 수락 존
    SMALL_RECT OptionZone = { 2, 11, 6, 18 };
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
    if (now - global::questMessageStartTime >= 1000) {
        // 메시지 삭제
        GotoXY(44, 14);
        for (int i = 0; i < global::questMessage.length(); ++i) putchar(' ');
        global::isQuestMessageVisible = false;
        global::questMessage = "";
    }
    else {
        // 메시지 출력 (계속 덮어쓰기)
        GotoXY(44, 14);
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
                    global::GameSound::PlaySFX(6);
                    GotoXY(global::msg.x, global::msg.y);

                    global::atkCounter++;

                    UpdateQuestProgress_atkupgrade();
                    UpdateQuestProgress_atkupgrade2();
                    UpdateQuestProgress_atkupgrade3();
                    printf("공격력 +%d      ", global::up_atk); // 기존 메시지를 덮어쓰기 위해 공백 포함
                }
                else {
                    GotoXY(global::msg.x, global::msg.y);
                    global::GameSound::PlaySFX(5);
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
                    UpdateQuestProgress_hpupgrade2();
                    UpdateQuestProgress_hpupgrade3();
                    global::GameSound::PlaySFX(6);
                    printf("체력 +%d      ", global::up_hp); // 기존 메시지를 덮어쓰기 위해 공백 포함
                }
                else {
                    GotoXY(global::msg.x, global::msg.y);
                    global::GameSound::PlaySFX(5);
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
            printf("구매 = SPACE      ");
        }
        // 스페이스바를 처음 눌렀을 때만 실행 & 구매 횟수 체크
        if (global::gold >= 50 && global::input::IsSpaceKeyOn() && !global::WasSpaceKeyPressed && global::purchaseCount < maxPurchases) {
            global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록

            // 골드 차감
            global::gold -= 50;
            global::GameSound::PlaySFX(0);
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

    if (GetTickCount64() - autoGoldTime >= 3000) { // 3초(3000ms)마다 증가
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
            global::GameSound::StopBGM();
            global::GameSound::PlayBGM(1);
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

            //  유효한 인덱스인지 먼저 체크
            if (global::selectedQuestIndex >= global::questList.size()) {
                ShowQuestMessage("더 이상 수락할 퀘스트가 없습니다.");
                global::GameSound::PlaySFX(2);
            }
            else {
                Quest& q = global::questList[global::selectedQuestIndex];

                if (q.state == Quest::LOCKED) {
                    q.state = Quest::IN_PROGRESS;
                    ShowQuestMessage("'" + q.name + "' 퀘스트를 수락했습니다.");
                    global::GameSound::PlaySFX(2);
                }
                else {
                    ShowQuestMessage("이미 수락한 퀘스트입니다.                  ");
                    global::GameSound::PlaySFX(2);
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
                    std::string msg = "퀘스트: " + q.description + " (" + std::to_string(q.current) + "/" + std::to_string(q.goal) + ")            ";
                    global::GameSound::PlaySFX(2);
                    ShowQuestMessage(msg); // 3초간 중앙 출력
                    found = true;
                    break;
                }
            }

            if (!found) {
                ShowQuestMessage("진행 중인 퀘스트가 없습니다.         ");
                global::GameSound::PlaySFX(2);
            }

            global::input::Set(global::input::IsYKeyOn(), false);
        }
    }

    if (!global::input::IsYKeyOn()) {
        global::WasYKeyPressed = false;
    }
}


void UpdateQuestProgress_GoldMined() // 골드20원 수집 퀘스트  // 1번 퀘스트 골드 수집
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

void UpdateQuestProgress_atkupgrade() // 공격력 강화 성공 시 진행 // 2번 퀘스트 공격강화
{
    for (auto& q : global::questList)
    {
        if (q.name == "ATK 강화 1" && q.state == Quest::IN_PROGRESS)
        {
            q.current = global::atkCounter; // 공격력 강화 1회 성공 = 현재 강화 정도 확인

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_monsterAclear() // 몬스터 A처치 시 진행 // 3번 퀘스트 공격강화
{
    for (auto& q : global::questList)
    {
        if (q.name == "몬스터A 처치" && q.state == Quest::IN_PROGRESS)
        {
            q.current = global::battle::monsterA.hpFlag; // 몬스터 A 처치 성공 

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_hpupgrade() // 체력 강화 성공 시 진행 // 4번 퀘스트
{
    for (auto& q : global::questList)
    {
        if (q.name == "HP 강화 1" && q.state == Quest::IN_PROGRESS)
        {
            q.current = global::hpCounter; // 체력 강화 1회 성공 → 진행도 1 증가

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_atkupgrade2() // 공격력 강화 성공 시 진행 // 5번 퀘스트
{
    for (auto& q : global::questList)
    {
        if (q.name == "ATK 강화 2" && q.state == Quest::IN_PROGRESS)
        {
            q.current = global::atkCounter; // 공격력 강화 1회 성공 = 현재 강화 정도 확인

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_hpupgrade2() // 체력 강화 성공 시 진행 // 6번 퀘스트
{
    for (auto& q : global::questList)
    {
        if (q.name == "HP 강화 2" && q.state == Quest::IN_PROGRESS)
        {
            q.current = global::hpCounter; // 체력 강화 1회 성공 → 진행도 1 증가

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_monsterBclear() // 몬스터 B처치 시 진행 // 7번 퀘스트
{
    for (auto& q : global::questList)
    {
        if (q.name == "몬스터B 처치" && q.state == Quest::IN_PROGRESS)
        {
            q.current = global::battle::monsterB.hpFlag; // 몬스터 B 처치 성공 

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_atkupgrade3() // 공격력 강화 성공 시 진행 // 5번 퀘스트
{
    for (auto& q : global::questList)
    {
        if (q.name == "ATK 강화 3" && q.state == Quest::IN_PROGRESS)
        {
            q.current = global::atkCounter; // 공격력 강화 1회 성공 = 현재 강화 정도 확인

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void UpdateQuestProgress_hpupgrade3() // 체력 강화 성공 시 진행 // 6번 퀘스트
{
    for (auto& q : global::questList)
    {
        if (q.name == "HP 강화 3" && q.state == Quest::IN_PROGRESS)
        {
            q.current = global::hpCounter; // 체력 강화 1회 성공 → 진행도 1 증가

            if (q.IsComplete()) {
                q.state = Quest::COMPLETE;
                ShowQuestMessage("퀘스트 완료: " + q.name + " (보상 : 50G)");

                global::gold += 50;
                global::selectedQuestIndex++;
            }
        }
    }
}

void CheckOptionMenu()
{
    if (IsInsideZone(global::curPlayerPos, global::OptionZone))
    {
        GotoXY(global::msg.x, global::msg.y);
        printf("커서 변경 = Y        ");
        if (global::input::IsYKeyOn() && !global::WasYKeyPressed) {
            global::WasSpaceKeyPressed = true; // 키가 눌렸음을 기록


            //  여기에 배틀 시작 관련 함수 넣으면 됨!
            RunCursorSelectionMenu(); // 중앙 커서 선택 UI 호출

            // 키 입력 초기화 
            global::input::Set(global::input::IsYKeyOn(), false);
        }
    }


    if (!global::input::IsYKeyOn()) {
        global::WasYKeyPressed = false;
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
    global::heal_hp = 10 + (5 * global::hpCounter);
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
                global::GameSound::PlaySFX(2);
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

        if (GetTickCount64() - miningTime >= 500) { // 0.5초(500ms)마다 증가
            if (global::goldCounter < 10) { // 최대 10까지 증가
                global::goldCounter++;
                GotoXY(global::msg.x, global::msg.y);
                global::GameSound::PlaySFX(3);
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

            global::GameSound::PlaySFX(1);
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
    CheckOptionMenu();
    DrawMonster_info();


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
    printf("%s", global::playerIcon.c_str()); // 플레이어 위치이므로 #  >> 추후 다른 문자로 바꿀 예정 // ★, ☆ , ♀ , ∵ , ■ , д
}

void DrawTitleRect()
{
    for (int i = 18; i <= 29; i++) {
        GotoXY(i, 14);
        printf("@");
    }
    for (int i = 15; i < 18; i++) {
        GotoXY(18, i);
        printf("@");
    }
    for (int i = 18; i <= 29; i++) {
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

void DrawOptionRect() {
    setColor(8); // 회색
    for (int i = global::option_zone.a; i < global::option_zone.a + 1; i++) {
        GotoXY(i, global::option_zone.w);
        printf("■");

    }
    setColor(15); // 기존색으로 복귀


    GotoXY(2, 12);
    printf("O");
    GotoXY(2, 13);
    printf("P");
    GotoXY(2, 14);
    printf("T");
    GotoXY(2, 15);
    printf("I");
    GotoXY(2, 16);
    printf("O");
    GotoXY(2, 17);
    printf("N");


    setColor(8); // 회색
    for (int i = global::option_zone.w; i <= global::option_zone.s; i++) {
        GotoXY(global::option_zone.a + 1, i);
        printf("■");

    }


    for (int i = global::option_zone.a; i <= global::option_zone.a + 1; i++) {
        GotoXY(i, global::option_zone.s);
        printf("■");
        GotoXY(i, global::option_zone.s);
        printf("■");
    }
    setColor(15); // 기존색으로 복귀
}


void DrawMonster_info() {
    if (!global::battle::monsterA.hpFlag) {
        GotoXY(95, 2);
        printf("MonsterA : 슬라임");

        COORD start = { 91, 4 };

        std::string art[] = {
            "          ▒▒▒▒▒▒          ",
            "        ▒▒      ▒▒        ",
            "      ▒▒          ▒▒      ",
            "    ▒▒              ▒▒    ",
            "  ▒▒   ●         ●    ▒▒  ",
            "   ▒▒     ______     ▒▒   ",
            "     ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒     "
        };

        setColor(10);
        for (int i = 0; i < 7; ++i) {
            COORD pos = { start.X, static_cast<SHORT>(start.Y + i) };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            std::wcout << art[i].c_str();
        }
        setColor(15);
        GotoXY(95, 11);
        printf("HP : %d , ATK : %d", global::battle::monsterA.heart, global::battle::monsterA.attack);
    }
    else if (!global::battle::monsterB.hpFlag) {
        GotoXY(95, 2);
        printf("MonsterB : 스켈레톤");

        COORD start = { 93, 3 };

        std::string art[] = {
            "       ▒▒▒▒▒▒▒▒▒▒▒      ",
            "      ▒           ▒     ",
            "     ▒   |\\   /|   ▒   ",
            "     ▒   |_\\ /_|   ▒   ",
            "      ▒           ▒     ",
            "       ▒         ▒      ",
            "       ▒|▒|▒|▒|▒|▒      ",
            "        ▒▒▒▒▒▒▒▒▒       "

        };

        setColor(8);
        for (int i = 0; i < 8; ++i) {
            COORD pos = { start.X, static_cast<SHORT>(start.Y + i) };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            std::wcout << art[i].c_str();
        }
        setColor(15);
        GotoXY(95, 11);
        printf("HP : %d , ATK : %d", global::battle::monsterB.heart, global::battle::monsterB.attack);
    }
    else if (!global::battle::monsterC.hpFlag) {
        GotoXY(100, 2);
        printf("BOSS : 마녀");

        COORD start = { 91, 3 };

        std::string art[] = {
            "            ▒▒            ",
            "           ▒  ▒           ",
            "          ▒    ▒        ",
            "        ▒▒      ▒▒      ",
            "       ▒          ▒    ",
            "      ▒▒▒▒▒▒★ ▒▒▒▒▒▒  ",
            "     ▒              ▒   ",
            " ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"
        };

        setColor(4);
        for (int i = 0; i < 8; ++i) {
            COORD pos = { start.X, static_cast<SHORT>(start.Y + i) };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            std::wcout << art[i].c_str();
        }
        setColor(15);
        GotoXY(95, 11);
        printf("HP : %d , ATK : %d", global::battle::monsterC.heart, global::battle::monsterC.attack);
    }
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
    printf("MINE 2G/S");
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


void DrawDungeonRect() { //
    setColor(8);
    for (int y = global::playerMovableRect.Top; y < global::playerMovableRect.Bottom - 4; y++) { // top- 1 에서 임시로 +1로 변경
        GotoXY(90, y);
        printf("■");
        //putchar('@');
    }
    for (int y = global::playerMovableRect.Top; y < global::playerMovableRect.Bottom - 4; y++) {
        GotoXY(89, y);
        printf("■");
        //putchar('@');
    }
    for (int y = global::playerMovableRect.Top; y < global::playerMovableRect.Bottom - 4; y++) {
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

void RunCursorSelectionMenu()
{

    setConsoleSize(120, 30);
    GotoXY(global::msg.x, global::msg.y);
    printf("선택 = SPACE");



    const std::vector<std::string>& options = global::playerIconOptions;
    int currentIndex = 0;

    const int centerX = 50;
    const int centerY = 10;

    while (true)
    {


        // UI 타이틀
        GotoXY(centerX, centerY + 1);
        std::cout << "플레이어 기호 선택";

        // 기호 리스트 출력
        for (int i = 0; i < options.size(); ++i)
        {
            GotoXY(centerX + 2, centerY + i + 2);
            if (i == currentIndex)
            {
                setColor(11); // 밝은 파랑
                std::cout << "▶ " << options[i];
                setColor(15);
            }
            else
            {
                std::cout << "   " << options[i];
            }
        }

        global::input::UpdateInput();

        if (global::input::IsUpKeyOn())
        {
            currentIndex = (currentIndex - 1 + options.size()) % options.size();
            Sleep(150);
        }
        else if (global::input::IsDownKeyOn())
        {
            currentIndex = (currentIndex + 1) % options.size();
            Sleep(150);
        }
        else if (global::input::IsSpaceKeyOn())
        {
            global::playerIcon = options[currentIndex];
            break;
        }

    }

    system("cls");
    startGame(); // 게임 화면 다시 그리기
}


/// <summary>
/// 게임 설명 창 그리기
/// </summary>
void RenderTutorial()
{
    int x = 10;
    int y = 5;
    for (int i = 7; i < 19; i++)
    {
        GotoXY(48, i);
        std::cout << "|" << std::endl;
    }
    GotoXY(50, y + 3);
    std::cout << "<< 조작 방법 >>" << std::endl;

    GotoXY(50, y + 6);
    std::cout << "1. Mine 영역에서 골드 캐기 ! " << std::endl;
    GotoXY(50, y + 7);
    std::cout << "2. 침대 옆 Auto Money로 이동하여 골드 모으기 ! " << std::endl;
    GotoXY(50, y + 8);
    std::cout << "3. '공격 강화 구역' '체력 강화 구역' 에서 골드로 캐릭터 강화하기!" << std::endl;
    GotoXY(50, y + 9);
    std::cout << "4. 왼쪽 상단에서 퀘스트 수락하여 미션 수행하기 !" << std::endl;
    GotoXY(50, y + 10);
    std::cout << "5. 퀘스트 목록에서 퀘스트 내용 확인하기 !" << std::endl;
    GotoXY(50, y + 11);
    std::cout << "6. 보스 방으로 입장하여 몬스터와 전투하기 !" << std::endl;
    GotoXY(50, y + 12);
    std::cout << "7. 침대로 이동하여 HP 회복하기 ! " << std::endl;

    GotoXY(13, y + 3);
    std::cout << " << 조작 키 >>" << std::endl;
    GotoXY(13, y + 6);
    std::cout << " [↑] [↓] [←] [→]   플레이어 이동" << std::endl;
    GotoXY(13, y + 8);
    std::cout << " [Space Bar]   강화, 입장" << std::endl;
    GotoXY(13, y + 10);
    std::cout << " [Y]   확인" << std::endl;

    GotoXY(40, y + 16);
    std::cout << "<< [Y] 누르면 첫화면으로 >>" << std::endl;
}

/// <summary>
/// 게임 설명 창
/// </summary>
void TutorialPage()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, }; // 커서 관련 정보 구조체
    cursorInfo.bVisible = 0; // 0 이면 커서 숨김, 1이면 커서 보임
    cursorInfo.dwSize = 1; // 커서 크기 1~100
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // 핸들 불러서 커서 

    CONSOLE_SCREEN_BUFFER_INFO csbi; // 콘솔 화면 버퍼 정보 구조체
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    global::consoleScreenSize.Left = csbi.srWindow.Left; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 0
    global::consoleScreenSize.Right = csbi.srWindow.Right; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 0
    global::consoleScreenSize.Bottom = csbi.srWindow.Bottom; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 169
    global::consoleScreenSize.Top = csbi.srWindow.Top; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 50

    global::playerMovableRect.Left = global::consoleScreenSize.Left + 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Right = global::consoleScreenSize.Right - 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Bottom = global::consoleScreenSize.Bottom - 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Top = global::consoleScreenSize.Top + 2; // 플레이어 이동 범위 제한

    DrawMovableRect(); // 테두리 벽 생성

    system("cls");
    DrawMovableRect(); // 테두리 벽 생성
    while (IsGameRun())
    {
        global::time::UpdateTime();
        ProcessInput();
        FixedUpdate();
        RenderTutorial();
        if (global::gametutorialflag == true) break;
        if (global::input::IsYKeyOn())
        {
            system("cls");
            break;
        }
    }
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
/// 방향키 움직이기, 화살표 출력, clamp 함수 넣어 테스트 해보아야함
/// </summary>
void MoveSelectMenu()
{
    DrawPlayer(false);
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

    int x = 23;
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

    GotoXY(x + 29, y + 10);
    std::cout << "게임 시작" << std::endl;
    GotoXY(x + 29, y + 11);
    std::cout << "게임 설명" << std::endl;
    GotoXY(x + 29, y + 12);
    std::cout << "게임 종료" << std::endl;

    GotoXY(x + 72, y + 19);
    std::cout << "<< 제작 >> " << std::endl;
    GotoXY(x + 63, y + 21);
    std::cout << "[ 박준혁   윤동민   김예은 ]" << std::endl;
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

    global::consoleScreenSize.Left = csbi.srWindow.Left; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 0
    global::consoleScreenSize.Right = csbi.srWindow.Right; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 0
    global::consoleScreenSize.Bottom = csbi.srWindow.Bottom; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 169
    global::consoleScreenSize.Top = csbi.srWindow.Top; // 버퍼의 크기로 콘솔 화면의 크기 설정 >> 50

    global::playerMovableRect.Left = global::consoleScreenSize.Left + 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Right = global::consoleScreenSize.Right - 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Bottom = global::consoleScreenSize.Bottom - 2; // 플레이어 이동 범위 제한
    global::playerMovableRect.Top = global::consoleScreenSize.Top + 2; // 플레이어 이동 범위 제한

    DrawMovableRect(); // 테두리 벽 생성

    global::prePlayerPos.X = 50;
    global::prePlayerPos.Y = 15;
    global::curPlayerPos.X = 50;
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
    DrawOptionRect(); //옵션 벽 생성

    global::prePlayerPos.X = 10;
    global::prePlayerPos.Y = 20;
    global::curPlayerPos.X = 10;
    global::curPlayerPos.Y = 20; // 플레이어 시작 위치

    DrawPlayer(false); // 플레이어 생성
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // 시드를 시간으로 변경
    global::GameSound::GameSoundInit();
    global::time::InitTime(); // 시간 초기화
    global::GameSound::PlayBGM(0);
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
        global::GameSound::SoundUpdate();
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
        global::GameSound::SoundUpdate();
    }

    return 0;
}

bool IsGameRun() // 게임 루프
{
    return true;
}

