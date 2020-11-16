#pragma once
#include "pch.h"
#include "GameNode.h"

class EMissileManager;
class Enemy : public GameNode
{
private:
	FPOINT pos;
	int size;
	int life;
	
	EMissileManager* missileMgr;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

