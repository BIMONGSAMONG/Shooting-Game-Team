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
	float movePosY;
	float destAngle;

	EnemyName name;
	Mode mode;
	float fireDelay;
	
	EMissileManager* missileMgr;
	Image* img;

public:
	HRESULT Init();
	void Release();
	void Update(EnemyName name);
	void Render(HDC hdc, EnemyName name, Mode mode);

	void Move();
	void Fire(EnemyName name);

	FPOINT GetEnemyPos() { return pos; }

	void SetEnemyName(EnemyName name) { this->name = name; }
	void SetMode(Mode mode) { this->mode = mode; }
	void SetTargetPos(FPOINT targetPos) { this->targetPos = targetPos; }
};

