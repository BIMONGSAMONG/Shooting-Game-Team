#pragma once
#include "GameNode.h"
#include <vector>

class EMissile;
class EMissileManager :public GameNode
{
private:
	vector<EMissile*> vecMissiles;
	vector<EMissile*>::iterator itMissiles;
	int enemyMissileCount;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT pos, float angle, float speed);

};

