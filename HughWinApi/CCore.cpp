#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
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

	// Manager Init
	CTimeMgr::GetInstance()->init();

	cObj.SetPos(Vector2((float)(c_ptResolution.x / 2), (float)(c_ptResolution.y / 2)));
	cObj.SetScale(Vector2(100, 100));

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
	// Manager Update
	CTimeMgr::GetInstance()->update();

	Vector2 curPos = cObj.GetPos();
	// ��Ʈ �����ؼ� 0x8000 �ڸ��� �ִٸ� true ��ȯ
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		curPos.x -= 100.0f * fDeltaTime
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		curPos.x += 100.0f * fDeltaTime;
	}
	cObj.SetPos(curPos);
}

void CCore::render()
{
	Vector2 curPos = cObj.GetPos();
	Vector2 curScale = cObj.GetScale();

	Rectangle(c_hdc, int(curPos.x - curScale.x / 2.0f),
		int(curPos.y - curScale.y / 2.0f),
		int(curPos.x + curScale.x / 2.0f),
		int(curPos.y + curScale.y / 2.0f));
}