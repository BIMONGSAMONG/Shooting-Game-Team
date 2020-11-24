#include "Enemy.h"
#include "Image.h"
#include "EMissileManager.h"

HRESULT Enemy::Init()
{
	pos = { WINSIZE_X / 2, 150 };
	size = 64;
	bossSize = 128; 
	firstBerrierSize = 320;
	secondtBerrierSize = 160;
	finBossSize = 60;
	life = FULL_LIFE;
	finBossLife = FIN_LIFE;
	currFrameX = 0;
	currFrameY = 0;
	destAngle = 0;
	die = false;
	missileMgr = new EMissileManager();
	missileMgr->Init();
	setLife = false;
	BossLife = FULL_LIFE;
	firstBarriarLife = FULL_LIFE;
	secondBarriarLife = FULL_LIFE;

	img = ImageManager::GetSingleton()->FindImage("Small_Boss");
	Fin_Easy_Boss = ImageManager::GetSingleton()->FindImage("Easy_Boss");
	Fin_Hard_Boss = ImageManager::GetSingleton()->FindImage("Hard_Boss");
	BossBarrier1 = ImageManager::GetSingleton()->FindImage("Boss_FirstBarrier");
	BossBarrier2 = ImageManager::GetSingleton()->FindImage("Boss_SecondBarrier");

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
		fireDelay = 0.05f;
		break;
	case Jealousy:
		fireDelay = 0.3f;
		break;
	case Hoplessness:
		fireDelay = 0.3f;
		break;
	case Anger:
		if (setLife == false)
		{
			life = 30;
			setLife = true;
		}
		fireDelay = 0.2f;
		break;
	case Anxiety:
		if (setLife == false)
		{
			life = 30;
			setLife = true;
		}
		fireDelay = 0.2f;
		break;
	case Sadness:
		if (setLife == false)
		{
			life = 30;
			setLife = true;
		}
		fireDelay = 0.4f;
		break;
	case Panic:
		if (setLife == false)
		{
			life = 30;
			setLife = true;
		}
		fireDelay = 0.2f;
		break;
	case Despair:
		if (setLife == false)
		{
			life = 30;
			setLife = true;
		}
		fireDelay = 0.2f;
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

	if (name != EnemyName::Anger && name <= EnemyName::Panic)
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.016f)
		{
			Move();
			moveTimer = 0;
		}
	}

	if (name <= EnemyName::Panic)
	{
		animationTime += TimerManager::GetSingleton()->GetElapsedTime();
		if (animationTime >= 0.35f)
		{
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
	}
	if (name == EnemyName::Despair)
	{
		finBossAnimationTimer += TimerManager::GetSingleton()->GetElapsedTime();		
		if (finBossAnimationTimer >= 0.2f)
		{
			currFrameX++;
			if (name == EnemyName::Despair)
			{
				if (currFrameX >= Fin_Hard_Boss->GetMaxFrameX())
				{
					currFrameX = 0;
				}
			}
			finBossAnimationTimer = 0;
		}

		barrierTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (barrierTimer >= 0.016f)
		{
			currFrameX2++;
			if (name == EnemyName::Despair)
			{
				Move();
				if (currFrameX2 >= BossBarrier1->GetMaxFrameX())
				{
					currFrameX2 = 0;
				}
			}
			barrierTimer = 0;
		}
	}

	if (name == EnemyName::Anger)
	{
		bossAnimationTime += TimerManager::GetSingleton()->GetElapsedTime();
		if (bossAnimationTime >= 0.016f)
		{
			if (name == EnemyName::Anger)
			{
				if (mode == Mode::Easy && life <= 15)
				{
					pos.x += 2;
					if (pos.x - bossSize >= WINSIZE_X)
					{
						pos.x = 0;
					}
				}
				else if (mode == Mode::Hard && life <= 20)
				{
					pos.x += 2;
					if (pos.x - bossSize >= WINSIZE_X)
					{
						pos.x = 0;
					}
				}
			}
			bossAnimationTime = 0;
		}
	}

	if (life <= 0)
	{
		die = true;
	}
	if (name == EnemyName::Despair)
	{
		if (finBossLife <= 30)
		{
			phase = Phase::Phase3;
		}
		if (finBossLife <= 60 && finBossLife > 30)
		{
			phase = Phase::Phase2;
		}
		if (finBossLife > 60)
		{
			phase = Phase::Phase1;
		}
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
			if (name >= EnemyName::Anger && name <= EnemyName::Panic )
			{
				bossImg[name - 13]->FrameRender(hdc, pos.x, pos.y, currFrameX, mode);
			}
		}

		if (name == EnemyName::Despair && mode == Mode::Easy)
		{
			if (phase >= Phase::Phase1)
			{
				if (BossBarrier1)
				{
					//BossBarrier1->AlphaFrameRender(hdc, pos.x, pos.y, currFrameX2, 0, 100);
					BossBarrier1->FrameRender(hdc, pos.x, pos.y, currFrameX2, 0);
				}
			}
			if (phase >= Phase::Phase2)
			{
				if (BossBarrier2)
				{
					BossBarrier2->Render(hdc, pos.x, pos.y);
				}
			}
			if (Fin_Easy_Boss)
			{
				if (phase == Phase::Phase1 || phase == Phase::Phase2)
				{
					Fin_Easy_Boss->FrameRender(hdc, pos.x, pos.y, 0, 0);
				}
				else if (phase == Phase::Phase3)
				{
					Fin_Easy_Boss->FrameRender(hdc, pos.x, pos.y, 0, 1);
				}
			}
		}
		if (name == EnemyName::Despair && mode == Mode::Hard)
		{
			if (BossBarrier1)
			{
				if (phase >= Phase::Phase1)
				{
					//BossBarrier1->AlphaFrameRender(hdc, pos.x, pos.y, currFrameX2, 0, 100);
					BossBarrier1->FrameRender(hdc, pos.x, pos.y, currFrameX2, 0);
				}
			}

			if (BossBarrier2)
			{
				if (phase >= Phase::Phase2)
				{
					BossBarrier2->Render(hdc, pos.x, pos.y);
				}
			}

			if (Fin_Hard_Boss)
			{
				if (phase == Phase::Phase1 || phase == Phase::Phase2)
				{
					Fin_Hard_Boss->FrameRender(hdc, pos.x, pos.y, currFrameX, 0);
				}
				else if (phase == Phase::Phase3)
				{
					Fin_Hard_Boss->FrameRender(hdc, pos.x, pos.y, currFrameX, 1);
				}
			}
		}
	}
}

void Enemy::Move()
{
	pos.y += movePosY;
	if (pos.y <= 150)
	{
		movePosY = (float)0.2;
	}
	else if (pos.y >= 162)
	{
		movePosY = -(float)0.2;
	}
}

void Enemy::Fire(EnemyName name, Mode mode)
{
	missileMgr->Fire(name, pos, destAngle, mode);
}