#pragma once
#include "pch.h"
#include "GameNode.h"
#include "EasyModeUI.h"
class EasyModeUI;
class HardModeUI;
class MainScene:public GameNode
{
private:
	EasyModeUI* easy;
	HardModeUI* hard;
	Image* img;
	FPOINT pos;
	int size;
	bool enemyChoice;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetEnemyChoice() { return this->enemyChoice; }
	void SetEnemyChoice(bool choice) { this->enemyChoice = choice; }
	FPOINT GetEasyPos() { return this->easy->GetTilePos(); }
	int GetEasySize() { return this->easy->GetSize(); }
	EnemyName GetEasyTileNum() { return this->easy->GetTileNum(); }
};

