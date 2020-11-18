#include "Enemy.h"
#include "Image.h"
#include "EMissileManager.h"

HRESULT Enemy::Init()
{
	pos = { WINSIZE_X / 2, 150 };
	size = 64;
	life = 50;
	currFrameX = 0;
	currFrameY = 0;
	destAngle = 0;

	missileMgr = new EMissileManager();
	missileMgr->Init();

	img = ImageManager::GetSingleton()->FindImage("Small_Boss");

	return S_OK;
}

void Enemy::Release()
{
	missileMgr->Release();
	delete missileMgr;
}

void Enemy::Update(EnemyName name)
{
	if (missileMgr)
	{
		missileMgr->Update();
	}

	destAngle = atan2f(-(targetPos.y) - pos.y, (targetPos.x) - pos.x);
	animationTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (animationTime >= 0.4f)
	{
		//currFrameX++;
		//if (currFrameX >= img->GetMaxFrameX())
		//{
		Move();
		//currFrameX = 0;
		//}
		animationTime = 0;
	}
	fireTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (fireTime >= 0.7)
	{
		Fire(name);
		fireTime = 0;
	}
}

void Enemy::Render(HDC hdc, EnemyName name, Mode mode)
{
	if (img)
	{
		img->FrameRender(hdc, pos.x, pos.y, name, mode);
	}

	if (missileMgr)
	{
		missileMgr->Render(hdc);
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

void Enemy::Fire(EnemyName name)
{
	switch (name)
	{
	case EnemyName::Irritation:
		if (missileMgr)
		{
			missileMgr->Fire(pos, destAngle, 1800);
		}
		break;
	case EnemyName::Pressure:
		if (missileMgr)
		{
			for (int i = -2; i < 3; i++)
			{
				missileMgr->Fire(pos, destAngle + (i / 10.0f), 800);
			}
		}
		break;
	}
}

