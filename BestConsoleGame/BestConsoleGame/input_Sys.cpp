#include <windows.h>
#include <cassert>
#include "Input_Sys.h"


namespace global
{
	namespace input
	{
		bool inputKeyTable[MAX_KEY]; // ���ǵ� 5���� Ű ���� ó�� �մϴ�.

		// Helper Functions ..
		void Set(const int keyIdx, bool bOn)
		{
			assert(keyIdx >= 0 && keyIdx < MAX_KEY); // ��� �ڵ带 �ۼ��ϴ� �Ϳ� �ͼ������� �մϴ�.  �迭�� �ٷ� ���� �ε����� �����ؾ� �մϴ�!!

			inputKeyTable[keyIdx] = bOn;			// bool Ÿ���� Ȱ�� �սô�.
		}
		// ���� Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsLeftKeyOn()
		{
			return inputKeyTable[LEFT_KEY_INDEX]; //Ű���̺� ����Ű �ε����� �� ��ȯ 1
		}
		// ������ Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsRightKeyOn()
		{
			return inputKeyTable[RIGHT_KEY_INDEX]; //Ű���̺� ������Ű �ε����� �� ��ȯ 2
		}
		// ���� Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsUpKeyOn()
		{
			return inputKeyTable[UP_KEY_INDEX]; //Ű���̺� ����Ű �ε����� �� ��ȯ 3
		}
		// �Ʒ��� Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsDownKeyOn()
		{
			return inputKeyTable[DOWN_KEY_INDEX]; //Ű���̺� �Ʒ���Ű �ε����� �� ��ȯ 4
		}
		// �����̽� Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsSpaceKeyOn()
		{
			return inputKeyTable[Space_KEY_INDEX]; //Ű���̺� �����̽�Ű �ε����� �� ��ȯ 5
		}

		bool IsYKeyOn()
		{
			return inputKeyTable[Y_KEY_INDEX]; // �ε��� 6 (Y Ű �Է� ����)
		}
		bool IsEnterKeyOn()
		{
			return inputKeyTable[Enter_KEY_INDEX]; // �ε��� 7 (Y Ű �Է� ����)
		}

		// �Է� Ű���� ���� �˾� ���ô�. ��ŷ�� �ͺ�ŷ�� ���ؼ��� �����ϰ� ����� �մϴ�!!
		// * ��Ʈ ���꿡 ���� �н��մϴ�. & �� && �� �޶��. 
		// &, * �����ڰ� �ƶ��� ���� �ٸ��� �ؼ��Ǵ� �Ϳ� ���� �ؾ� �մϴ�. 

		//Ű �Է¿� ���� ���� ������Ʈ ���ִ� �Լ�
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

			// ����
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				global::input::Set(LEFT_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(LEFT_KEY_INDEX, false);
			}

			// ������
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				global::input::Set(RIGHT_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(RIGHT_KEY_INDEX, false);
			}

			// ��
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				global::input::Set(UP_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(UP_KEY_INDEX, false);
			}

			// �Ʒ�
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				global::input::Set(DOWN_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(DOWN_KEY_INDEX, false);
			}

			// �����̽��� (Ű�� ���� false�� �ʱ�ȭ)
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				global::input::Set(Space_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(Space_KEY_INDEX, false);
			}

			// YŰ (Ű�� ���� false�� �ʱ�ȭ)
			if (GetAsyncKeyState(0x59) & 0x8000)
			{
				global::input::Set(Y_KEY_INDEX, true);
			}
			else
			{
				global::input::Set(Y_KEY_INDEX, false);
			}
			// EnterŰ (Ű�� ���� false�� �ʱ�ȭ)
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



