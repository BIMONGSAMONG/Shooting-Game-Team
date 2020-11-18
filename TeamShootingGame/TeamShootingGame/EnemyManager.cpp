#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
	enemyCount = 1;
	vecEnemys.reserve(enemyCount);
	for (int i = 0; i < enemyCount; i++)
	{
		vecEnemys.push_back(new Enemy());
		vecEnemys[i]->Init();
	}
	return S_OK;
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Release();
		delete (*itEnemys);
	}
	vecEnemys.clear();
}

void EnemyManager::Update()
{
	switch (name)
	{
	case Irritation:
		fireDelay = 2.1f;
		break;
	case Pressure:
		fireDelay = 0.1f;
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
	default:
		break;
	}
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Update(name, fireDelay);
		(*itEnemys)->SetTargetPos(targetPos);
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc, name, mode);
	}
}
