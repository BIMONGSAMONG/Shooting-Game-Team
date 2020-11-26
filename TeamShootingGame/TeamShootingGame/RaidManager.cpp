#include "RaidManager.h"
#include "Enemy.h"
#include "Player.h"
#include "EMissileManager.h"
HRESULT RaidManager::Init()
{
	pos = { 10, 60 };
	pos2 = { WINSIZE_X - 10, 60 };
	enemyMaxNum = 2;
	vecEnemy.reserve(enemyMaxNum);
	for (int i = 0; i < enemyMaxNum; i++)
	{
		vecEnemy.push_back(new Enemy());
		vecEnemy[i]->Init();
	}
	mode = Mode::Easy;
	name = EnemyName::Irritation;
	name2 = EnemyName::Jealousy;
	raidLife = 60;
	vecEnemy[0]->SetLife(60);
	randomName = 0;
	i = 1.0;
	k = -1.0f;
	j = 0.5f;
	t = 0;
	timer = 0;
	moveTimer = 0;
	vecEnemy[0]->SetEnemyPos(pos);
	vecEnemy[1]->SetEnemyPos(pos2);
	return S_OK;
}

void RaidManager::Release()
{
	for (itEnemy = vecEnemy.begin(); itEnemy != vecEnemy.end(); itEnemy++)
	{
		(*itEnemy)->Release();
		delete (*itEnemy);
	}
	vecEnemy.clear();
}

void RaidManager::Update()
{
	//randomName = rand()%18;
	//mode = Mode(rand() % 2);
	//name = EnemyName(17);
	vecEnemy[0]->Update(name, mode);
	vecEnemy[1]->Update(name2, mode);
		
	Move(); 
	Move2();
}

void RaidManager::Render(HDC hdc)
{
	vecEnemy[0]->Render(hdc, name, mode);
	vecEnemy[1]->Render(hdc, name2, mode);
	char szText[128] = "";
	wsprintf(szText, "Raid HP : %d", raidLife);
	TextOut(hdc, 10, 175, szText, strlen(szText));
}

