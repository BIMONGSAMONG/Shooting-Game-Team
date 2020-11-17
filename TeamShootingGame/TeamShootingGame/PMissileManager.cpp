#include "PMissileManager.h"
#include "PMissile.h"

HRESULT PMissileManager::Init()
{
	missileCount = 6;
	vecMissiles.reserve(missileCount);
	for (int i = 0; i < 6; i++)
	{
		vecMissiles.push_back(new PMissile());
		vecMissiles[i]->Init();
	}
	return S_OK;
}

void PMissileManager::Release()
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Release();
		delete (*itMissiles);
	}
	vecMissiles.clear();
}

void PMissileManager::Update()
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Update();
	}
}

void PMissileManager::Render(HDC hdc)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Render(hdc);
	}
}

void PMissileManager::Fire(FPOINT pos)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		if ((*itMissiles)->GetIsFire() == false)
		{
			(*itMissiles)->SetPos(pos);
			(*itMissiles)->SetIsFire(true);
			break;
		}
	}
}
