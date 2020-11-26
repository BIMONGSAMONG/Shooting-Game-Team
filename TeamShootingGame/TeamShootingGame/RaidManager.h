#pragma once
#include "pch.h"
#include "GameNode.h"
#include <vector>

class Enemy;

class RaidManager : public GameNode
{
private:
	vector <Enemy*> vecEnemy;
	vector <Enemy*>::iterator itEnemy;

	EnemyName name;
	Mode mode;
	int randomName;
	int enemyMaxNum;

	bool isRaid;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetIsRaid(bool raid) { this->isRaid = raid; }
	bool GetIsRaid() { return this->isRaid; }
	vector<Enemy*> GetVecEnemy() { return vecEnemy; }
	EnemyName GetName() { return this->name; }
	Mode GetMode() { return this->mode; }
	int GetEnemyMaxNum() { return this->enemyMaxNum; }

	
};
