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
	int firstBerrierSize;
	int secondtBerrierSize;
	int finBossSize;
	int life;
	int finBossLife;
	int currFrameX, currFrameY;
	int currFrameX2, currFrameY2;
	Phase phase;
	float animationTime;
	float bossAnimationTime;
	float finBossAnimationTimer;
	float barrierTimer;
	float moveTimer;
	float movePosY;
	float destAngle;
	bool die;

	EnemyName name;
	Mode mode;
	float fireDelay;

	EMissileManager* missileMgr;
	Image* img;
	Image* bossImg[4];
	Image* Fin_Easy_Boss;
	Image* Fin_Hard_Boss;
	Image* BossBarrier1;
	Image* BossBarrier2;

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
	int GetFirstBerrierSize() { return firstBerrierSize; }
	int GetSecondBerrierSize() { return secondtBerrierSize; }
	int GetFinBossSize() { return finBossSize; }
	EnemyName GetEnemyName() { return name; }
	EMissileManager* GetMissileMgr() { return missileMgr; }
	Phase GetPhase() { return phase; }
	int GetLife() { return life; }
	int GetBossLife() { return finBossLife; }

	void SetEnemyName(EnemyName name) { this->name = name; }
	void SetMode(Mode mode) { this->mode = mode; }
	void SetTargetPos(FPOINT targetPos) { this->targetPos = targetPos; }
	void SetLife(int life) { this->life = life; }
	void SetBossLife(int finBossLife) { this->finBossLife = finBossLife; }
	
};