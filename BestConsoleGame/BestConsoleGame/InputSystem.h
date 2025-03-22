#pragma once
namespace global
{
	// 함수의 선언과 정의 개념에 대해 생각해 봅시다.
	// 필요한 인터페이스만 노출한다는 개념에 대해 생각해 봅시다.
	namespace input
	{
		// 상수를 정의 하는 방법에 대해 알아 봅시다. 
		// const 키와 #define 의 차이를 알아야 합니다. 힌트! const 는 변수에 붙은 키워드이고 #이 붙으면 프리컴파일에 결정 됩니다.
		constexpr int ESCAPE_KEY_INDEX = 0; // 방어코드
		constexpr int LEFT_KEY_INDEX = 1; // 왼쪽 키
		constexpr int RIGHT_KEY_INDEX = 2; // 오른쪽 키
		constexpr int UP_KEY_INDEX = 3; //	위쪽 키
		constexpr int DOWN_KEY_INDEX = 4;// 아래쪽 키
		constexpr int Space_KEY_INDEX = 5; // 스페이스 키

		const int MAX_KEY = 6;

		void Set(const int keyIdx, bool bOn);

		bool IsLeftKeyOn(); // 왼쪽 키가 눌렸는지 확인하는 함수
		bool IsRightKeyOn(); // 오른쪽 키가 눌렸는지 확인하는 함수
		bool IsUpKeyOn(); // 위쪽 키가 눌렸는지 확인하는 함수
		bool IsDownKeyOn(); // 아래쪽 키가 눌렸는지 확인하는 함수
		bool IsSpaceKeyOn(); // 스페이스 키가 눌렸는지 확인하는 함수

		void UpdateInput();
	};
};