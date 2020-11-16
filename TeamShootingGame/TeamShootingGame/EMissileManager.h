#pragma once
#include "GameNode.h"
#include <vector>

class EMissile;
class EMissileManager :public GameNode
{
private:
	vector<EMissile*> vecMissiles;
	vector<EMissile*>::iterator itMissiles;
	int eMissileCount;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire();
};

