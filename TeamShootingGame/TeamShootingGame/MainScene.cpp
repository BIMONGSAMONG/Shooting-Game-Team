#include "MainScene.h"
#include "EasyModeUI.h"
#include "HardModeUi.h"
#include "Image.h"

HRESULT MainScene::Init()
{
	img[0] = ImageManager::GetSingleton()->FindImage("왼쪽화살표");
	img[1] = ImageManager::GetSingleton()->FindImage("오른쪽화살표");
	img[2] = ImageManager::GetSingleton()->FindImage("시크릿");
	img[3] = ImageManager::GetSingleton()->FindImage("레이드");

	mode = Mode::Easy;
	enemyChoice = false;
	easy = new EasyModeUI();
	easy->Init();

	hard = new HardModeUi();
	hard->Init();

	pos[0] = { 0 + 22 , WINSIZE_Y / 2 - 50 };
	pos[1] = { WINSIZE_X - 22 , WINSIZE_Y / 2 - 50 };

	raidTile.isClear = false;
	raidTile.pos = { WINSIZE_X / 2, WINSIZE_Y / 2 };
	raidTile.size = 194 * 3;

	return S_OK;
}

void MainScene::Release()
{
}

void MainScene::Update()
{
	if (mode == Mode::Easy)
	{
		if (easy) easy->Update();
	}
	else if (mode == Mode::Hard)
	{
		if (hard) hard->Update();
	}

}

void MainScene::Render(HDC hdc)
{
	if (mode == Mode::Easy)
	{
		if (easy) easy->Render(hdc);
		img[0]->Render(hdc, pos[0].x, pos[0].y);
		img[1]->Render(hdc, pos[1].x, pos[1].y);
		//Rectangle(hdc, pos[0].x , pos[0].y , pos[0].x + 36 , pos[0].y + 72 );
		//Rectangle(hdc, pos[1].x, pos[1].y, pos[1].x + 36, pos[1].y + 72);
	}
	else if (mode == Mode::Hard)
	{
		img[0]->Render(hdc, pos[0].x, pos[0].y);
		img[1]->Render(hdc, pos[1].x, pos[1].y);
		if (hard) hard->Render(hdc);
	}
	else if (mode == Mode::Secret)
	{
		img[2]->Render(hdc, 0, 0);
		img[1]->Render(hdc, pos[1].x, pos[1].y);
	}
	else if (mode == Mode::Raid)
	{
		img[0]->Render(hdc, pos[0].x, pos[0].y);
		img[3]->FrameRender(hdc, raidTile.pos.x, raidTile.pos.y, 0, raidTile.isClear);
	}
}