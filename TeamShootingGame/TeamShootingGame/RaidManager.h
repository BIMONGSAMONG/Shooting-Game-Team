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
	FPOINT pos;
	FPOINT pos2;
	EnemyName name;
	EnemyName name2;
	Mode mode;

	float timer;
	float moveTimer;
	float i;	// name 의 x좌표 움직임 추가값
	float k;	// name2 의 x좌표 움직임 추가값
	float j;	// y 좌표 움직임 추가값
	float t;	// 맵에 얼마나 체류할것인지 정하는 타이머

	int raidLife;
	int randomName;
	int enemyMaxNum;
	int count;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	vector<Enemy*> GetVecEnemy() { return vecEnemy; }
	EnemyName GetName() { return this->name; }
	EnemyName GetName2() { return this->name2; }
	Mode GetMode() { return this->mode; }
	int GetEnemyMaxNum() { return this->enemyMaxNum; }
	void Move();
	void Move2();
	int GetRaidLife() { return raidLife; }
	void SetRaidLife(int raidLife) { this->raidLife = raidLife; }
};
