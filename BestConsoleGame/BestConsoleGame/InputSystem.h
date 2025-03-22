#pragma once
namespace global
{
	// �Լ��� ����� ���� ���信 ���� ������ ���ô�.
	// �ʿ��� �������̽��� �����Ѵٴ� ���信 ���� ������ ���ô�.
	namespace input
	{
		// ����� ���� �ϴ� ����� ���� �˾� ���ô�. 
		// const Ű�� #define �� ���̸� �˾ƾ� �մϴ�. ��Ʈ! const �� ������ ���� Ű�����̰� #�� ������ ���������Ͽ� ���� �˴ϴ�.
		constexpr int ESCAPE_KEY_INDEX = 0; // ����ڵ�
		constexpr int LEFT_KEY_INDEX = 1; // ���� Ű
		constexpr int RIGHT_KEY_INDEX = 2; // ������ Ű
		constexpr int UP_KEY_INDEX = 3; //	���� Ű
		constexpr int DOWN_KEY_INDEX = 4;// �Ʒ��� Ű
		constexpr int Space_KEY_INDEX = 5; // �����̽� Ű

		const int MAX_KEY = 6;

		void Set(const int keyIdx, bool bOn);

		bool IsLeftKeyOn(); // ���� Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsRightKeyOn(); // ������ Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsUpKeyOn(); // ���� Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsDownKeyOn(); // �Ʒ��� Ű�� ���ȴ��� Ȯ���ϴ� �Լ�
		bool IsSpaceKeyOn(); // �����̽� Ű�� ���ȴ��� Ȯ���ϴ� �Լ�

		void UpdateInput();
	};
};