#include "EMissile.h"
#include "Image.h"

HRESULT EMissile::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Boss_Bullet");
	isFire = false;
	pos = { 0,0 };
	size = 16;
	angle = -PI / 2;
	speed = 1500.0f;
	goalTime = 5.0f;
	isPingPong = false;

	isSizeDown = false;
	isSizeUp = false;;
	isLeftAngle = false;
	isRightAngle = false;
	leftAddAngle = 0;
	rightAddAngle = 0;

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
			timer += TimerManager::GetSingleton()->GetElapsedTime();
			if (timer <= 8.0f)
			{
				if (pos.x - (size / 2) <= 0)
				{
					pingpongAngle[0] = PI - (PI / 2) - (PI / 4);
					pingpongAngle[1] = PI + (PI / 2) + (PI / 4);
					angle = pingpongAngle[random];
				}
				if (pos.x + (size / 2) >= WINSIZE_X)
				{
					pingpongAngle[0] = 0 - (PI / 2) - (PI / 4);
					pingpongAngle[1] = 0 + (PI / 2) + (PI / 4);
					angle = pingpongAngle[random];
				}
				if (pos.y - (size / 2) <= 0)
				{
					pingpongAngle[0] = 0 - (PI / 4);
					pingpongAngle[1] = PI + (PI / 4);
					angle = pingpongAngle[random];
				}
				if (pos.y + (size / 2) >= WINSIZE_Y)
				{
					pingpongAngle[0] = 0 + (PI / 4);
					pingpongAngle[1] = PI - (PI / 4);
					angle = pingpongAngle[random];
				}
			}
			else if (timer > 8.0f)
			{
				isFire = false;
				timer = 0;
			}
		}
		if (isLeftAngle)
		{

			pos.x += cosf(angle)* speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
			pos.y -= sinf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
			angle += leftAddAngle;
		}
		if (isRightAngle)
		{
			pos.x += cosf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
			pos.y -= sinf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
			angle += rightAddAngle;
		}
		if (!isLeftAngle && !isRightAngle)
		{
			pos.x += cosf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
			pos.y -= sinf(angle) * speed * TimerManager::GetSingleton()->GetElapsedTime() / goalTime;
		}

		if (pos.x <= 0 || pos.x >= WINSIZE_X || pos.y <= 0 || pos.y >= WINSIZE_Y)
		{
			isFire = false;
			isSizeDown = false;
			isSizeUp = false;
		}
		if (pos.x <= 150 || pos.x >= WINSIZE_X - 150 || pos.y <= 50 || pos.y >= WINSIZE_Y - 150)
		{
			if (isSizeDown)
			{
				size = 10;
			}
			if (isSizeUp)
			{
				size = 15;
			}
		}
	}

}

void EMissile::Render(HDC hdc, EnemyName name, Mode mode)
{
	if (isFire)
	{
		//Ellipse(hdc, pos.x - (size / 2), pos.y - (size / 2), pos.x + (size / 2), pos.y + (size / 2));
		if (img)
		{
			img->FrameRender(hdc, pos.x, pos.y, name, mode);
		}
	}
}

void EMissile::SetLeftAddAngle(float leftAddAngle, float fDivision)
{
	this->leftAddAngle = DegreeToRadian(leftAddAngle) / fDivision;
}

void EMissile::SetRightAddAngle(float rightAddAngle, float fDivision)
{
	this->rightAddAngle = DegreeToRadian(rightAddAngle) / fDivision;
}
