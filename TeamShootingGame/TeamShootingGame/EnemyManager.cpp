#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
	enemyCount = 36;
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
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Update(name);
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc, name);
	}
}
