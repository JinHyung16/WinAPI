#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
{
	mCurCount = {};
	mCurFrequency = {};
	mPrevCount = {};

	mDeltaTime = 0.0;
	mAcc = 0.0;
	mCallCount = 0;
	mFPS = 0;
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&mPrevCount);

	// �ʴ� ī��Ʈ
	QueryPerformanceFrequency(&mCurFrequency); // 1�ʴ� count�� ��� ���� �Ͼ����
}

void CTimeMgr::update()
{
	// Delta Time�� ���ϱ� ���� ����
	QueryPerformanceCounter(&mCurCount);

	// ���� �������� ī���ð� ���� �������� ī������ ���̸� ���� �ʴ� ī��Ʈ�� ���� �����Ӱ��� �ð� ���̸� ���Ѵ�.
	mDeltaTime = (double)(mCurCount.QuadPart - mPrevCount.QuadPart) / (double)(mCurFrequency.QuadPart);

	// ���� ī��Ʈ ���� ���� ī��Ʈ ������ ��ü�Ѵ�.
	mPrevCount = mCurCount;

	mCallCount += 1;
	mAcc += mDeltaTime;
	if (1.0 <= mAcc)
	{
		mFPS = mCallCount;
		mAcc = 0.0;
		mCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %1f", mFPS, mDeltaTime);
		SetWindowText(CCore::GetInstance()->GetMainHwnd(), szBuffer);
	}
}