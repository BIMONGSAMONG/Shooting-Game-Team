#pragma once
#include "pch.h"
#include "GameNode.h"

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


public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

