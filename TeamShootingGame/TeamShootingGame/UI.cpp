#include "UI.h"
#include "Image.h"

HRESULT UI::Init()
{
	ImageManager::GetSingleton()->AddImage("Èò»ö", "Image/lifebar_white.bmp", WINSIZE_X, 8 * 3.20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("»¡°­", "Image/lifebar_red.bmp", WINSIZE_X - 10, 6 * 3.22, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("°ËÁ¤", "Image/lifebar_black.bmp", WINSIZE_X - 10, 6 * 3.22, true, RGB(255, 0, 255));

	lifeBar[LifebarColor::White] = ImageManager::GetSingleton()->FindImage("Èò»ö");
	lifeBar[LifebarColor::Red] = ImageManager::GetSingleton()->FindImage("»¡°­");
	lifeBar[LifebarColor::Black] = ImageManager::GetSingleton()->FindImage("°ËÁ¤");

	red = WINSIZE_X - 10;
	black = WINSIZE_X - 10;

	sec = 0.0f;

	return S_OK;
}

void UI::Release()
{
}

void UI::Update(int life)
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

void UI::Render(HDC hdc)
{
	lifeBar[LifebarColor::White]->Render(hdc, 0, 0, White);
	lifeBar[LifebarColor::Red]->Render(hdc, 5, 2.5, Red, red);
	lifeBar[LifebarColor::Black]->Render(hdc, 5, 2.5, Black, black);
}
