#pragma once

// Singleton 패턴으로 객체 1개로 제한

// 정적 변수 (데이터 영역에 존재) -> 결론은 딱 1개의 데이터만 데이터 영역에 존재한다.
// 1. 함수 내 -> 함수 호출이 끝나도 메모리는 남아있다.
// 2. 파일 내 -> 다른 class에서 이름 중복되어도 사용 가능
// 3. 클래스 내 -> 클래스 내 멤버 함수에서만 접근 가능, 100개 1000개 있든 메모리는 오로지 1개

// 만약 static CCore *core가 GetInstance함수 내 정적 멤버 함수였다면, Release()에서 core 객체를 지우고
// 다시 GetInstance를 한다면, 이 정적 멤버 함수 내 정적 멤버 변수인 core는 사라진 객체의 주소를 들고있기에
// core != nullptr로 존재하지 않은 객체의 주소를 반환하기에 문제가 생긴다.
// 이를 해결하기 위해 CCore를 클래스 내 정적 멤버 변수로 선언한다.

/*
class CCore
{
private:

	static CCore *core;

public :

	static CCore* GetInstance()
	{
		if (core == nullptr)
		{
			core = new CCore;
		}

		return core;
	}

	static void Release()
	{
		if (core != nullptr)
		{
			delete core;
			core = nullptr;
		}
	}

private:
	// 생성자를 숨겨서 외부에서 막 인스턴스 하는걸 방지
	CCore();
	~CCore();
};
*/

/*
/// <summary>
/// 데이터 영역에 올리는 방법
/// 데이터를 해제하는걸 고민하지 않아도 된다.
/// 왜? 프로그램이 종료되면 알아서 해제되니깐
/// </summary>
class CCore
{
public:
	static CCore* GetInstance()
	{
		static CCore core; // 데이터 영역에 생성
		return &core; // 주소값을 전달한다.
	}

private:
	CCore();
	~CCore();
};
*/

/// <summary>
/// 데이터 영역에 올려 쓰는 CCore를 매크로로 만들기
/// Define.h에 미리 선언해둔다. -> pch.h를 이용해 헤더 참조 최적화
/// </summary>

class CCore
{
	SINGLE(CCore);
private:
	HWND c_hwnd; // 메인 윈도우 핸들
	POINT c_ptResolution; // 메인 윈도우 해상도
	HDC c_hdc; // 메인 윈도우에 draw할 DC
public:
	int init(HWND _hwnd, POINT _resolution); // main에서 윈도우 메인 핸들러와 해상도 받아 초기화
	void progress(); // 실제 계속해서 처리할 함수

private:
	void update();
	void render();

private:
	CCore();
	~CCore();
};

