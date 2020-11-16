#include "Enemy.h"
#include "Image.h"

HRESULT Enemy::Init()
{
	pos = { WINSIZE_X / 2, 150 };
	size = 40;
	life = 50;
	currFrameX = 0;
	currFrameY = 0;
	img = ImageManager::GetSingleton()->FindImage("ºÐ³ë");

	return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	animationTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (animationTime >= 0.4f)
	{
		currFrameX++;
		if (currFrameX >= img->GetMaxFrameX())
		{
			//Move();
			currFrameX = 0;
		}
		animationTime = 0;
	}
}

void Enemy::Render(HDC hdc)
{
	if (img)
	{
		img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
	}
}

void Enemy::Move()
{
	pos.y += movePosY;
	if (pos.y <= 100)
	{
		movePosY = 2;
	}
	else if (pos.y >= 120)
	{
		movePosY = -2;
	}
}
