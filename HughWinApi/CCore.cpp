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

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, c_ptResolution.x, c_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	SetWindowPos(c_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	c_hdc = GetDC(c_hwnd);

	cObj.m_pos = POINT{ c_ptResolution.x / 2, c_ptResolution.y / 2 };
	cObj.m_scale = POINT{ 100, 100 };

	return S_OK; // pch.h�� S_OK �ǹ�
}

void CCore::progress()
{
	// �޽����� ó������ ���� �� �׻� ó���Ǵ� �Լ�
	update();
	render();
}

void CCore::update()
{
	// ��Ʈ �����ؼ� 0x8000 �ڸ��� �ִٸ� true ��ȯ
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