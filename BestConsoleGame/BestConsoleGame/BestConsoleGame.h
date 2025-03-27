#pragma once

namespace global {
    extern int hp;
    extern int atk;
    extern int max_hp;
}

void startGame();
void setColor(int color);
void ShowQuestMessage(const std::string& msg); // 메시지 출력 시간 조절 함수
void UpdateQuestProgress_monsterAclear();
void UpdateQuestProgress_monsterBclear();
