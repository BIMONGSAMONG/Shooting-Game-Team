#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class TitleScene :public GameNode
{
private:
	Image* background;
	bool goMain;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void PressZKey(); // Z키를 누르면 MainScene으로 넘어가도록
	bool GetGoMain() { return goMain; }
};

