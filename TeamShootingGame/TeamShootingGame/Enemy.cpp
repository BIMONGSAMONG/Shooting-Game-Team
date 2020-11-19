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

	fireDelay = 0;

	return S_OK;
}

void Enemy::Release()
{
	missileMgr->Release();
	delete missileMgr;
}

void Enemy::Update(EnemyName name)
{
	switch (name)
	{
	case Irritation:
		fireDelay = 0.9f;
		break;
	case Pressure:
		fireDelay = 1.2f;
		break;
	case Loneliness:
		break;
	case Distress:
		fireDelay = 1.2f;
		break;
	case Fear:
		break;
	case Hatred:
		fireDelay = 0.2f;
		break;
	case Guilt:
		break;
	case Confusion:
		break;
	case Emptiness:
		break;
	case Shame:
		break;
	case Frustration:
		break;
	case Jealousy:
		break;
	case Hoplessness:
		break;
	case Anger:
		break;
	case Anxiety:
		break;
	case Sadness:
		break;
	case Panic:
		break;
	case Despair:
		break;
	default:
		break;
	}

	if (missileMgr)
	{
		missileMgr->Update(name, pos, destAngle, fireDelay);
	}

	//////플레이어가 있는 방향
	SetTargetPos(targetPos);
	destAngle = atan2f(-(targetPos.y - pos.y), (targetPos.x - pos.x));

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
}

void Enemy::Render(HDC hdc, EnemyName name, Mode mode)
{
	if (missileMgr)
	{
		missileMgr->Render(hdc);
	}
	if (img)
	{
		img->FrameRender(hdc, pos.x, pos.y, name, mode);
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
	missileMgr->Fire(name, pos, destAngle);
}

