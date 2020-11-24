#include "UI.h"
#include "Image.h"

HRESULT UI::Init()
{
	ImageManager::GetSingleton()->AddImage("»Úªˆ", "Image/lifebar_white.bmp", WINSIZE_X, 8 * 3.20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("ª°∞≠", "Image/lifebar_red.bmp", WINSIZE_X - 10, 6 * 3.22, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("∞À¡§", "Image/lifebar_black.bmp", WINSIZE_X - 10, 6 * 3.22, true, RGB(255, 0, 255));

	lifeBar[LifebarColor::White] = ImageManager::GetSingleton()->FindImage("»Úªˆ");
	lifeBar[LifebarColor::Red] = ImageManager::GetSingleton()->FindImage("ª°∞≠");
	lifeBar[LifebarColor::Black] = ImageManager::GetSingleton()->FindImage("∞À¡§");

	red = WINSIZE_X - 10;
	black = WINSIZE_X - 10;
	whiteBar = WINSIZE_X - 10;

	sec = 0.0f;

	return S_OK;
}

void UI::Release()
{
}

void UI::Update(int life, int bossLife, int firstBarrierLife, int secondBarrierLife, EnemyName name, Phase phase)
{
	if (name <= EnemyName::Panic)
	{
		if (life != FULL_LIFE)
		{
			black = ((WINSIZE_X - 10) / FULL_LIFE) * life;
		}

		sec += TimerManager::GetSingleton()->GetElapsedTime();

		if (sec >= 0.05)
		{
			if (red > black)
			{
				red -= 8.0f;
			}
			sec = 0.0f;
		}
	}

	if (name == EnemyName::Despair)
	{
		sec += TimerManager::GetSingleton()->GetElapsedTime();
		if (phase >= Phase::Phase1)
		{
			if (firstBarrierLife != FULL_LIFE)
			{
				black = ((WINSIZE_X - 10) / FULL_LIFE) * firstBarrierLife;
			}
			if (sec >= 0.05)
			{
				if (red > black)
				{
					red -= 8.0f;
				}
				sec = 0.0f;
			}
		}
		if (phase >= Phase::Phase2)
		{

		}
		if (phase >= Phase::Phase3)
		{
			
		}
	}
}

void UI::Render(HDC hdc)
{
	lifeBar[LifebarColor::White]->Render(hdc, 0, 0, White);
	lifeBar[LifebarColor::Red]->Render(hdc, 5, 2.5, Red, red);
	lifeBar[LifebarColor::Black]->Render(hdc, 5, 2.5, Black, black);
}
