#pragma once
#include "GameNode.h"
#include <vector>

class EMissile;
class EMissileManager :public GameNode
{
private:
	vector<EMissile*> vecMissiles;
	vector<EMissile*>::iterator itMissiles;
	int enemyMissileCount;
	bool isPingPong;

	float angle;
	float addAngle;

	float fireTime;
	int count;

public:
	HRESULT Init();
	void Release();
	void Update(EnemyName name, FPOINT pos, float destAngle, float fireDelay);
	void Render(HDC hdc);

	void Fire(EnemyName name, FPOINT pos, float angle);
	void SetIsPingPong(bool isPingPong) { this->isPingPong = isPingPong; }
};

