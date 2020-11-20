#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
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
	float timer;
	Image* img;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc, EnemyName name, Mode mode);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool isFire) { this->isFire = isFire; }
	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT GetPos() { return pos; }
	int GetSize() { return size; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetAngle(float angle) { this->angle = angle; }
	void SetIsPingPong(bool isPingPong) { this->isPingPong = isPingPong; }
};

