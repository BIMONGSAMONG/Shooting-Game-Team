#pragma once
#include "pch.h"
#include "GameNode.h"

class Image;
class TitleScene :public GameNode
{
private:
	Image* background;
	Image* startScene;
	bool goMain;
	bool isStart;
	float startTimer;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void PressZKey(); // Z키를 누르면 MainScene으로 넘어가도록
	void StartSceneTimer();
	bool GetGoMain() { return goMain; }
};

