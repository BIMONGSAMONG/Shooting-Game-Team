#include "MainScene.h"
#include "EasyModeUI.h"
#include "HardModeUi.h"

HRESULT MainScene::Init()
{
	easy = new EasyModeUI();
	easy->Init();
	pos = { 0, 0 };
	return E_NOTIMPL;
}

void MainScene::Release()
{
}

void MainScene::Update()
{
}

void MainScene::Render(HDC hdc)
{
	if (easy) easy->Render(hdc);
}
