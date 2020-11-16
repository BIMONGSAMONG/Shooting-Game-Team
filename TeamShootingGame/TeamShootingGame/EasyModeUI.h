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
		Image* img;
	};

	Tile tile[18];
	int size;
	FPOINT pos;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void UpMouseCurser();
	void MouseLButtonClick();
	
	//void ImageRender(HDC hdc, int name);
};