void RaidManager::Move()
{
	switch (name)
	{
	case Irritation:
		vecEnemy[0]->GetMissileMgr()->SetMissileCount(10);
		pos.x += i;
		t =5.0f;
		if (pos.y <= WINSIZE_Y / 2 + 100)
		{
			pos.y += j;
			if (pos.x >= (WINSIZE_X / 2) - 400)
			{
				i = +1.0f;
			}
			if (pos.x >= (WINSIZE_X / 2) - 300)
			{
				i = +0.9f;
			}
			if (pos.x >= (WINSIZE_X / 2) - 280)
			{
				i = +0.8f;
			}
			if (pos.x >= (WINSIZE_X / 2) - 260)
			{
				i = +0.7f;
			}
			if (pos.x >= (WINSIZE_X / 2) - 200)
			{
				i = +0.5f;
			}
		}
		if (pos.y >= WINSIZE_Y / 2 + 100)
		{
			i = -2.0f;
			j = 0;
			
		}

			moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (moveTimer >= t)
			{
				pos.x = 10;
				pos.y = 100;
				i = +1.0f;
				name = EnemyName::Pressure;
				moveTimer = 0;
			}
		break;
	case Pressure:
		vecEnemy[0]->GetMissileMgr()->SetMissileCount(30);
		pos.x += i;
		t = 1.5f;
		if (pos.x >= WINSIZE_X)
		{
			moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (moveTimer >= t)
			{
				pos.x = 10;
				pos.y = 30;
				i = +2.0f;
				name = EnemyName::Frustration;
				mode = Mode::Hard;
				moveTimer = 0;
			}
		}
		break;
	case Loneliness:
		pos.x += i;
		pos.y += 1.0f;
		t = 2.2f;
		if (pos.x >= WINSIZE_X)
		{
			moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (moveTimer >= t)
			{
				pos.x = WINSIZE_X - 10;
				pos.y = 50;
				i = -1.0f;
				name = EnemyName::Distress;
				moveTimer = 0;
			}
		}
		break;
	case Distress:
		pos.x += i;
		t = 0.1f;
		if (pos.x <= 0)
		{
			moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (moveTimer >= t)
			{
				pos.x = WINSIZE_X / 2;
				pos.y = 0;
				i = 3.0f;
				name = EnemyName::Shame;
				moveTimer = 0;
			}
		}
		break;
	case Fear:
		pos.x += i;
		t = 2.0f;
		if (pos.x >= (WINSIZE_X / 2) - 100)
		{
			i = -1.0f;
		}
		pos.y += 0.1;
		if (pos.x <= 200)
		{
			pos.x = 200;
			if (pos.x <= 0)
			{
				moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
				if (moveTimer >= t)
				{
					pos.x = 10;
					pos.y = 50;
					i = +1.0f;
					name = EnemyName::Confusion;
					moveTimer = 0;
				}
			}
		}
		break;
	case Hatred:
		pos.x += i;
		t = 2.0f;
		if (pos.x >= (WINSIZE_X / 2) - 100)
		{
			i = -1.0f;
		}
		pos.y += 0.1;
		if (pos.x <= 200)
		{
			pos.x = 200;
			if (pos.x <= 0)
			{
				moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
				if (moveTimer >= t)
				{
					pos.x = 10;
					pos.y = 50;
					i = +1.0f;
					name = EnemyName::Guilt;
					moveTimer = 0;
				}
			}
		}
		break;
	case Guilt:
		pos.x += i;
		t = 2.0f;
		if (pos.x >= (WINSIZE_X / 2) - 100)
		{
			i = -1.0f;
		}
		pos.y += 0.1;
		if (pos.x <= 200)
		{
			pos.x = 200;
			if (pos.x <= 0)
			{
				moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
				if (moveTimer >= t)
				{
					pos.x = 10;
					pos.y = 50;
					i = +1.0f;
					name = EnemyName::Pressure;
					moveTimer = 0;
				}
			}
		}
		break;
	case Confusion:
		pos.x += i;
		t = 2.0f;
		if (pos.x >= (WINSIZE_X / 2) - 100)
		{
			i = -1.0f;
		}
		pos.y += 0.1;
		if (pos.x <= 200)
		{
			pos.x = 200;
			if (pos.x <= 0)
			{
				moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
				if (moveTimer >= t)
				{
					pos.x = 10;
					pos.y = 50;
					i = +1.0f;
					name = EnemyName::Hatred;
					moveTimer = 0;
				}
			}
		}
		break;
	case Emptiness:
		vecEnemy[0]->GetMissileMgr()->SetMissileCount(50);
		pos.x += i;
		t = 2.0f;
		if (pos.x >= (WINSIZE_X / 2) - 100)
		{
			i = -1.0f;
		}
		pos.y += 0.1;
		if (pos.x <= 200)
		{
			pos.x = 200;
			if (pos.x <= 0)
			{
				moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
				if (moveTimer >= t)
				{
					pos.x = 10;
					pos.y = 50;
					i = +1.0f;
					name = EnemyName::Loneliness;
					moveTimer = 0;
				}
			}
		}
		break;
	case Shame:
		if (pos.y < 100)
		{
			pos.y += i;
		}
		t = 3.0f;
		if (pos.y >= 100 && pos.y < 103)
		{
			i = 0;
			pos.y += i;
			moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (moveTimer >= t)
			{
				pos.x = WINSIZE_X / 2;
				pos.y = 0;
				i = 2.0f;
				name = EnemyName::Fear;
				moveTimer = 0;
			}
		}
		pos.y += i;
		break;
	case Frustration:
		vecEnemy[0]->GetMissileMgr()->SetMissileCount(200);
		pos.x += i;
		t = 2.0f;
		if (pos.x >= (WINSIZE_X / 2) - 100)
		{
			i = -1.0f;
		}
		pos.y += 0.1;
		if (pos.x <= 200)
		{
			pos.x = 200;
			if (pos.x <= 0)
			{
				moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
				if (moveTimer >= t)
				{
					pos.x = 10;
					pos.y = 50;
					i = +1.0f;
					name = EnemyName::Emptiness;
					moveTimer = 0;
				}
			}
		}
		break;
	}
	vecEnemy[0]->SetEnemyPos(pos);
}

void RaidManager::Move2()
{
	switch (name2)
	{
	case Jealousy:
		vecEnemy[1]->GetMissileMgr()->SetMissileCount(30);
		pos2.x += k;
		t = 1.0f;
		if (pos2.y <= WINSIZE_Y / 2 - 100)
		{
			pos2.y += j;
			if (pos2.x >= (WINSIZE_X / 2) + 400)
			{
				k = -1.0f;
			}
			if (pos2.x >= (WINSIZE_X / 2) + 300)
			{
				k = -0.9f;
			}
			if (pos2.x >= (WINSIZE_X / 2) + 280)
			{
				k = -0.8f;
			}
			if (pos2.x >= (WINSIZE_X / 2) + 260)
			{
				k = -0.7f;
			}
			if (pos2.x >= (WINSIZE_X / 2) + 200)
			{
				k = -0.5f;
			}
		}
		if (pos2.y >= WINSIZE_Y / 2 + 100)
		{
			k = +2.0f;
			j = 0;

		}
		if (pos2.x >= WINSIZE_X)
		{
			timer += TimerManager::GetSingleton()->GetElapsedTime();
			if (timer >= t)
			{
				pos2.x = 10;
				pos2.y = 100;
				k = +1.0f;
				name2 = EnemyName::Hoplessness;
				timer = 0;
			}
		}
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

	vecEnemy[1]->SetEnemyPos(pos2);
}
