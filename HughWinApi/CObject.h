#pragma once
class CObject
{
private:
	Vector2 mPos;
	Vector2 mScale;

public:
	void SetPos(Vector2 pos) { mPos = pos; }
	void SetScale(Vector2 scale) { mScale = scale; }

	Vector2 GetPos() { return mPos; }
	Vector2 GetScale() { return mScale; }
public:
	CObject();
	~CObject();
};

