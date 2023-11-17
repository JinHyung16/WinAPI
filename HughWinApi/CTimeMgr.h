#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	// FPS
	// 1프레임 당 시간 == Delta Time
	LARGE_INTEGER mCurCount;
	LARGE_INTEGER mPrevCount;
	LARGE_INTEGER mCurFrequency;

	double mDeltaTime; // 프레임과 프레임 사이 걸린 시간
	double mAcc; // delta time을 누적한 값
	UINT mCallCount; // 함수 호출 횟수
	UINT mFPS; // 초당 호출 횟수 (FPS)

public:
	void init();
	void update();
	double GetDeltaTime() { return mDeltaTime; }
	float GetDeltaTimeF() { return (float)mDeltaTime; }
};

