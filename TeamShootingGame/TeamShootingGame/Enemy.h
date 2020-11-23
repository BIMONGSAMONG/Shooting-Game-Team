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
	int bossSize;
	int life;
	int currFrameX, currFrameY;
	float animationTime;
	float bossAnimationTime;
	float movePosY;
	float destAngle;
	bool die;

	EnemyName name;
	Mode mode;
	float fireDelay;

	EMissileManager* missileMgr;
	Image* img;
	Image* bossImg[4];

	bool setLife;

public:
	HRESULT Init();
	void Release();
	void Update(EnemyName name, Mode mode);
	void Render(HDC hdc, EnemyName name, Mode mode);

	void Move();
	void Fire(EnemyName name, Mode mode);

	FPOINT GetEnemyPos() { return pos; }
	int GetSize() { return size; }
	int GetBossSize() { return bossSize; }
	EMissileManager* GetMissileMgr() { return missileMgr; }
	int GetLife() { return life; }

	void SetEnemyName(EnemyName name) { this->name = name; }
	void SetMode(Mode mode) { this->mode = mode; }
	void SetTargetPos(FPOINT targetPos) { this->targetPos = targetPos; }
	void SetLife(int life) { this->life = life; }
	
};