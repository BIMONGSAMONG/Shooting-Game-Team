#pragma once
#include "pch.h"
#include "GameNode.h"
#include <vector>

class Enemy;
class RaidManager : public GameNode
{
private:
	vector <Enemy*> vecEnemy;
	vector <Enemy*>::iterator itEnemy;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};
