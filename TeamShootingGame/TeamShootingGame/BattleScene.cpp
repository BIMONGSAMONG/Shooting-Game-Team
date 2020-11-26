#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "EMissileManager.h"
#include "EMissile.h"
#include "PMissileManager.h"
#include "PMissile.h"
#include "Image.h"
#include "UI.h"
#include "MainScene.h"
#include "RaidManager.h"

HRESULT BattleScene::Init()
{
	player = new Player();
	player->Init();

	enemy = new Enemy();
	enemy->Init();

	ui = new UI();
	ui->Init();

	raidMgr = new RaidManager();
	raidMgr->Init();

	img[0] = ImageManager::GetSingleton()->FindImage("일반죽음");
	img[1] = ImageManager::GetSingleton()->FindImage("보스죽음");

	isShake = false;
	shaking = false;
	isClear = false;

	return S_OK;
}

void BattleScene::Release()
{
	player->Release();
	delete player;

	enemy->Release();
	delete enemy;

	ui->Release();
	delete ui;

	raidMgr->Release();
	delete raidMgr;
}

void BattleScene::Update()
{

	if (player)
	{
		player->Update();
		if (name == EnemyName::Despair)
		{
			player->SetBossName(EnemyName::Despair);
		}
	}

	if (name == EnemyName::RaidMob)
	{
		if (raidMgr) raidMgr->Update();
	}
	else
	{
		if (enemy) enemy->Update(name, mode);
	}
	if (mode != Mode::Raid)
	{

		if (ui) ui->Update(enemy->GetLife(), enemy->GetBossLife(), enemy->GetFirstBarriarLife(), raidMgr->GetRaidLife(), enemy->GetSecondBarriarLife(), name, enemy->GetPhase(), mode);

		enemy->SetEnemyName(name);
		enemy->SetMode(mode);
		enemy->SetTargetPos(player->GetPos());
	}
	if(mode == Mode::Raid)
	{	
	 if (ui) ui->Update(raidMgr->GetVecEnemy()[0]->GetLife(), raidMgr->GetVecEnemy()[0]->GetBossLife(),
		 raidMgr->GetVecEnemy()[0]->GetFirstBarriarLife(), raidMgr->GetVecEnemy()[0]->GetSecondBarriarLife(), raidMgr->GetRaidLife(), raidMgr->GetName(),
		 raidMgr->GetVecEnemy()[0]->GetPhase(), mode);
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
	{
		player->Release();
		delete player;


		ui->Release();
		delete ui;

		player = new Player();
		player->Init();

		ui = new UI();
		ui->Init();

		if (name == EnemyName::RaidMob)
		{
			raidMgr->Release();
			delete raidMgr;
			raidMgr = new RaidManager();
			raidMgr->Init();
			//raidMgr->SetIsRaid(true);
		}
		else
		{
			enemy->Release();
			delete enemy;
			enemy = new Enemy();
			enemy->Init();
		}

	}

	if (mode != Mode::Raid)
	{
		//////총알에 맞는다니 제정신이 아니네요.
		for (int i = 0; i < enemy->GetMissileMgr()->GetMissileCount(); i++)
		{
			if (enemy->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
			{
				if (CheckCollision(player->GetSize(), enemy->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
					player->GetPos(), enemy->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && player->GetDie() == false)
				{
					if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_SHIFT))
					{
						player->SetDie(true);
						isShake = true;
						enemy->GetMissileMgr()->SetIsShoot(false);
					}
					enemy->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);

				}
			}
		}
		//////이겼으니 다행이지 목숨은 하나입니다.
		if (name < EnemyName::Anger)
		{
			for (int i = 0; i < player->GetMissileMgr()->GetMissileCount(); i++)
			{
				if (player->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
				{
					if (CheckCollision(enemy->GetSize(), player->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
						enemy->GetEnemyPos(), player->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && enemy->GetLife() >= 1)
					{
						enemy->SetLife(enemy->GetLife() - 1);
						player->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);
						if (enemy->GetLife() <= 0)
						{
							enemy->GetMissileMgr()->SetIsShoot(false);
							isShake = true;
							isClear = true;
						}
					}
				}
			}
		}

		else if (name >= EnemyName::Anger && name <= EnemyName::Panic)
		{
			for (int i = 0; i < player->GetMissileMgr()->GetMissileCount(); i++)
			{
				if (player->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
				{
					if (CheckCollision(enemy->GetBossSize(), player->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
						enemy->GetEnemyPos(), player->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && enemy->GetLife() >= 1)
					{
						enemy->SetLife(enemy->GetLife() - 1);
						player->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);
						if (enemy->GetLife() <= 0)
						{
							enemy->GetMissileMgr()->SetIsShoot(false);
							isShake = true;
							isClear = true;
						}
					}
				}
			}
		}

		else if (name == EnemyName::Despair)
		{
			if (enemy->GetPhase() >= Phase::Phase1)
			{
				for (int i = 0; i < player->GetMissileMgr()->GetMissileCount(); i++)
				{
					if (player->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
					{
						if (CheckCollision(enemy->GetFirstBerrierSize(), player->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
							enemy->GetEnemyPos(), player->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && enemy->GetBossLife() >= 1)
						{
							enemy->SetFinBossLife(enemy->GetFinBossLife() - 1);
							enemy->SetFirstBarriarLife(enemy->GetFirstBarriarLife() - 1);
							player->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);
							if (enemy->GetFirstBarriarLife() <= 0)
							{
								isShake = true;
							}
						}
					}
				}
			}
			else if (enemy->GetPhase() >= Phase::Phase2)
			{
				for (int i = 0; i < player->GetMissileMgr()->GetMissileCount(); i++)
				{
					if (player->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
					{
						if (CheckCollision(enemy->GetSecondBerrierSize(), player->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
							enemy->GetEnemyPos(), player->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && enemy->GetBossLife() >= 1)
						{
							enemy->SetFinBossLife(enemy->GetFinBossLife() - 1);
							enemy->SetSecondBarriarLife(enemy->GetSecondBarriarLife() - 1);
							player->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);
							if (enemy->GetSecondBarriarLife() <= 0)
							{
								isShake = true;
							}
						}
					}
				}
			}
			if (enemy->GetPhase() >= Phase::Phase3)
			{
				for (int i = 0; i < player->GetMissileMgr()->GetMissileCount(); i++)
				{
					if (player->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
					{
						if (CheckCollision(enemy->GetFinBossSize(), player->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
							enemy->GetEnemyPos(), player->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && enemy->GetBossLife() >= 1)
						{
							enemy->SetFinBossLife(enemy->GetFinBossLife() - 1);
							enemy->SetBossLife(enemy->GetBossLife() - 1);
							player->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);
							if (enemy->GetFinBossLife() <= 0)
							{
								enemy->GetMissileMgr()->SetIsShoot(false);
								isShake = true;
								isClear = true;
							}
						}
					}
				}
			}
		}

		if (name == EnemyName::Anger)
		{
			if (enemy->GetLife() > 10 && shaking == false)
			{
				shaking = enemy->GetMissileMgr()->GetIsShake();
			}
			if (enemy->GetLife() <= 10)
			{
				shaking = false;
			}
		}

		else if (name < EnemyName::Anger)
		{
			if (CheckCollision(enemy->GetSize(), player->GetSize(), enemy->GetEnemyPos(), player->GetPos()))
			{
				player->SetDie(true);
				isShake = true;
				shaking = false;
				enemy->GetMissileMgr()->SetIsShoot(false);
			}
		}

		else if (name >= EnemyName::Anger && name <= EnemyName::Panic)
		{
			if (CheckCollision(enemy->GetBossSize(), player->GetSize(), enemy->GetEnemyPos(), player->GetPos()))
			{
				player->SetDie(true);
				isShake = true;
				shaking = false;
				enemy->GetMissileMgr()->SetIsShoot(false);
			}
		}

		else if (name == EnemyName::Despair)
		{
			if (enemy->GetPhase() >= Phase::Phase1)
			{
				if (CheckCollision(enemy->GetFirstBerrierSize(), player->GetSize(), enemy->GetEnemyPos(), player->GetPos()))
				{
					player->SetDie(true);
					isShake = true;
					shaking = false;
					enemy->GetMissileMgr()->SetIsShoot(false);
				}
			}
			else if (enemy->GetPhase() >= Phase::Phase2)
			{
				if (CheckCollision(enemy->GetSecondBerrierSize(), player->GetSize(), enemy->GetEnemyPos(), player->GetPos()))
				{
					player->SetDie(true);
					isShake = true;
					shaking = false;
					enemy->GetMissileMgr()->SetIsShoot(false);
				}
			}
			if (enemy->GetPhase() >= Phase::Phase3)
			{
				if (CheckCollision(enemy->GetFinBossSize(), player->GetSize(), enemy->GetEnemyPos(), player->GetPos()))
				{
					player->SetDie(true);
					isShake = true;
					shaking = false;
					enemy->GetMissileMgr()->SetIsShoot(false);
				}
			}
		}
	}
	
	if (mode == Mode::Raid)
	{
		
		for (int i = 0; i < raidMgr->GetEnemyMaxNum(); i++)
		{
			//적 공격 플레이어에게 적중
			for (int j = 0; j < raidMgr->GetVecEnemy()[i]->GetMissileMgr()->GetMissileCount(); j++)
			{
				if (raidMgr->GetVecEnemy()[i]->GetMissileMgr()->GetVecMissiles()[j]->GetIsFire() == true)
				{
					if (CheckCollision(player->GetSize(), raidMgr->GetVecEnemy()[i]->GetMissileMgr()->GetVecMissiles()[j]->GetSize(),
						player->GetPos(), raidMgr->GetVecEnemy()[i]->GetMissileMgr()->GetVecMissiles()[j]->GetPos()) && player->GetDie() == false)
					{
						if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_SHIFT))
						{
							player->SetDie(true);
							isShake = true;
							raidMgr->GetVecEnemy()[i]->GetMissileMgr()->SetIsShoot(false);
						}
						raidMgr->GetVecEnemy()[i]->GetMissileMgr()->GetVecMissiles()[j]->SetIsFire(false);
					}
				}
			}
		}
		// 플레이어 공격 적에게 적중
		if (raidMgr->GetRaidLife() > 0)
		{
			for (int i = 0; i < player->GetMissileMgr()->GetMissileCount(); i++)
			{
				for (int j = 0; j < raidMgr->GetEnemyMaxNum(); j++)
				{
					if (player->GetMissileMgr()->GetVecMissiles()[i]->GetIsFire() == true)
					{
						if (CheckCollision(raidMgr->GetVecEnemy()[j]->GetSize(), player->GetMissileMgr()->GetVecMissiles()[i]->GetSize(),
							raidMgr->GetVecEnemy()[j]->GetEnemyPos(), player->GetMissileMgr()->GetVecMissiles()[i]->GetPos()) && raidMgr->GetRaidLife() >= 1)
						{
							raidMgr->SetRaidLife(raidMgr->GetRaidLife() - 1);
							player->GetMissileMgr()->GetVecMissiles()[i]->SetIsFire(false);
							if (raidMgr->GetRaidLife() <= 0)
							{
								raidMgr->GetVecEnemy()[j]->GetMissileMgr()->SetIsShoot(false);
								isShake = true;
								isClear = true;
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < raidMgr->GetEnemyMaxNum(); i++)
		{
			raidMgr->GetVecEnemy()[i]->SetTargetPos(player->GetPos());
		}
	}


	//////벽에 다가서지마세요 죽고싶습니까?
	if (player->GetPos().x - (player->GetSize() / 2.0f) < 0 || player->GetPos().x + (player->GetSize() / 2.0f) > WINSIZE_X ||
		player->GetPos().y - (player->GetSize() / 2.0f) < 0 || player->GetPos().y + (player->GetSize() / 2.0f) > WINSIZE_Y)
	{
		player->SetDie(true);
		enemy->GetMissileMgr()->SetIsShoot(false);
		isShake = true;
		shaking = false;
	}
}

void BattleScene::Render(HDC hdc)
{

	if (player) player->Render(hdc);

	if (name == EnemyName::RaidMob)
	{
		if (raidMgr->GetRaidLife() > 0)
		{
			if (raidMgr) raidMgr->Render(hdc);
		}
	}
	else
	{
		if (enemy) enemy->Render(hdc, name, mode);
	}
	if (mode != Mode::Raid)
	{
		if (ui) ui->Render(hdc, name, enemy->GetPhase(), mode);
	}
	else if (mode == Mode::Raid)
	{
		if (ui) ui->Render(hdc, raidMgr->GetName(), raidMgr->GetVecEnemy()[0]->GetPhase(), raidMgr->GetMode());
	}
	if (player->GetDie() == true)
	{
		if (img)
		{
			if (name <= EnemyName::Panic)
			{
				img[0]->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2);
			}
			else if (name == EnemyName::Despair)
			{
				img[1]->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2);
			}
		}
	}
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

//void BattleScene::SetIsRaid(bool raid)
//{
//	this->raidMgr->SetIsRaid(raid);
//}
