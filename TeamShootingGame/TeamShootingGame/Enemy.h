#pragma once
#include "pch.h"
#include "GameNode.h"

class EMissileManager;
class Image;
class Enemy : public GameNode
{
private:
	FPOINT pos;
	int size;
	int life;
	int currFrameX, currFrameY;
	float animationTime;
	float movePosY;
	
	EMissileManager* missileMgr;
	Image* img;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();

	FPOINT GetEnemyPos() { return pos; }
};

