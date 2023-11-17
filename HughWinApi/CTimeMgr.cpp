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
	// 현재 카운트
	QueryPerformanceCounter(&mPrevCount);

	// 초당 카운트
	QueryPerformanceFrequency(&mCurFrequency); // 1초당 count가 몇번 자주 일어나는지
}

void CTimeMgr::update()
{
	// Delta Time을 구하기 위한 공식
	QueryPerformanceCounter(&mCurCount);

	// 이전 프레임의 카운팅과 현재 프레임의 카운팅의 차이를 구해 초당 카운트로 나눠 프레임간의 시간 차이를 구한다.
	mDeltaTime = (double)(mCurCount.QuadPart - mPrevCount.QuadPart) / (double)(mCurFrequency.QuadPart);

	// 이전 카운트 값을 현재 카운트 값으로 대체한다.
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