#include "RaidManager.h"
#include "Enemy.h"
#include "Player.h"
#include "EMissileManager.h"
#include "EMissile.h"
HRESULT RaidManager::Init()
{
	enemyMaxNum = 1;
	vecEnemy.reserve(enemyMaxNum);
	for (int i = 0; i < enemyMaxNum; i++)
	{
		vecEnemy.push_back(new Enemy());
		vecEnemy[i]->Init();
	}
	mode = Mode::Hard;
	name = EnemyName::Irritation;
	randomName = 0;
	raidLife = 60;
	bossCounter = 0;
	counter = 0;
	timer = 0;
	delayTIme = 6.0;
	movePosX = 1.0f;
	movePosY = 0.0f;
	pos1 = { WINSIZE_X / 2, 100 };
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
	if (raidLife <= 59)
	{
		delayTIme = 2.2f;
	}
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	if (timer >= delayTIme)
	{
		if (delayTIme == 2.2f)
		{
			vecEnemy[0]->GetMissileMgr()->SetCounter(0);
		}
		counter++;
		bossCounter++;
		name = (EnemyName)counter;
		timer = 0;
	}
	if (name >= EnemyName::Anger)
	{
		counter = 0;
		name = (EnemyName)counter;
	}
	if (bossCounter >= 13)
	{
		name = (EnemyName)bossCounter;
	}
	if (name > EnemyName::Despair)
	{
		name = EnemyName::Anger;
		bossCounter = 13;
	}

	move();
	vecEnemy[0]->Update(name, mode);
}

void RaidManager::Render(HDC hdc)
{
	if (raidLife > 0)
	{
		vecEnemy[0]->Render(hdc, name, mode);
	}
	if (raidLife <= 0)
	{
		vecEnemy[0]->GetMissileMgr()->Render(hdc, name, mode);
	}



	//char szText[128] = "";
	//wsprintf(szText, "HP : %d", raidLife);
	//TextOut(hdc, 10, 175, szText, strlen(szText));
}

void RaidManager::move()
{
	switch (name)
	{
	case Irritation:
		pos1.x += movePosX;
		if (pos1.x <= 10)
		{
			movePosX = 1.0f;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -1.0f;
		}
		break;
	case Pressure:
		pos1.x += movePosX;
		if (pos1.x <= 10)
		{
			movePosX = 2.0f;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -2.0f;
		}
		break;
	case Loneliness:
		pos1.x += movePosX;
		pos1.y += movePosY;
		if (pos1.x <= 10)
		{
			movePosX = 1.0f;
			movePosY = 0.5f;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -1.0f;
			movePosY = -0.1f;
		}
		break;
	case Distress:
		break;
	case Fear:
		pos1.x += movePosX;
		if (pos1.x <= 10)
		{
			movePosX = rand() % 10 + 1;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -(rand() % 10 + 1);
		}
		break;
	case Hatred:
		pos1.x += movePosX;
		if (pos1.x <= 10)
		{
			movePosX = 1.0f;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -1.0f;
		}
		break;
	case Guilt:
		pos1.x += movePosX;
		pos1.y += movePosY;
		if (pos1.x <= 10)
		{
			movePosX = 2.0f;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -2.0f;
		}
		if (pos1.y <= 50)
		{
			movePosY = 2.0f;
		}
		else if (pos1.y >= 100)
		{
			movePosY = -2.0f;
		}
		break;
	case Confusion:
		pos1.x += movePosX;
		if (pos1.x <= 10)
		{
			movePosX = 1.0f;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -1.0f;
		}
		break;
	case Emptiness:
		break;
	case Shame:
		pos1.x += movePosX;
		if (pos1.x <= 10)
		{
			movePosX = rand() % 10 + 1;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -(rand() % 10 + 1);
		}
		break;
	case Frustration:
		pos1.x = 100;
		pos1.y = 100;
		break;
	case Jealousy:
		pos1.x = 600;
		pos1.y = 100;
		break;
	case Hoplessness:
		pos1.x += movePosX;
		pos1.y += movePosY;
		if (pos1.x <= 10)
		{
			movePosX = 1.0f;
			movePosY = 0.5f;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -1.0f;
			movePosY = -0.1f;
		}
		break;
	case Anger:
		pos1.x = WINSIZE_X / 2;
		pos1.y = 200;
		vecEnemy[0]->SetSize(128);
		break;
	case Anxiety:
		pos1.x += movePosX;
		pos1.y += movePosY;
		if (pos1.x <= 10)
		{
			movePosX = 2.0f;
		}
		else if (pos1.x >= WINSIZE_X - 10)
		{
			movePosX = -2.0f;
		}
		if (pos1.y <= 50)
		{
			movePosY = 2.0f;
		}
		else if (pos1.y >= 100)
		{
			movePosY = -2.0f;
		}
		break;
	case Sadness:
		pos1.x = rand() % 590 + 200;
		pos1.y = rand() % 200 + 100;
		break;
	case Panic:
		pos1.x = rand() % 590 + 200;
		pos1.y = rand() % 200 + 100;
		break;
	case Despair:
		pos1.x = WINSIZE_X / 2;
		pos1.y = 150;
		vecEnemy[0]->SetSize(320);
	default:
		break;
	}
	vecEnemy[0]->SetPos(pos1);
}