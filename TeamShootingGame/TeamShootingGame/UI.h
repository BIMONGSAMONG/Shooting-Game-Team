#pragma once
#include "GameNode.h"
#include "Image.h"

class UI : public GameNode
{
private:
	Image* lifeBar[3];
	float red;
	float black;

	float sec;

public:
	HRESULT Init();
	void Release();
	void Update(int life);
	void Render(HDC hdc);
};
