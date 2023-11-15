#pragma once

// Singleton �������� ��ü 1���� ����

// ���� ���� (������ ������ ����) -> ����� �� 1���� �����͸� ������ ������ �����Ѵ�.
// 1. �Լ� �� -> �Լ� ȣ���� ������ �޸𸮴� �����ִ�.
// 2. ���� �� -> �ٸ� class���� �̸� �ߺ��Ǿ ��� ����
// 3. Ŭ���� �� -> Ŭ���� �� ��� �Լ������� ���� ����, 100�� 1000�� �ֵ� �޸𸮴� ������ 1��

// ���� static CCore *core�� GetInstance�Լ� �� ���� ��� �Լ����ٸ�, Release()���� core ��ü�� �����
// �ٽ� GetInstance�� �Ѵٸ�, �� ���� ��� �Լ� �� ���� ��� ������ core�� ����� ��ü�� �ּҸ� ����ֱ⿡
// core != nullptr�� �������� ���� ��ü�� �ּҸ� ��ȯ�ϱ⿡ ������ �����.
// �̸� �ذ��ϱ� ���� CCore�� Ŭ���� �� ���� ��� ������ �����Ѵ�.

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
	// �����ڸ� ���ܼ� �ܺο��� �� �ν��Ͻ� �ϴ°� ����
	CCore();
	~CCore();
};
*/

/*
/// <summary>
/// ������ ������ �ø��� ���
/// �����͸� �����ϴ°� ������� �ʾƵ� �ȴ�.
/// ��? ���α׷��� ����Ǹ� �˾Ƽ� �����Ǵϱ�
/// </summary>
class CCore
{
public:
	static CCore* GetInstance()
	{
		static CCore core; // ������ ������ ����
		return &core; // �ּҰ��� �����Ѵ�.
	}

private:
	CCore();
	~CCore();
};
*/

/// <summary>
/// ������ ������ �÷� ���� CCore�� ��ũ�η� �����
/// Define.h�� �̸� �����صд�. -> pch.h�� �̿��� ��� ���� ����ȭ
/// </summary>

class CCore
{
	SINGLE(CCore);
private:
	HWND c_hwnd; // ���� ������ �ڵ�
	POINT c_ptResolution; // ���� ������ �ػ�
	HDC c_hdc; // ���� �����쿡 draw�� DC
public:
	int init(HWND _hwnd, POINT _resolution); // main���� ������ ���� �ڵ鷯�� �ػ� �޾� �ʱ�ȭ
	void progress(); // ���� ����ؼ� ó���� �Լ�

private:
	void update();
	void render();

private:
	CCore();
	~CCore();
};

