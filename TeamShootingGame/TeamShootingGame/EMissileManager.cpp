#include "EMissileManager.h"
#include "EMissile.h"

HRESULT EMissileManager::Init()
{
	enemyMissileCount = 100;
	vecMissiles.reserve(enemyMissileCount);
	for (int i = 0; i < enemyMissileCount; i++)
	{
		vecMissiles.push_back(new EMissile());
		vecMissiles[i]->Init();
	}
	return E_NOTIMPL;
}

void EMissileManager::Release()
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Release();
		delete (*itMissiles);
	}
	vecMissiles.clear();
}

void EMissileManager::Update()
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Update();
	}
}

void EMissileManager::Render(HDC hdc)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		(*itMissiles)->Render(hdc);
	}
}

void EMissileManager::Fire(FPOINT pos, float angle, float speed)
{
	for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
	{
		if ((*itMissiles)->GetIsFire() == false)
		{
			(*itMissiles)->SetPos(pos);
			(*itMissiles)->SetSpeed(speed);
			(*itMissiles)->SetAngle(angle);
			(*itMissiles)->SetIsFire(true);
			(*itMissiles)->SetIsPingPong(isPingPong);
			break;
		}
	}
}
