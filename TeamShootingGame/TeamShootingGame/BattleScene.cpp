#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"

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
	if(player) player->Update();

	if (enemy) enemy->Update(name);

	enemy->SetEnemyName(name);
	enemy->SetMode(mode);
	enemy->SetTargetPos(player->GetPos());
}

void BattleScene::Render(HDC hdc)
{
	if (player) player->Render(hdc);
	if (enemy) enemy->Render(hdc, name, mode);
}
