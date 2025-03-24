#include <windows.h>
#include <cassert>
#include "Input_Sys.h"


namespace global
{
	namespace input
	{
		bool inputKeyTable[MAX_KEY]; // 정의된 5개의 키 값을 처리 합니다.

		// Helper Functions ..
		void Set(const int keyIdx, bool bOn)
		{
			assert(keyIdx >= 0 && keyIdx < MAX_KEY); // 방어 코드를 작성하는 것에 익숙해져야 합니다.  배열을 다룰 때는 인덱스를 조심해야 합니다!!

			inputKeyTable[keyIdx] = bOn;			// bool 타입을 활용 합시다.
		}
		// 왼쪽 키가 눌렸는지 확인하는 함수
		bool IsLeftKeyOn()
		{
			return inputKeyTable[LEFT_KEY_INDEX]; //키테이블 왼쪽키 인덱스의 값 반환 1
		}
		// 오른쪽 키가 눌렸는지 확인하는 함수
		bool IsRightKeyOn()
		{
			return inputKeyTable[RIGHT_KEY_INDEX]; //키테이블 오른쪽키 인덱스의 값 반환 2
		}
		// 위쪽 키가 눌렸는지 확인하는 함수
		bool IsUpKeyOn()
		{
			return inputKeyTable[UP_KEY_INDEX]; //키테이블 위쪽키 인덱스의 값 반환 3
		}
		// 아래쪽 키가 눌렸는지 확인하는 함수
		bool IsDownKeyOn()
		{
			return inputKeyTable[DOWN_KEY_INDEX]; //키테이블 아래쪽키 인덱스의 값 반환 4
		}
		// 스페이스 키가 눌렸는지 확인하는 함수
		bool IsSpaceKeyOn()
		{
			return inputKeyTable[Space_KEY_INDEX]; //키테이블 스페이스키 인덱스의 값 반환 5
		}

		bool IsYKeyOn()
		{
			return inputKeyTable[Y_KEY_INDEX]; // 인덱스 6 (Y 키 입력 감지)
		}
		bool IsEnterKeyOn()
		{
			return inputKeyTable[Enter_KEY_INDEX]; // 인덱스 7 (Y 키 입력 감지)
		}

		// 입력 키값에 대해 알아 봅시다. 블러킹과 넌블러킹에 대해서만 이해하고 가기로 합니다!!
		// * 비트 연산에 대해 학습합니다. & 와 && 은 달라요. 
		// &, * 연산자가 맥락에 따라 다르게 해석되는 것에 주의 해야 합니다. 

		//키 입력에 따라 값을 업데이트 해주는 함수
		void UpdateInput()
		{
			// ESC
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				global::input::Set(ESCAPE_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(ESCAPE_KEY_INDEX, false);
			}

			// 왼쪽
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				global::input::Set(LEFT_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(LEFT_KEY_INDEX, false);
			}

			// 오른쪽
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				global::input::Set(RIGHT_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(RIGHT_KEY_INDEX, false);
			}

			// 위
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				global::input::Set(UP_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(UP_KEY_INDEX, false);
			}

			// 아래
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				global::input::Set(DOWN_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(DOWN_KEY_INDEX, false);
			}

			// 스페이스바 (키를 떼면 false로 초기화)
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				global::input::Set(Space_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(Space_KEY_INDEX, false);
			}

			// Y키 (키를 떼면 false로 초기화)
			if (GetAsyncKeyState(0x59) & 0x8000)
			{
				global::input::Set(Y_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(Y_KEY_INDEX, false);
			}
			// Enter키 (키를 떼면 false로 초기화)
			if (GetAsyncKeyState(0x0D) & 0x8000)
			{
				global::input::Set(Enter_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(Enter_KEY_INDEX, false);
			}
		}

	};
};



