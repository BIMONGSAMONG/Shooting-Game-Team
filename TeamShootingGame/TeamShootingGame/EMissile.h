#pragma once
#include "pch.h"
#include "GameNode.h"

class EMissile : public GameNode
{
private:
	FPOINT pos;
	int size;
	float angle;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

