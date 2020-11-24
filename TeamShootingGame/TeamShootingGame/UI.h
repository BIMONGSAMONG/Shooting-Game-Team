#pragma once
#include "GameNode.h"
#include "Image.h"

class UI : public GameNode
{
private:
	Image* lifeBar[4];
	float red;
	float black;
	float whiteBar;

	float sec;

public:
	HRESULT Init();
	void Release();
	void Update(int life, int bossLife, int firstBarrierLife, int secondBarrierLife, EnemyName name, Phase phase);
	void Render(HDC hdc);
};
