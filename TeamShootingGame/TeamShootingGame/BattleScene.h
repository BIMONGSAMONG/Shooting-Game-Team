#pragma once
#include "pch.h"
#include "GameNode.h"

class Player;
class Enemy;
class EMissileManager;
class PMissileManager;
class Image;
class UI;
class RaidManager;
class BattleScene : public GameNode
{
private:
	Player* player;
	Enemy* enemy;
	Image* img[2];
	EnemyName name;
	Mode mode;
	UI* ui;
	RaidManager* raidMgr;

	bool isShake;
	bool shaking;
	bool isClear;
	
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetEnemyName(EnemyName name) { this->name = name; }
	void SetMode(Mode mode) { this->mode = mode; }

	bool CheckCollision(int size_1, int size_2, FPOINT pos_1, FPOINT pos_2);
	float GetDistance(FPOINT pos1, FPOINT pos2);

	Enemy* GetEnemy() { return enemy; }

	bool GetIsShake() { return isShake; }
	void SetIsShake(bool isShake) { this->isShake = isShake; }
	bool GetIsShaking() { return shaking; }
	void SetIsShaking(bool shaking) { this->shaking = shaking; }
	bool GetIsClear() { return isClear; }
	//void SetIsRaid(bool raid);
};

