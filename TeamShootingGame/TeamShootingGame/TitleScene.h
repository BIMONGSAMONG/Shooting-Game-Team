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

	void PressZKey(); // ZŰ�� ������ MainScene���� �Ѿ����
	void StartSceneTimer();
	bool GetGoMain() { return goMain; }
};

