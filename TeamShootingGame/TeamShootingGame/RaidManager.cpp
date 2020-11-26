#include "RaidManager.h"
#include "Enemy.h"
#include "Player.h"
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
	randomName = 0;
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
	name = EnemyName(randomName);
	vecEnemy[0]->Update(name, mode);
}

void RaidManager::Render(HDC hdc)
{
	vecEnemy[0]->Render(hdc, name, mode);
}
