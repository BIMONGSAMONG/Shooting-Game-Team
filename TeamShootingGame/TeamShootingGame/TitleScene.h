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

	void PressZKey(); // ZŰ�� ������ MainScene���� �Ѿ����
	bool GetGoMain() { return goMain; }
};

