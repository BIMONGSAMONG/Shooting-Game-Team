#pragma once
#include "pch.h"
#include "GameNode.h"

class EMissile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float angle;
	bool isFire;
	float speed;
	float goalTime;

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
};

