#include "pch.h"
#include "CCore.h"
#include "CObject.h"

// CCore* CCore::core = nullptr;

CObject cObj;

CCore::CCore()
{
	c_hwnd = nullptr;
	c_ptResolution = {};
	c_hdc = nullptr;
}

CCore::~CCore()
{
	ReleaseDC(c_hwnd, c_hdc);
}

int CCore::init(HWND _hwnd, POINT _resolution)
{
	c_hwnd = _hwnd;
	c_ptResolution = _resolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0, c_ptResolution.x, c_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	SetWindowPos(c_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	c_hdc = GetDC(c_hwnd);

	cObj.m_pos = POINT{ c_ptResolution.x / 2, c_ptResolution.y / 2 };
	cObj.m_scale = POINT{ 100, 100 };

	return S_OK; // pch.h의 S_OK 의미
}

void CCore::progress()
{
	// 메시지가 처리되지 않을 때 항상 처리되는 함수
	update();
	render();
}

void CCore::update()
{
	// 비트 연산해서 0x8000 자리에 있다면 true 반환
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		cObj.m_pos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		cObj.m_pos.x += 1;
	}
}

void CCore::render()
{
	Rectangle(c_hdc, cObj.m_pos.x - cObj.m_scale.x / 2, 
		cObj.m_pos.y - cObj.m_scale.y / 2, 
		cObj.m_pos.x + cObj.m_scale.x / 2, 
		cObj.m_pos.y + cObj.m_scale.y / 2);
}