#include "EMissile.h"

HRESULT EMissile::Init()
{
	isFire = false;
	pos = { 0,0 };
	size = 14;
	angle = -PI / 2;
	speed = 1500.0f;
	goalTime = 5.0f;
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