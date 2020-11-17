#include "MainScene.h"
#include "EasyModeUI.h"
#include "HardModeUi.h"

HRESULT MainScene::Init()
{
	enemyChoice = false;
	easy = new EasyModeUI();
	easy->Init();
	pos = { 0, 0 };
	return S_OK;
}

void MainScene::Release()
{
}

void MainScene::Update()
{
	if (easy) easy->Update();
}

void MainScene::Render(HDC hdc)
{
	if (easy) easy->Render(hdc);
}
