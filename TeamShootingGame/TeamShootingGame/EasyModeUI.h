#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class EasyModeUI:public GameNode
{
private:
	Image* enemyTile;
	Image* script;

	struct Tile
	{
		bool isClear;
		FPOINT pos;
	};


	Image* img;

	Tile tile[18];
	int size;
	FPOINT pos;
	FPOINT tilePos[18];
	EnemyName TileNum[18];
	int count;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void UpMouseCurser();
	void MouseLButtonClick();

	int GetSize() { return this->size; }
	FPOINT GetTilePos();
	EnemyName GetTileNum();
	void SetIsClear(bool isClear, int num) { this->tile[num].isClear = isClear; }
	
};

