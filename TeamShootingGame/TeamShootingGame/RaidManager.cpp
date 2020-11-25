#include "RaidManager.h"
#include "Enemy.h"

HRESULT RaidManager::Init()
{
	vecEnemy.reserve(36);
	for (int i = 0; i < 36; i++)
	{
		vecEnemy.push_back(new Enemy());
		vecEnemy[i]->Init();
	}
	return S_OK;
}

void RaidManager::Release()
{
	for (itEnemy = vecEnemy.begin(); itEnemy != vecEnemy.end(); itEnemy++)
	{
		(*itEnemy)->Release();
		delete (*itEnemy);
	}
}

void RaidManager::Update()
{
	
}

void RaidManager::Render(HDC hdc)
{
	
}
