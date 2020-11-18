#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class EnemyManager
{
private:
	vector<Enemy*>	vecEnemys;
	vector<Enemy*>::iterator itEnemys;
	int enemyCount;
	EnemyName name;
	Mode mode;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetEnemyName(EnemyName name) { this->name = name; }
	//EnemyName GetEnemyName() { return this->name; }

	void SetMode(Mode mode) { this->mode = mode; }
};

