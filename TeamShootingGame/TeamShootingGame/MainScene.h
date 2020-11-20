#pragma once
#include "pch.h"
#include "GameNode.h"
#include "EasyModeUI.h"
#include "HardModeUi.h"

class EasyModeUI;
class HardModeUi;
class MainScene :public GameNode
{
private:
	EasyModeUI* easy;
	HardModeUi* hard;
	Image* img[2];
	FPOINT pos[2];
	int size;
	bool enemyChoice;
	Mode mode;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetEnemyChoice() { return this->enemyChoice; }
	void SetEnemyChoice(bool choice) { this->enemyChoice = choice; }

	FPOINT GetEasyPos() { return this->easy->GetTilePos(); }
	FPOINT GetHardPos() { return this->hard->GetTilePos(); }

	int GetEasySize() { return this->easy->GetSize(); }
	int GetHardSize() { return this->hard->GetSize(); }

	EnemyName GetEasyTileNum() { return this->easy->GetTileNum(); }
	EnemyName GetHardTileNum() { return this->hard->GetTileNum(); }

	FPOINT GetLeftPos() { return this->pos[0]; }
	FPOINT GetRightPos() { return this->pos[1]; }

	void SetMode(Mode mode) { this->mode = mode; }
	Mode GetMode() { return  this->mode; }
	EasyModeUI* GetEasyModUI() { return this->easy; }
	HardModeUi* GetHardModeUI() { return this->hard; }
};

