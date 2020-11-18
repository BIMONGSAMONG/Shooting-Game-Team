#include "BattleScene.h"
#include "Player.h"
#include "EnemyManager.h"

HRESULT BattleScene::Init()
{
	player = new Player();
	player->Init();

	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	return S_OK;
}

void BattleScene::Release()
{
	player->Release();
	delete player;

	enemyMgr->Release();
	delete enemyMgr;
}

void BattleScene::Update()
{
	if(player) player->Update();

	if (enemyMgr) enemyMgr->Update();

	enemyMgr->SetEnemyName(name);
	enemyMgr->SetMode(mode);
}

void BattleScene::Render(HDC hdc)
{
	if (player) player->Render(hdc);
	if (enemyMgr) enemyMgr->Render(hdc);
}
