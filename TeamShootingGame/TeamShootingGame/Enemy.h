#pragma once
#include "pch.h"
#include "GameNode.h"

class EMissileManager;
class Image;
class Enemy : public GameNode
{
private:
	FPOINT pos;
	FPOINT targetPos;
	int size;
	int life;
	int currFrameX, currFrameY;
	float animationTime;
	float fireTime;
	float secondFireDelay;
	float movePosY;
	float destAngle;
	float angle;
	float tempAngle;
	float addAngle;
	int count;
	bool isPingpong;
	
	EMissileManager* missileMgr;
	Image* img;


public:
	HRESULT Init();
	void Release();
	void Update(EnemyName name , float fireDelay);
	void Render(HDC hdc, EnemyName name, Mode mode);

	void Move();
	void Fire(EnemyName name);

	FPOINT GetEnemyPos() { return pos; }
	void SetTargetPos(FPOINT targetPos) { this->targetPos = targetPos; }
};

