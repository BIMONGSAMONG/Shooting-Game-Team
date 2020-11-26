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
	float i;	// name �� x��ǥ ������ �߰���
	float k;	// name2 �� x��ǥ ������ �߰���
	float j;	// y ��ǥ ������ �߰���
	float t;	// �ʿ� �󸶳� ü���Ұ����� ���ϴ� Ÿ�̸�

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
