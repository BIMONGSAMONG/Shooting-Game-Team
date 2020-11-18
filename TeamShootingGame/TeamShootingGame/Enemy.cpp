#include "Enemy.h"
#include "Image.h"

HRESULT Enemy::Init()
{
	pos = { WINSIZE_X / 2, 150 };
	size = 64;
	life = 50;
	currFrameX = 0;
	currFrameY = 0;

	img = ImageManager::GetSingleton()->FindImage("Easy_Boss");

	return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update(EnemyName name)
{
	animationTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (animationTime >= 0.4f)
	{
		//currFrameX++;
		//if (currFrameX >= img->GetMaxFrameX())
		//{
			Move();
			currFrameX = 0;
		//}
		animationTime = 0;
	}
}

void Enemy::Render(HDC hdc, EnemyName name)
{
	if (img)
	{
		img->FrameRender(hdc, pos.x, pos.y, name, 0);
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
