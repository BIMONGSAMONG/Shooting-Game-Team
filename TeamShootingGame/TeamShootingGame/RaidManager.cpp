#include "RaidManager.h"
#include "Enemy.h"
#include "Player.h"
#include "EMissileManager.h"
#include "EMissile.h"
HRESULT RaidManager::Init()
{
	enemyMaxNum = 2;
	vecEnemy.reserve(enemyMaxNum);
	for (int i = 0; i < enemyMaxNum; i++)
	{
		vecEnemy.push_back(new Enemy());
		vecEnemy[i]->Init();
	}
	mode = Mode::Easy;
	name = EnemyName::Irritation;
	name2 = EnemyName::Anxiety;
	randomName = 0;
	raidLife = 60;
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
	vecEnemy[0]->Update(name, mode);
	vecEnemy[1]->Update(name2, mode);
	move();
	move2();
}

void RaidManager::Render(HDC hdc)
{
	vecEnemy[0]->Render(hdc, name, mode);
	vecEnemy[1]->Render(hdc, name2, mode);

	char szText[128] = "";
	wsprintf(szText, "HP : %d", raidLife);
	TextOut(hdc, 10, 175, szText, strlen(szText));
}

void RaidManager::move()
{
	switch (name)
	{
	case Irritation:
		vecEnemy[0]->GetMissileMgr()->SetMissileCount(3);
		break;
	case Pressure:
		break;
	case Loneliness:
		break;
	case Distress:
		break;
	case Fear:
		break;
	case Hatred:
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
	case END_NUM:
		break;
	case RaidMob:
		break;
	default:
		break;
	}
}

void RaidManager::move2()
{
	switch (name2)
	{
	case Irritation:
		break;
	case Pressure:
		break;
	case Loneliness:
		break;
	case Distress:
		break;
	case Fear:
		break;
	case Hatred:
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
		vecEnemy[1]->GetMissileMgr()->SetMissileCount(50);
		break;
	case Sadness:
		break;
	case Panic:
		break;
	case Despair:
		break;
	case END_NUM:
		break;
	case RaidMob:
		break;
	default:
		break;
	}
}
