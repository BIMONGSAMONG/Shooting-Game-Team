#pragma once
#include "pch.h"
#include "GameNode.h"

class PMissile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float angle;
	bool isFire;
	EnemyName boss;
	float speed;
	Image* img[2];


public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool isFire) { this->isFire = isFire; }

	void SetPos(FPOINT pos) { this->pos = pos; }
	void SetBossName(EnemyName boss) { this->boss = boss; }
	int GetSize() { return size; }
	FPOINT GetPos() { return pos; }
};

