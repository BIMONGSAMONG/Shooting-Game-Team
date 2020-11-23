#include "Enemy.h"
#include "Image.h"
#include "EMissileManager.h"

HRESULT Enemy::Init()
{
	pos = { WINSIZE_X / 2, 150 };
	size = 64;
	bossSize = 128;
	life = 30;
	currFrameX = 0;
	currFrameY = 0;
	destAngle = 0;
	die = false;
	missileMgr = new EMissileManager();
	missileMgr->Init();

	img = ImageManager::GetSingleton()->FindImage("Small_Boss");
	for (int i = EnemyName::Anger; i <= EnemyName::Panic; i++)
	{
		bossImg[i - 13] = ImageManager::GetSingleton()->FindImage(i);
	}

	fireDelay = 0;

	return S_OK;
}

void Enemy::Release()
{
	missileMgr->Release();
	delete missileMgr;
}

void Enemy::Update(EnemyName name, Mode mode)
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
		fireDelay = 0.2f;
		break;
	case Distress:
		fireDelay = 0.3f;
		break;
	case Fear:
		fireDelay = 0.3;
		break;
	case Hatred:
		fireDelay = 0.2f;
		break;
	case Guilt:
		fireDelay = 0.3f;
		break;
	case Confusion:
		fireDelay = 0.3f;
		break;
	case Emptiness:
		fireDelay = 0.1f;
		break;
	case Shame:
		fireDelay = 0.3f;
		break;
	case Frustration:
		fireDelay = 1.3f;
		break;
	case Jealousy:
		fireDelay = 0.3f;
		break;
	case Hoplessness:
		break;
	case Anger:
		fireDelay = 0.2f;
		break;
	case Anxiety:
		break;
	case Sadness:
		fireDelay = 0.4f;
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
		missileMgr->Update(name, pos, destAngle, fireDelay, mode);
		missileMgr->SetLife(life);
	}

	//////플레이어가 있는 방향
	SetTargetPos(targetPos);
	destAngle = atan2f(-(targetPos.y - pos.y), (targetPos.x - pos.x));

	missileMgr->SetTargetPos(targetPos);

	animationTime += TimerManager::GetSingleton()->GetElapsedTime();
	if (animationTime >= 0.35f)
	{
		if (name != EnemyName::Anger)
		{
			Move();
		}
		currFrameX++;
		for (int i = EnemyName::Anger; i <= EnemyName::Panic; i++)
		{
			if (currFrameX >= bossImg[i - 13]->GetMaxFrameX())
			{
				currFrameX = 0;
			}
		}
		animationTime = 0;
	}

	if (name >= EnemyName::Anger)
	{
		bossAnimationTime += TimerManager::GetSingleton()->GetElapsedTime();
		if (bossAnimationTime >= 0.016f)
		{
			if (name == EnemyName::Anger && life <= 10)
			{
				pos.x += 2;
				if (pos.x - bossSize >= WINSIZE_X)
				{
					pos.x = 0;
				}
			}
			bossAnimationTime = 0;
		}
	}

	if (life <= 0)
	{
		die = true;
	}
}

void Enemy::Render(HDC hdc, EnemyName name, Mode mode)
{
	char szText[128] = "";
	wsprintf(szText, "HP : %d", life);
	TextOut(hdc, 10, 80, szText, strlen(szText));
	if (missileMgr)
	{
		missileMgr->Render(hdc, name, mode);
	}
	if (die == false)
	{
		if (img)
		{
			if (name < EnemyName::Anger)
			{
				img->FrameRender(hdc, pos.x, pos.y, name, mode);
			}
		}
		if (bossImg)
		{
			if (name >= EnemyName::Anger)
			{
				bossImg[name - 13]->FrameRender(hdc, pos.x, pos.y, currFrameX, mode);
			}
		}
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

void Enemy::Fire(EnemyName name, Mode mode)
{
	missileMgr->Fire(name, pos, destAngle, mode);
}