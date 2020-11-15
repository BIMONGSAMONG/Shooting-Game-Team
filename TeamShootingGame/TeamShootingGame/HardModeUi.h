#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class HardModeUi : public GameNode
{
private:
	Image* enemyTile;
	Image* script;
	
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void UpMouseCurser();
	void MouseLButtonClick();
};

