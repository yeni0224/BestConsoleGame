#pragma once


namespace global {
    extern int gold;
    extern int hp;
    extern int atk;
    extern int max_hp;

    namespace GameSound {
        void PlaySFX(int x);
    }
}

void startGame();
void setColor(int color);
void ShowQuestMessage(const std::string& msg);
void UpdateQuestProgress_monsterAclear();
void UpdateQuestProgress_monsterBclear();

