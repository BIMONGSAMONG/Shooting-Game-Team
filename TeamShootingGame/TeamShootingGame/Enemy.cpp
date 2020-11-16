#include "Enemy.h"
#include "Image.h"

HRESULT Enemy::Init()
{
	pos = { WINSIZE_X / 2, 150 };
	size = 40;
	life = 50;
	currFrameX = 0;
	currFrameY = 0;
	img = ImageManager::GetSingleton()->FindImage("EºÐ³ë");
	img = ImageManager::GetSingleton()->FindImage("EÈ¥¶õ");

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
			Move();
			currFrameX = 0;
		}
		animationTime = 0;
	}
}

void Enemy::Render(HDC hdc)
{
	if (img)
	{
		img->FrameRender(hdc, pos.x - (size / 2), pos.y - (size / 2), currFrameX, currFrameY);
	}
	if (img)
	{
		img->Render(hdc, pos.x - (size / 2), pos.y - (size / 2));
	}
}

void Enemy::Move()
{
	pos.y += movePosY;
	if (pos.y <= 150)
	{
		movePosY = 4;
	}
	else if (pos.y >= 162)
	{
		movePosY = -4;
	}
}
