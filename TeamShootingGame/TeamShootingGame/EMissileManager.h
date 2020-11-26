#pragma once
#include "GameNode.h"
#include <vector>

class EMissile;
class EMissileManager :public GameNode
{
private:
	vector<EMissile*> vecMissiles;
	vector<EMissile*>::iterator itMissiles;
	FPOINT targetPos;
	FPOINT randomPos;
	FPOINT vertexPos1;
	FPOINT vertexPos2;

	FPOINT rotatePos3;
	FPOINT rotatePos4;
	
	int enemyMissileCount;
	bool isPingPong;
	bool isPattern;
	bool isShoot;
	bool isShake;

	float angle;
	float addAngle1;
	float addAngle2;
	float destAngle1;
	float destAngle2;
	float fireTime;

	int bulletCount;
	int count;
	int life;
	int bossLife;
	float random;
	float clearBullet;

	bool phaseTwo;
	bool lastPhase;
	float randomAngle;
	float randomSpeed;
	int  randomPhase;
	int randomAddAngle;

	int BossLife;

	Phase phase;

public:
	HRESULT Init();
	void Release();
	void Update(EnemyName name, FPOINT pos, float destAngle, float fireDelay, Mode mode, FPOINT rotatePos1, FPOINT rotatePos2);
	void Render(HDC hdc, EnemyName name, Mode mode);

	void Fire(EnemyName name, FPOINT pos, float angle, Mode mode, FPOINT rotatePos1, FPOINT rotatePos2);
	void SetIsPingPong(bool isPingPong) { this->isPingPong = isPingPong; }
	void SetTargetPos(FPOINT targetPos) { this->targetPos = targetPos; }

	vector<EMissile*> GetVecMissiles() { return vecMissiles; }
	int GetMissileCount() { return enemyMissileCount; }
	void SetIsShoot(bool isShoot) { this->isShoot = isShoot; }
	void SetLife(int life) { this->life = life; }

	int GetBossLife() { return bossLife; }
	void SetBossLife(int bossLife) { this->bossLife = bossLife; }

	bool GetIsShake() { return isShake; }
	void SetPhase(Phase phase) { this->phase = phase; }
	void SetMissileCount(int enemyMissileCount) { this->enemyMissileCount = enemyMissileCount; }

};