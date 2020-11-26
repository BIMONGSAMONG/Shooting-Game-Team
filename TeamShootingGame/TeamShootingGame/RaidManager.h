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
	EnemyName name2;
	Mode mode;
	int randomName;
	int enemyMaxNum;
	int raidLife;
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
	void move();
	void move2();
	int GetRaidLife() { return this->raidLife; }
	void SetRaidLife(int life) { this->raidLife = life; }
	
};
