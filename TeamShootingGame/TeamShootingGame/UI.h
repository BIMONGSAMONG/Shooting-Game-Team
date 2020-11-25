#pragma once
#include "GameNode.h"
#include "Image.h"

class UI : public GameNode
{
private:
	Image* lifeBar[3];
	float red;
	float black;
	float whiteBar;

	float fRed;
	float fBlack;

	float sec;

	char szText[256];

public:
	HRESULT Init();
	void Release();
	void Update(int life, int bossLife, int firstBarrierLife, int secondBarrierLife, EnemyName name, Phase phase);
	void Render(HDC hdc, EnemyName name, Phase phase, Mode mode);
};
