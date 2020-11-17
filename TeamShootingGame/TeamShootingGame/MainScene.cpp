#include "MainScene.h"
#include "EasyModeUI.h"
#include "HardModeUi.h"
#include "Image.h"

HRESULT MainScene::Init()
{
	img[0] = ImageManager::GetSingleton()->FindImage("왼쪽화살표");
	img[1] = ImageManager::GetSingleton()->FindImage("오른쪽화살표");
	isEasy = true;
	enemyChoice = false;
	easy = new EasyModeUI();
	easy->Init();

	hard = new HardModeUi();
	hard->Init();


	pos[0] = { 0 + 5, WINSIZE_Y / 2 - (24 * 3) };
	pos[1] = { WINSIZE_X - 12 * 3 - 5, WINSIZE_Y / 2 - (24 * 3) };
	return S_OK;
}

void MainScene::Release()
{
}

void MainScene::Update()
{
	if (isEasy)
	{
		if (easy) easy->Update();
	}
	else
	{
		if (hard) hard->Update();
	}

}

void MainScene::Render(HDC hdc)
{
	if (isEasy)
	{
		if (easy) easy->Render(hdc);
		img[0]->Render(hdc, pos[0].x, pos[0].y);
		img[1]->Render(hdc, pos[1].x, pos[1].y);
		//Rectangle(hdc, pos[0].x , pos[0].y , pos[0].x + 36 , pos[0].y + 72 );
		//Rectangle(hdc, pos[1].x, pos[1].y, pos[1].x + 36, pos[1].y + 72);
	}
	else
	{
		img[0]->Render(hdc, pos[0].x, pos[0].y);
		if (hard) hard->Render(hdc);
	}
}