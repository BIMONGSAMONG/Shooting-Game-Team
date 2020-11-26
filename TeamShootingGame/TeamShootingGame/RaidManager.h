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
	FPOINT pos1;
	EnemyName name;
	EnemyName name2;
	Mode mode;
	int randomName;
	int enemyMaxNum;
	int raidLife;
	bool isRaid;
	float timer;
	int counter;
	int bossCounter;
	float movePosX;
	float movePosY;
	float delayTIme;

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
	int GetRaidLife() { return this->raidLife; }
	void SetRaidLife(int life) { this->raidLife = life; }
};
