#include "EMissile.h"

HRESULT EMissile::Init()
{
	isFire = false;
	pos = { 0,0 };
	size = 14;
	angle = -PI / 2;
	pingpongAngle[0] = PI - (PI / 4);
	pingpongAngle[1] = PI + (PI / 4);
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
	random = rand() % 2;
	if (isFire)
	{
		pos.x += cosf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
		pos.y -= sinf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
		if (isPingPong)
		{
			if (pos.x - (size / 2) <= 0)
			{
				angle = pingpongAngle[random];
			}
			if (pos.x + (size / 2) >= WINSIZE_X)
			{
				angle = pingpongAngle[random] - PI;
			}
			if (pos.y + (size / 2) >= WINSIZE_Y)
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