#include "EMissile.h"

HRESULT EMissile::Init()
{
	isFire = false;
	pos = { 0,0 };
	size = 20;
	angle = -PI / 2;
	speed = 1500.0f;
	goalTime = 5.0f;
	isPingPong = false;
	return S_OK;
}

void EMissile::Release()
{
}

void EMissile::Update()
{
	if (isFire)
	{
		pos.x += cosf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
		pos.y -= sinf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
		if (isPingPong)
		{
			if (pos.x - (size / 2) <= 0 + 10)
			{
				angle = PI - angle - (PI / 4);
			}
			if (pos.x + (size / 2) >= WINSIZE_X - 10)
			{
				angle = PI - angle + (PI / 4);
			}
			if (pos.y - (size / 2) <= 0 || pos.y + (size / 2) >= WINSIZE_Y)
			{
				angle = PI * 2.0f - angle;
			}
		}
		
		if (pos.x <= 0 || pos.x >= WINSIZE_X || pos.y <= 0 || pos.y >= WINSIZE_Y)
		{
			isFire = false;
		}
	}
	
}

void EMissile::Render(HDC hdc)
{
	if (isFire)
	{
		Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));
	}
}