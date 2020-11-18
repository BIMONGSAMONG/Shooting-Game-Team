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
	int name;
	
	EMissileManager* missileMgr;
	Image* img;


public:
	HRESULT Init();
	void Release();
	void Update(EnemyName name);
	void Render(HDC hdc, EnemyName name);

	void Move();

	FPOINT GetEnemyPos() { return pos; }
};

