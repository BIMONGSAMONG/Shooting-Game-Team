#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "EMissileManager.h"
#include "EMissile.h"
#include "PMissileManager.h"
#include "PMissile.h"

HRESULT BattleScene::Init()
{
	player = new Player();
	player->Init();

	enemy = new Enemy();
	enemy->Init();

	return S_OK;
}

void BattleScene::Release()
{
	player->Release();
	delete player;

	enemy->Release();
	delete enemy;
}

void BattleScene::Update()
{
	if (player->GetDie() == false)
	{
		if (player) player->Update();
	}

	if (enemy) enemy->Update(name, mode);


	enemy->SetEnemyName(name);
	enemy->SetMode(mode);
	enemy->SetTargetPos(player->GetPos());

	for (int i = 0; i < enemy->GetMissileMgr()->GetMissileCount(); i++)
	{
		if (enemy->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
		{
			if (CheckCollision(player->GetSize(), enemy->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
				player->GetPos(), enemy->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && player->GetDie() == false)
			{
				player->SetDie(true);
				enemy->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);
				enemy->GetMissileMgr()->SetIsShoot(false);
			}
		}
	}

	for (int i = 0; i < player->GetMissileMgr()->GetMissileCount(); i++)
	{
		if (player->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
		{
			if (CheckCollision(enemy->GetSize(), player->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
				enemy->GetEnemyPos(), player->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && enemy->GetLife() >= 1)
			{
				enemy->SetLife(enemy->GetLife() - 1);
				player->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);
				enemy->GetMissileMgr()->SetIsShoot(false);
			}
		}
	}
}

void BattleScene::Render(HDC hdc)
{
	if (player) player->Render(hdc);
	if (enemy) enemy->Render(hdc, name, mode);
}

bool BattleScene::CheckCollision(int size_1, int size_2, FPOINT pos_1, FPOINT pos_2)
{
	float halfSize1 = size_1 / 2.0f;
	float halfSize2 = size_2 / 2.0f;
	FPOINT pos1 = pos_1;
	FPOINT pos2 = pos_2;

	if (GetDistance(pos1, pos2) <= halfSize1 + halfSize2)
	{
		return true;
	}
	return false;
}

float BattleScene::GetDistance(FPOINT pos1, FPOINT pos2)
{
	float dist = sqrtf((pos2.x - pos1.x) * (pos2.x - pos1.x)
		+ (pos2.y - pos1.y) * (pos2.y - pos1.y));

	return dist;
}
