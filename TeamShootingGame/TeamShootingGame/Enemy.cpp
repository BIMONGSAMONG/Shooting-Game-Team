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
	addAngle = PI / 3;
	count = 0;
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

void Enemy::Update(EnemyName name , float fireDelay)
{
	if (missileMgr)
	{
		missileMgr->Update();
	}

	//////플레이어가 있는 방향
	destAngle = atan2f(-(targetPos.y - pos.y), (targetPos.x - pos.x));
	
	fireTime += TimerManager::GetSingleton()->GetElapsedTime();
	secondFireDelay += TimerManager::GetSingleton()->GetElapsedTime();
	if (fireTime >= fireDelay)
	{
		Fire(name);
		count++;
		fireTime = 0.0f;
	}

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
	switch (name)
	{
	case Irritation:
		if (missileMgr)
		{
			missileMgr->Fire(pos, destAngle, 1300);
		}
		break;
	case Pressure:
		if (missileMgr)
		{
			angle += addAngle - (PI / 4);
			for (int i = 0; i < 6; i++)
			{
				missileMgr->Fire(pos, angle + addAngle * i + (PI / 4), 1000.0f);
			}
		}
		break;
	case Loneliness:
		break;
	case Distress:
		if (missileMgr)
		{
			for (int i = -1; i <= 1; i++)
			{
				missileMgr->Fire(pos, destAngle + (i / 6.0f), 1000.0f);
			}
		}
		break;
	case Fear:
		break;
	case Hatred:
		if (missileMgr)
		{
			if (count == 1)
			{
				for (int i = -4; i <= 4; i++)
				{
					if (i <= -2)
					{
						missileMgr->Fire(pos, destAngle + (i / 40.0f) - 0.25f, 1500.0f);
					}
					else if (i > -2 && i <= 1)
					{
						missileMgr->Fire(pos, destAngle + (i / 40.0f), 1500.0f);
					}
					else if (i > 1)
					{
						missileMgr->Fire(pos, destAngle + (i / 40.0f) + 0.25f, 1500.0f);
					}
				}
			}
			else if (count == 3)
			{
				for (int i = -6; i < 6; i++)
				{
					if (i <= -4)
					{
						missileMgr->Fire(pos, destAngle + (i / 40.0f) - 0.3f, 1500.0f);
					}
					else if (i > -4 && i <= -1)
					{
						missileMgr->Fire(pos, destAngle + (i / 40.0f) - 0.1f, 1500.0f);
					}
					else if (i > -1 && i <= 2)
					{
						missileMgr->Fire(pos, destAngle + (i / 40.0f) + 0.1f, 1500.0f);
					}
					else if (i > 2)
					{
						missileMgr->Fire(pos, destAngle + (i / 40.0f) + 0.3f, 1500.0f);
					}
				}
			}
			if (count >= 8)
			{
				count = 0;;
			}
		}
		break;
	case Guilt:
		break;
	case Confusion:
		if (missileMgr)
		{
			angle = 0;
			for (int i = 0; i < 4; i++)
			{
				missileMgr->Fire(pos, angle + addAngle * i, 1000.0f);
				missileMgr->SetIsPingPong(true);
			}
		}
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
	case END_NUM:
		break;
	default:
		break;
	}
}

