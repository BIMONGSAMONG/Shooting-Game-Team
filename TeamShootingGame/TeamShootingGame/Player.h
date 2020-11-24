#pragma once
#include "pch.h"
#include "GameNode.h"

class PMissileManager;
class Player : public GameNode
{
private:
	FPOINT pos;
	int size;
	float timer;
	EnemyName boss;
	bool die;
	PMissileManager* missileMgr;
	Image* img[2];
	float timerDelay;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();

	FPOINT GetPos() { return pos; }
	int GetSize() { return size; }
	void SetDie(bool die) { this->die = die; }
	PMissileManager* GetMissileMgr() { return missileMgr; }
	bool GetDie() { return die; }
	void SetBossName(EnemyName boss) { this->boss = boss; }
};

