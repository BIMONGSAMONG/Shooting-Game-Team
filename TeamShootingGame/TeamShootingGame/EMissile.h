#pragma once
#include "pch.h"
#include "GameNode.h"

class EMissile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float angle;
	float pingpongAngle[2];
	int random;
	bool isFire;
	float speed;
	float goalTime;
	bool isPingPong;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool isFire) { this->isFire = isFire; }
	void SetPos(FPOINT pos) { this->pos = pos; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetAngle(float angle) { this->angle = angle; }
	void SetIsPingPong(bool isPingPong) { this->isPingPong = isPingPong; }
};

