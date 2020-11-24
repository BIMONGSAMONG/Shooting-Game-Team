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
	int phase;
	float random;
	float clearBullet;

	bool phaseTwo;
	bool lastPhase;
	float randomAngle;
	float randomSpeed;
	int  randomPhase;
	Phase phase;

public:
	HRESULT Init();
	void Release();
	void Update(EnemyName name, FPOINT pos, float destAngle, float fireDelay, Mode mode);
	void Render(HDC hdc, EnemyName name, Mode mode);

	void Fire(EnemyName name, FPOINT pos, float angle, Mode mode);
	void SetIsPingPong(bool isPingPong) { this->isPingPong = isPingPong; }
	void SetTargetPos(FPOINT targetPos) { this->targetPos = targetPos; }

	vector<EMissile*> GetVecMissiles() { return vecMissiles; }
	int GetMissileCount() { return enemyMissileCount; }
	void SetIsShoot(bool isShoot) { this->isShoot = isShoot; }
	void SetLife(int life) { this->life = life; }
	bool GetIsShake() { return isShake; }
	void SetPhase(Phase phase) { this->phase = phase; }
};