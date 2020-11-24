#pragma once
#include "GameNode.h"
#include <vector>

class PMissile;
class PMissileManager
{
private:
	int missileCount;
	EnemyName boss;
	vector<PMissile*> vecMissiles;
	vector<PMissile*>::iterator itMissiles;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT pos);
	int GetMissileCount() { return missileCount; }
	vector<PMissile*> GetVecMissiles() { return vecMissiles; }
	void SetBossName(EnemyName boss) { this->boss = boss; }
};

