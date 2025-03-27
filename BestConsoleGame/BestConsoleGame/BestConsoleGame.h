#pragma once


namespace global 
{
    extern int gold;
    extern int hp;
    extern int atk;
    extern int max_hp;
    extern bool gamestartflag;

    namespace GameSound
    {
        void PlaySFX(int index);
        void PlayBGM(int index);
        void SoundUpdate();
        void StopBGM();
    }
    namespace time 
    {
        void UpdateTime();
    }

    void resetCounter();
}

void startGame();
void setColor(int color);
void ShowQuestMessage(const std::string& msg);
void UpdateQuestProgress_monsterAclear();
void UpdateQuestProgress_monsterBclear();

void OpeningTitle();
void MoveSelectMenu();
void FixedUpdate();
void RenderOpening();
void ProcessInput();

