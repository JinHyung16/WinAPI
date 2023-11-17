#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	// FPS
	// 1������ �� �ð� == Delta Time
	LARGE_INTEGER mCurCount;
	LARGE_INTEGER mPrevCount;
	LARGE_INTEGER mCurFrequency;

	double mDeltaTime; // �����Ӱ� ������ ���� �ɸ� �ð�
	double mAcc; // delta time�� ������ ��
	UINT mCallCount; // �Լ� ȣ�� Ƚ��
	UINT mFPS; // �ʴ� ȣ�� Ƚ�� (FPS)

public:
	void init();
	void update();
	double GetDeltaTime() { return mDeltaTime; }
	float GetDeltaTimeF() { return (float)mDeltaTime; }
};

