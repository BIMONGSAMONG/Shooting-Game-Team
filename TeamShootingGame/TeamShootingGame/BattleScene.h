#pragma once
#include "pch.h"
#include "GameNode.h"

class Player;
class Enemy;
class BattleScene : public GameNode
{
private:
	Player* player;
	Enemy* enemy;
	EnemyName name;
	Mode mode;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetEnemyName(EnemyName name) { this->name = name; }
	void SetMode(Mode mode) { this->mode = mode; }
};

