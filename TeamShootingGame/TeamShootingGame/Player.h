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

	PMissileManager* missileMgr;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();

	FPOINT GetPos() { return pos; }
};

